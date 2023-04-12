#Imports
import numpy as np
from mpi4py import MPI
import argparse

# Initialize comm network, get rank so processes can identify themselves / execute as appropriate
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
info = MPI.Status()

# Get total number of processes
size = comm.Get_size() 
last_rank = size-1

# Initialize buffer for each process
p = np.ones(1)

# Process 0 Logic
if rank == 0:   
    
    # Using arg parse rather than sys.stdin 
    # Easier to prove code works in Jupyter Notebook / Run from CLI
    parser = argparse.ArgumentParser(
                    prog='sol08pr02',
                    description='Solves Problem 2 as described',
                    )

    parser.add_argument('nums', type=float, nargs=2,
                        help='stores 2 numbers, x and y')
    args = parser.parse_args()
    
    # Retrieve x,y from CLI
    x,y = args.nums
    
    # Check for x,y != 0
    if (x == 0.0) or (y == 0.0):
        raise AssertionError(f"Inputs must be non zero! x={x}, y={y}")
    
    # Make values into arrays to send
    x = np.array(x)
    y = np.array(y)
    
    # Send y to Process 1
    comm.Send(y, dest=1)
        
    # Mulitply p * x, send to Process 1
    for i in range(5):
        p *= x
        print(f"Sending message {i}, p={p}")
        comm.Send(p, dest=1)
        comm.Recv(p, source=1)
    print(f"Final Value of p={p[0]}")
    
        
# Process 1 Logic
if rank == 1:
    
    # Receive y from Process 0
    y = np.ones(1)
    comm.Recv(y, source=0)
    
    # Receive p from Process 0
    for i in range(1,10,2):
        comm.Recv(p, source=0)
        
        # Divide p by y
        p /= y
        # Send back to Process 0
        print(f"Sending message {i}, p={p}")
        comm.Send(p,dest=0)
