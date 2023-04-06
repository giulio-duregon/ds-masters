#Imports
import numpy as np
from mpi4py import MPI

# Initialize comm network, get rank so processes can identify themselves / execute as appropriate
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
info = MPI.Status()

# Get total number of processes
size = comm.Get_size() 
last_rank = size-1

# Initialize buffer
buffer = np.zeros(1)

# Start of with the first process rank == 0
if rank == 0:
    print(f"Process {rank}, sending number: {buffer[0]}, to Process {rank+1}")
    comm.Send(buffer, dest=(rank+1))
    
    # Wait for message from last process
    print(f"Waiting for value from Process {size-1}")
    comm.Recv(buffer, source = (last_rank))
    
    # Print final output
    print(f"Received Final Number From Process {last_rank}: {buffer[0]}")
    
# Do all for N-2
if rank != last_rank and rank != 0:
    # Receive value into buffer
    comm.Recv(buffer, source=(rank-1), status=info)
    print(f"Process {rank}, received the number {buffer[0]}, from Process {info.Get_source()}")
    # Square rank and add to buffer
    buffer += rank**2
    
    # Send value
    comm.Send(buffer, dest=(rank+1))
    
# Check for the final process (N-1)
if rank == last_rank:
    comm.Recv(buffer, source=(last_rank-1), status=info)
    print(f"Process {rank}, received the number {buffer[0]}, from Process {info.Get_source()}")
    # Square rank and add to buffer
    buffer += rank**2
    
    # Send value, but this time to process 0
    print("Sending result back to Process 0")
    comm.Send(buffer, dest=0)
    
