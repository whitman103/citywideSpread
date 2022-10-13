#include "agent.hpp"
#include <cmath>
#include <iostream>

Agent::Agent(int globalIndex, int state = 0) : globalIndex{globalIndex}, state{state}, infectiousStrength(0), position{std::make_tuple(0,0)}, timeToRecover(0), timeToInfectious(0) {
};

int Agent::getGlobalIndex(){
    return this->globalIndex;
}

int Agent::getState(){
    return this->state;
}

void Agent::changeState(std::string targetState, StateMap inStateMap){
    this->state = inStateMap.at(targetState);
}

void Agent::getInfected(const int timeToInfectious, const double infectiousStrength, const int newState){
    this->timeToInfectious = timeToInfectious;
    this->infectiousStrength = infectiousStrength;
    this->state=newState;
}

void Agent::becomeInfectious(const int timeToRecovery, const int newState){
    this->timeToRecover = timeToRecovery;
    this->state = newState;
}

bool Agent::checkForInfectious(const int currentTime){
    return this->timeToInfectious < currentTime ? true : false;
}

bool Agent::checkToInfect(std::shared_ptr<Agent> targetAgent, double randPull = 1){
    double infectionProb = exp(-1.*targetAgent->immuneStrength)*tanh(this->infectiousStrength);
    std::cout<<infectionProb<<" "<<randPull<<std::endl;
    return infectionProb>randPull;
}

void Agent::setInfectiousStrength(const double inValue){
    this->infectiousStrength = inValue;
}

void Agent::setRecoveryTime(const int inValue){
    this->timeToRecover = inValue;
}

int Agent::getRecoveryTime(){
    return this->timeToRecover;
}

void Agent::setInfectiousTime(const int inValue){
    this->timeToInfectious = inValue;
}

bool Agent::checkForRecovery(const int currentTime){
    return this->timeToRecover< currentTime ? true : false;
}