#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "state.h"

#define LOG_PATH "resource/_log.txt"
#define WEIGHTS_PATH "resource/_weights.txt"

using namespace std;


/**
 * @brief Create array of States which are the components
 * of the state machine
 * 
 * @param size size of the state array
 * @param nStates states can call n different states at most
 * @return vector<State> array of state
 */
vector<State> createArray(int size, int nStates) {
    vector<State> arr;
    string stateID;
    State newState;

    for (int index=0; index<size; index++) { 
        State newState(index);
        newState.generateStatesToCall(size, nStates);
        arr.push_back(newState);
    }

    return arr;
}


/**
 * @brief Simulates the transitions in state machine flow
 * 
 * @param arr states of the state machine
 * @param nStates states can call n different states at most
 * @param nIterations produce n lines of log
 * @param filePath file to write the log
 */
void simulateAndLog(vector<State>& arr, int nStates, int nIterations, string filePath) {
    int sourceIndex;
    int destIndex;
    int destID;

    fstream outFile;
    outFile.open(filePath, fstream::out);

    sourceIndex = rand() % arr.size();
    for (int iteration=0; iteration<nIterations; iteration++) {
        destIndex = rand() % nStates;

        destID = arr[sourceIndex].getStatesToCall()[destIndex].getID();
        arr[destID].incrementNumberOfCalls();

        outFile << arr[sourceIndex].getID() << "-->" << arr[destID].getID() << endl;
        sourceIndex = destID;
    }
}



/**
 * @brief Write the workload on the states of a state machine
 * 
 * @param arr states of the state machine
 * @param filePath file to write
 */
void writeWeights(vector<State>& arr, string filePath) {
    fstream outFile;
    outFile.open(filePath, fstream::out);

    for (State state : arr) {
        outFile << state.getID() << "\t" << state.getNumberOfCalls() << endl;
    }

    outFile.close();
}


/**
 * @brief Main program
 * 
 * @param argc number of arguments
 * @param argv arguments as string
 * @return int success or failure
 */
int main(int argc, char** argv) {
    srand(time(NULL));
    
    int size = 50;
    int nStates = 10;
    int nIterations = 100000;

    if (argc == 4) {
        size = stoi(argv[1]);
        nStates = stoi(argv[2]);
        nIterations = stoi(argv[3]);
    }

    
    vector<State> stateArr = createArray(size, nStates);
    simulateAndLog(stateArr, nStates, nIterations, LOG_PATH);
    writeWeights(stateArr, WEIGHTS_PATH);
    stateArr.clear();

    return 0;
}
