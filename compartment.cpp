#include "compartment.hpp"
#include <iostream>

Compartment::Compartment(){
}

Compartment::Compartment(const int size, RandDrivers* inGenerator, double infectiousScaling) : randDrivers(inGenerator) , stateMap( StateMap({{"Uninfected", 0}, {"Infected", 1}, {"Infectious", 2}, {"Recovered", 3}})), infectiousScaling(infectiousScaling)  {
    currentAgentSet.resize(size);
};

void Compartment::initializeCompartment(){
}

void Compartment::setCurrentTime(const int currentTime){
    this->currentTime = currentTime;
}

int Compartment::getCurrentTime(){
    return this->currentTime;
}

double Compartment::getInfectiousScaling(){
    return this->infectiousScaling;
}

void Compartment::setInfectiousScaling(double inValue){
    this->infectiousScaling = inValue;
}

std::valarray<int> Compartment::getStateCounts(){
    std::valarray<int> sumCounts(0, this->stateMap.size());
    for(auto currentAgent: this->currentAgentSet){
        sumCounts[currentAgent->getState()]++;
    }
    return sumCounts;
}

void Compartment::infectionCycle(){
    for(auto currentAgent: this->currentAgentSet){
        switch(currentAgent->getState()){
            case 1:
            {
                if(currentAgent->checkForInfectious(this->currentTime) ){
                    int recoveryTime = this->currentTime+this->randDrivers->RecoveryTimeGenerator();
                    currentAgent->becomeInfectious(recoveryTime, this->stateMap.at("Infectious"));
                }
            }
            break;
            case 2:
            {   
                for(auto targetAgent: currentAgentSet){
                    if(targetAgent->getState()==this->stateMap.at("Uninfected") && currentAgent->checkToInfect(targetAgent,this->randDrivers->InfectionCheckGenerator()) ){
                        int infectiousTime = this->currentTime+this->randDrivers->InfectiousTimeGenerator();
                        double infectiousStrength = this->randDrivers->InfectiousStrengthGenerator()*this->infectiousScaling;
                        targetAgent->getInfected(infectiousTime, infectiousStrength, this->stateMap.at("Infected"));
                    }
                }
                if(currentAgent->checkForRecovery(this->currentTime)){
                    currentAgent->changeState("Recovered",this->stateMap);
                }
            }
            break;
            default:
            break;
        }
    }
}

