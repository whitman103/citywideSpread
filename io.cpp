#include "io.hpp"


IOHandler::IOHandler(std::string streamName){
    std::ofstream outFile(streamName);
    this->outputStream = std::move(outFile);
}

IOHandler::~IOHandler(){
    this->outputStream.close();
}

void IOHandler::initStateOutputs(Compartment inputCompartment){
    this->outputStream<<"Time ";
    for(int printIndex = 0 ; printIndex<inputCompartment.stateMap.size();++printIndex){
        for(auto val: inputCompartment.stateMap){
            if(val.second==printIndex){
                this->outputStream<<val.first<<" ";
            }
        }
    }
    this->outputStream<<'\n';
}

void IOHandler::writeState(Compartment inputCompartment){
    std::valarray<int> currentState = inputCompartment.getStateCounts();
    this->outputStream<<inputCompartment.getCurrentTime()<<" ";
    for(auto val: currentState){
        this->outputStream<<val<<" ";
    }
    this->outputStream<<'\n';
}

void IOHandler::writeState(std::vector<Compartment> setOfCompartments){
    std::valarray<int> stateVector(setOfCompartments[0].stateMap.size(),0);
    for(auto iterCompartment: setOfCompartments){
        stateVector+=iterCompartment.getStateCounts();
    }
}