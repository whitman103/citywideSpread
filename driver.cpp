#include <iostream>
#include <memory>
#include <chrono>



#include "agent.hpp"
#include "compartment.hpp"
#include "randDrivers.hpp"
#include "io.hpp"
#include "city.hpp"


int main(){


    boost::mt19937 baseRNG(time(NULL));
    boost::uniform_real<> standardUniform(0,1);
    boost::uniform_real<> immuneStrengh(0,0.1);

    boost::uniform_int<> recoveryTime(1,4);
    boost::uniform_int<> infectiousTime(1,3);
    
    //Make the generators not use the same RNG eventually. 
    RandDrivers randDrivers = {RealGenerator(baseRNG, standardUniform), IntGenerator(baseRNG, recoveryTime), IntGenerator(baseRNG, infectiousTime), RealGenerator(baseRNG,standardUniform)};

    boost::uniform_int<> compartmentSize(40,80);
    IntGenerator compartmentSizeGenerator(baseRNG,compartmentSize);

    RealGenerator immuneStrenghGenerator(baseRNG, immuneStrengh);

    std::vector<std::shared_ptr<Agent>> AgentPool;
    
    const int totalAgentNumber(10000);
    AgentPool.resize(totalAgentNumber);
    for(int i=0;i<(int)AgentPool.size();++i){
        AgentPool[i]=std::make_shared<Agent>(i,0,immuneStrenghGenerator());
    }

    const double globalInfectiousStrength(0.05);


    std::ofstream reportStream("NotConnected.txt");
    City simCity = City(25,&reportStream);

    int currentAgentOffset(0);
    while(currentAgentOffset<AgentPool.size()){
        int agentAdd(compartmentSizeGenerator());
        if((agentAdd+currentAgentOffset)>totalAgentNumber){
            agentAdd = totalAgentNumber-currentAgentOffset;
        }
        Compartment newCompartment = Compartment(agentAdd,&randDrivers,globalInfectiousStrength);
        newCompartment.setInfectiousScaling(globalInfectiousStrength);
        newCompartment.currentAgentSet.resize(agentAdd);
        for(int j=0;j<agentAdd;++j){
            newCompartment.currentAgentSet[j]=AgentPool[j+currentAgentOffset];
        }
        simCity.compartmentList.push_back(newCompartment);
        currentAgentOffset+=agentAdd;
    }

    double initialInfectionFraction(0.05);
    
    // Sloppy interobject working right now
    
    simCity.ioHandle.initStateOutputs(simCity.compartmentList[0]);

    for(auto& curCompartment: simCity.compartmentList){
        curCompartment.currentAgentSet[0]->getInfected(randDrivers.InfectiousTimeGenerator(),globalInfectiousStrength,1);
    }


    simCity.runSimulation();
    reportStream.close();
    
    

    return 0;
}