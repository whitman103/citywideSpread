#include <iostream>
#include <memory>



#include "agent.hpp"
#include "compartment.hpp"
#include "randDrivers.hpp"


int main(){


    boost::mt19937 baseRNG(0);
    boost::uniform_real<> standardUniform(0,1);

    boost::uniform_int<> recoveryTime(0,4);
    boost::uniform_int<> infectiousTime(0,3);
    
    //Make the generators not use the same RNG eventually. 
    RandDrivers randDrivers = {RealGenerator(baseRNG, standardUniform), IntGenerator(baseRNG, recoveryTime), IntGenerator(baseRNG, infectiousTime)};

    Compartment testCompartment = Compartment(10, &randDrivers);

    for(int i = 0 ; i <testCompartment.currentAgentSet.size();++i){
        testCompartment.currentAgentSet[i]=std::make_shared<Agent>(i,0);
    }
    testCompartment.currentAgentSet[1]->changeState("Infectious",testCompartment.stateMap);
    testCompartment.currentAgentSet[1]->setInfectiousStrength(0.01);
    testCompartment.infectionCycle();

    for(int i=0;i<testCompartment.currentAgentSet.size();++i){
        std::cout<<testCompartment.currentAgentSet[i]->getState()<<std::endl;
    }

    return 0;
}