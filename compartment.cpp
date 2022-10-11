#include "compartment.hpp"
#include <iostream>

Compartment::Compartment(const int size, RandDrivers* inGenerator) : randDrivers(inGenerator) , stateMap( StateMap({{"Uninfected", 0}, {"Infected", 1}, {"Infectious", 2}, {"Recovered", 3}})) {
    currentAgentSet.resize(size);
};

void Compartment::setCurrentTime(const int currentTime){
    this->currentTime = currentTime;
}

void Compartment::infectionCycle(){
    for(auto currentAgent: currentAgentSet){
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
                std::cout<<"Happening"<<std::endl;
                for(auto targetAgent: currentAgentSet){
                    if(targetAgent->getState()==this->stateMap.at("Uninfected") && currentAgent->checkToInfect(targetAgent,0) ){
                        int infectiousTime = this->currentTime+this->randDrivers->InfectiousTimeGenerator();
                        double infectiousStrength = this->randDrivers->InfectiousStrengthGenerator();
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

