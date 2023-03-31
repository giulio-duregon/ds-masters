import numpy as np
from functools import partial
from multiprocessing.pool import Pool
from time import time


def calculate_gamma_chunk(chunk):
    # sequential version to calculate Gamma(x):
    # where we approximate the given integral,
    # like this a discrete sum in number_of_steps
    # equidistant points on the interval [bound_1, bound_2]
    x, bound_1, bound_2, number_of_steps = chunk
    delta_x = (bound_2 - bound_1) / number_of_steps

    # initialize variables
    gamma_sum = 0
    current_x = bound_1

    # loop through equidistant points on the interval [bound_1, bound_2]
    for i in range(number_of_steps):
        # add contribution of current point to Gamma sum
        gamma_sum += np.exp(-current_x) * current_x ** (x - 1)

        # move to next point
        current_x += delta_x

    # multiply by step size to approximate integral
    gamma_approx = gamma_sum * delta_x

    return gamma_approx


def multiprocess_calculate_gamma(
    x, bound1, bound2, numsteps, NUM_PROCESSES, verbose=False
):
    # Start accounting
    ts = time()

    bound_increment = (bound2 - bound1) // NUM_PROCESSES
    num_steps_per_process = numsteps // NUM_PROCESSES

    arg_array = []
    # partial_gamma = partial(calculate_gamma)

    for i in range(NUM_PROCESSES):
        temp_start = bound1 + (i * bound_increment)
        temp_end = temp_start + bound_increment
        arg_array.append((x, temp_start, temp_end, num_steps_per_process))

    with Pool(NUM_PROCESSES) as pool:
        result = pool.map(calculate_gamma_chunk, arg_array)

    result_sum = sum(result)
    if verbose:
        from multiprocessing import cpu_count

        print("number of CPU cores:", cpu_count())
        print(f"Multiprocess Calculate Gamma with NUM_PROCESSES={NUM_PROCESSES}")
        print(f"Gamma(x) = {result_sum}, Total Time: {time()-ts}s")
