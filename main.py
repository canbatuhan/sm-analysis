import os
import numpy as np
import matplotlib.pyplot as plt


ARRAY_SIZE = 100
N_STATES = 20
N_ITERATIONS = 1000000


def run_simulation() -> None:
    os.system('g++ -std=c++11 -Wall -Werror src/main.cpp -o runner')
    os.system('runner.exe {} {} {}'.format(ARRAY_SIZE, N_STATES, N_ITERATIONS))
    os.system('del runner.exe')


if __name__ == "__main__":
    run_simulation()
