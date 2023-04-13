import numpy as np
from mpi4py import MPI
from time import time

# Standard Setup for MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
root = 0


# Helper function for computing averages
def chunk_average(points, n):
    return np.divide(np.sum(points),n)

def chunk_std(points, mean, n):
    return np.divide(np.sum(np.power(np.subtract(points, mean),2)),n)

# Number of samples to draw
n = 256_000

# Compute partition
num_points_per_process = (n // size)

# Let Process 0 Draw Samples, and hold final values
if rank == 0:
    start_time = time()
    samples = np.random.uniform(0,1,n)
    target_average = np.zeros(1, dtype=float)
    target_std = np.zeros(1, dtype=float)
else:
    # Need to be initialized to avoid errors
    samples = None
    target_average = np.zeros(1,dtype=float)
    target_std = np.zeros(1,dtype=float)

# Temp buffers for all processes
helper_average = np.zeros(1, dtype=float)
helper_std = np.zeros(1, dtype=float)

# Provide buffer for all samples
small_samples = np.zeros(num_points_per_process, dtype=float)

# Scatter the points
comm.Scatter(samples, small_samples, root=root)

#Perform Average calculation on each chunk (N is Global here)
helper_average = chunk_average(small_samples, n)

# Reduce The Helper averages -> Target Average (True avg of all points)
comm.Reduce(helper_average, target_average, op=MPI.SUM, root=root)

# Force Synchronization before sending the average back out
# (Used in std calculation)

comm.Bcast(target_average, root=root)

# # Perform standard deviation calcs on chunks
helper_std = chunk_std(small_samples, target_average, n)

# Send back and reduce into a sum
comm.Reduce(helper_std, target_std, op=MPI.SUM, root=root)

if rank == 0:
    target_std = np.sqrt(target_std)
    
if rank == 0:
    print(f"Time Elapsed: {time()-start_time}s")
    print(f"target_average={target_average}")
    print(f"target_std={target_std}")
