#include <iostream>
#include <memory>
#include <chrono>



#include "agent.hpp"
#include "compartment.hpp"
#include "randDrivers.hpp"
#include "io.hpp"


int main(){


    boost::mt19937 baseRNG(time(NULL));
    boost::uniform_real<> standardUniform(0,1);

    boost::uniform_int<> recoveryTime(1,4);
    boost::uniform_int<> infectiousTime(1,3);
    
    //Make the generators not use the same RNG eventually. 
    RandDrivers randDrivers = {RealGenerator(baseRNG, standardUniform), IntGenerator(baseRNG, recoveryTime), IntGenerator(baseRNG, infectiousTime), RealGenerator(baseRNG,standardUniform)};

    IOHandler outputFile = IOHandler("visualization/test.txt");

    Compartment testCompartment = Compartment(200, &randDrivers);
    testCompartment.setInfectiousScaling(0.05);
    outputFile.initStateOutputs(testCompartment);

    for(int i = 0 ; i <testCompartment.currentAgentSet.size();++i){
        testCompartment.currentAgentSet[i]=std::make_shared<Agent>(i,0);
    }

    double initialInfectionFraction(0.05);
    int numInitInfections(testCompartment.currentAgentSet.size()*initialInfectionFraction);
    for(int initInfect = 0; initInfect<numInitInfections;++initInfect){
        testCompartment.currentAgentSet[initInfect]->changeState("Infected",testCompartment.stateMap);
        testCompartment.currentAgentSet[initInfect]->setInfectiousTime(randDrivers.InfectiousTimeGenerator());
        testCompartment.currentAgentSet[initInfect]->setInfectiousStrength(testCompartment.getInfectiousScaling()*randDrivers.InfectionCheckGenerator());
    }
    
    
    for(int timeCycle = 0 ;timeCycle<25;timeCycle++){
        testCompartment.setCurrentTime(timeCycle);
        testCompartment.infectionCycle();
        outputFile.writeState(testCompartment);
    }

    return 0;
}