import os
import numpy as np
import matplotlib.pyplot as plt

ARRAY_SIZE = 10
N_STATES = 5
N_ITERATIONS = 10000
SAMPLE_SIZE = N_ITERATIONS/10

COMPILE_CMD = 'g++ -std=c++11 -Wall -Werror src/main.cpp -o runner'
RUN_CMD = 'runner.exe {} {} {}'.format(ARRAY_SIZE, N_STATES, N_ITERATIONS)
DEL_CMD = 'del runner.exe' # for Windows

LOG_PATH = 'resource/_log.txt'
WEIGHT_PATH = 'resource/_weights.txt'

BAR_CHART_PATH = 'resource/weights_on_states.png'
LINE_PLOT_PATH = 'resource/calls_over_time.png'

class State:
    def __init__(self, id:int, n_calls:int) -> None:
        self.__id = id
        self.__n_calls = n_calls

    def __hash__(self) -> int:
        return self.__id

    def __eq__(self, __o: object) -> bool:
        return isinstance(__o, type(self)) and self.__id == __o.get_id()

    def get_id(self):
        return self.__id

    def get_n_calls(self): 
        return self.__n_calls


def run_simulation() -> None:
    os.system(COMPILE_CMD)
    os.system(RUN_CMD)
    os.system(DEL_CMD)


def read_log(file_path, sample_size):
    samples = list()

    with open(file_path, 'r') as file:
        sample = list()

        for line in file:
            src, dst = line.rstrip("\n").split("-->")
            transition = {"src": int(src), "dst": int(dst)}
            sample.append(transition)

            if len(sample) == sample_size:
                samples.append(sample)
                sample = list()

    return samples


def read_weight(file_path):
    states = set()

    with open(file_path) as file:
        for line in file:
            state_id, n_calls = line.rstrip("\n").split("\t")
            states.add(State(int(state_id), int(n_calls)))
    
    return states
            

def visualize_weights(states, file_path):
    state_ids = list()
    state_n_calls = list()
    for state in states:
        state_ids.append(state.get_id())
        state_n_calls.append(state.get_n_calls())

    plt.figure(figsize=(16,9))

    plt.stem(state_ids,
             state_n_calls,
             basefmt=" ")

    plt.xticks(state_ids,
               ['State#{}'.format(state_id) for state_id in state_ids],
               rotation=60)

    plt.savefig(file_path)


def visualize_over_time(samples, file_path):
    plt.figure(figsize=(16,9))

    for state in states:
        calls_in_time = list()

        for sample in samples:
            calls_in_sample = 0

            for transition in sample:
                if transition['dst'] == state.get_id():
                    calls_in_sample = calls_in_sample + 1
                    
            calls_in_time.append(calls_in_sample)
        
        plt.plot(np.arange(len(samples)), 
                 calls_in_time,
                 label='State#{}'.format(state.get_id()))

    plt.yscale('log')
    plt.legend()
    plt.savefig(file_path)


if __name__ == "__main__":
    run_simulation()
    states = read_weight(WEIGHT_PATH)
    samples = read_log(LOG_PATH, SAMPLE_SIZE)
    visualize_weights(states, BAR_CHART_PATH)
    visualize_over_time(samples, LINE_PLOT_PATH)
