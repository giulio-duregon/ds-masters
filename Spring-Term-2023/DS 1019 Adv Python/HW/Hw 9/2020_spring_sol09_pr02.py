import numpy as np
from mpi4py import MPI

# Standard Setup for MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
root = 0

# Define helper function for integral calculation
def integral(start, stop, moment, inc_per_partition=1000):
    partial_int = np.zeros(1, dtype=float)
    step_size = (stop - start)/ inc_per_partition
    x = start
    for _ in range(inc_per_partition):
        partial_int += np.multiply(np.power(x,moment), np.exp(-x))
        x += step_size
    return np.multiply(partial_int, step_size)
        

start, stop = 0, 1000
temp_start = 0
N = 16
range_per_process = (stop - start) // N
inc_per_partition = 1000

worker_res = np.zeros(1)

if rank == 0:
    moment_results = np.zeros(16,dtype=float)
    gather_res = np.zeros(1,dtype=float)
else:
    moment_results = None
    gather_res = np.zeros(1,dtype=float)


# Scatter the buffer    
comm.Scatter(moment_results, gather_res, root=0)

# Calc moments 0-15

gather_res = integral(start,stop,rank+1, inc_per_partition)

# Gather the buffer
comm.Gather(gather_res, moment_results,root=0)
        
#print results, 
if rank == 0:
    ground_truth_arr = []
    ground_truth = 1
    for i in range(1,16):
        ground_truth *= i
        ground_truth_arr.append(ground_truth)
    ground_truth_arr = np.array(ground_truth_arr, dtype=float)
    
    for i in range(15):
        print(f"Moment {i+1} result = {moment_results[i]:.4f}, Ground Truth: {ground_truth_arr[i]:.1f} Error: {np.abs(ground_truth_arr[i]-moment_results[i]):.4f}")
