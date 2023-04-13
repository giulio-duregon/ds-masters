from mpi4py import MPI
import numpy as np

# Define the function to integrate
def f(x):
    return np.exp(-x)

# Define the range of integration
M = 1000.0

# Define the number of partitions and increments per partition
N = 16
n = 1000

# Compute the partition points
a = np.linspace(0, M, N+1)
b = a[1:]

# Initialize the MPI environment
comm = MPI.COMM_WORLD

# Get the rank and size of the current process
rank = comm.Get_rank()
size = comm.Get_size()

# Compute the integral over the local partition using the trapezoidal rule
h = (b - a) / n
x = np.linspace(a[rank], b[rank], n+1)
y = f(x) * x**rank
local_integral = h[rank] * (np.sum(y) - 0.5 * (y[0] + y[-1]))

# Sum up the local integrals over all processes
total_integral = comm.allreduce(local_integral, op=MPI.SUM)

# Print the result
if rank == 0:
    print("Integral of x^k f(x) from 0 to {}: {}".format(M, total_integral))

    # Compute the moments of the exponential distribution
    moments = [total_integral]
    for k in range(1, 15):
        moments.append(-k * moments[k-1])
    print("Moments of the exponential distribution: ", moments)
