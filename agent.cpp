#include "agent.hpp"

Agent::Agent(int globalIndex, int state = 0) : globalIndex{globalIndex}, state{state}, infectiousIndex(0), position{std::make_tuple(0,0)}, timeToRecover(0), timeToInfectious(0) {
    this->stateMap = {{"Uninfected", 0}, {"Infected", 1}, {"Infectious", 2}, {"Recovered", 3}};
};

int Agent::getGlobalIndex(){
    return this->globalIndex;
}

int Agent::getState(){
    return this->state;
}

void Agent::changeState(std::string targetState){
    this->state = this->stateMap.at(targetState);
}