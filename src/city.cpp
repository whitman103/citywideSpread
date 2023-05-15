#include "city.hpp"

#include <fstream>
#include <iostream>

City::City(const int endT, std::ofstream* streamName) : endT(endT), outStream(streamName) {
    this->compartmentList.resize(0);
};

City::~City(){
    (*this->outStream).close();
}

void City::runSimulation(){
    for(int currentTime=0;currentTime<this->endT;++currentTime){
        std::valarray<int> cumulativeCount(0,4);
        for(auto& currentCompartment: this->compartmentList){
            currentCompartment.setCurrentTime(currentTime);
            currentCompartment.infectionCycle();
        }
        this->writeState(this->compartmentList);
    }
}

void City::writeState(std::vector<Compartment> setOfCompartments){
    std::valarray<int> stateVector(0,setOfCompartments[0].stateMap.size());
    *(this->outStream)<<setOfCompartments[0].getCurrentTime()<<" ";
    for(auto iterCompartment: setOfCompartments){
        stateVector+=iterCompartment.getStateCounts();
    }
    for(auto val: stateVector){
        *(this->outStream)<<val<<" ";
    }
    *(this->outStream)<<'\n';
}

void City::writeState(Compartment inputCompartment){
    std::valarray<int> currentState = inputCompartment.getStateCounts();
    (*this->outStream)<<inputCompartment.getCurrentTime()<<" ";
    for(auto val: currentState){
        (*this->outStream)<<val<<" ";
    }
    (*this->outStream)<<'\n';
}

void City::initStateOutputs(Compartment inputCompartment){
    (*this->outStream)<<"Time ";
    for(int printIndex = 0 ; printIndex<inputCompartment.stateMap.size();++printIndex){
        for(auto val: inputCompartment.stateMap){
            if(val.second==printIndex){
                (*this->outStream)<<val.first<<" ";
            }
        }
    }
    (*this->outStream)<<'\n';
}