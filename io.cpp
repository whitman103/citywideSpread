#include "io.hpp"
#include <iostream>

IOHandler::IOHandler(){
}

IOHandler::IOHandler(std::ofstream* outStream): outputStream(outStream) {
}

IOHandler::~IOHandler(){
    (*this->outputStream).close();
}

void IOHandler::initStateOutputs(Compartment inputCompartment){
    (*this->outputStream)<<"Time ";
    for(int printIndex = 0 ; printIndex<inputCompartment.stateMap.size();++printIndex){
        for(auto val: inputCompartment.stateMap){
            if(val.second==printIndex){
                (*this->outputStream)<<val.first<<" ";
            }
        }
    }
    (*this->outputStream)<<'\n';
}

void IOHandler::writeState(Compartment inputCompartment){
    std::valarray<int> currentState = inputCompartment.getStateCounts();
    (*this->outputStream)<<inputCompartment.getCurrentTime()<<" ";
    for(auto val: currentState){
        (*this->outputStream)<<val<<" ";
    }
    (*this->outputStream)<<'\n';
}

void IOHandler::writeState(std::vector<Compartment> setOfCompartments){
    std::valarray<int> stateVector(setOfCompartments[0].stateMap.size(),0);
    std::cout<<"This is happening"<<std::endl;
    (*this->outputStream)<<setOfCompartments[0].getCurrentTime()<<" ";
    std::cout<<setOfCompartments[0].getCurrentTime()<<std::endl;
    for(auto iterCompartment: setOfCompartments){
        stateVector+=iterCompartment.getStateCounts();
    }
    (*this->outputStream)<<'\n';
}