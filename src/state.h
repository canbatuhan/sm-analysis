#include <iostream>
#include <vector>
#include <time.h>

#ifndef STATE_H
#define STATE_H

using namespace std;

/**
 * @brief State data type
 * 
 */
class State {
    private:
        int id;
        int numberOfCalls;
        vector<State> statesToCall;

    public:
        State() {
            this->id = -1;
            this->numberOfCalls = 0;
            this->statesToCall = vector<State>();
        }

        State(int id) {
            this->id = id;
            this->numberOfCalls = 0;
            this->statesToCall = vector<State>();
        }

        ~State() {
            this->statesToCall.clear();
        }

        void generateStatesToCall(int size, int nStates) {
            int rand_id;
            for (int index=0; index<nStates; index++) {
                rand_id = rand()%size;
                this->statesToCall.push_back(State(rand_id));
            }
        }

        int getID() {
            return this->id;
        }

        int getNumberOfCalls() {
            return this->numberOfCalls;
        }

        vector<State> getStatesToCall() {
            return this->statesToCall;
        }

        void incrementNumberOfCalls() {
            this->numberOfCalls++;
        }

};

#endif
