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
    work_chunks = []
    for _ in range(16):
        work_chunks.append((temp_start, temp_start + range_per_process))
        temp_start += range_per_process
    work_chunks = np.array(work_chunks, dtype=float)
    moment_results = np.zeros(16,dtype=float)
    moment_chunk = np.zeros(2, dtype=float)
    gather_res = np.zeros(1,dtype=float)
else:
    work_chunks = None
    moment_results = None
    gather_res = np.zeros(1,dtype=float)
    moment_chunk = np.zeros(2, dtype=float)
    
# Scatter the bits of work to do
comm.Scatter(work_chunks, moment_chunk, root=root)

for k in range(16):
    # Perform integration for ith moment
    worker_res[0] = integral(moment_chunk[0], moment_chunk[1], k+1)
    comm.Reduce(worker_res, gather_res, MPI.SUM, root)
    comm.Barrier()
    if rank == 0:
        moment_results[k] = gather_res[0]
        
if rank == 0:
    ground_truth_arr = []
    ground_truth = 1
    for i in range(1,17):
        ground_truth *= i
        ground_truth_arr.append(ground_truth)
    ground_truth_arr = np.array(ground_truth_arr, dtype=float)
    
    for i in range(0,16):
        print(f"Moment {i+1} result = {moment_results[i]}, Ground Truth: {ground_truth_arr[i]} Error: {np.abs(ground_truth_arr[i]-moment_results[i])}")
    
