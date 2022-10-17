#include "city.hpp"

#include <fstream>

City::City(const int endT, std::ofstream* outStream) : endT(endT){
    this->ioHandle=IOHandler(outStream);
    this->compartmentList.resize(0);
};

void City::runSimulation(){
    for(int currentTime=0;currentTime<this->endT;++currentTime){
        std::valarray<int> cumulativeCount(0,4);
        for(auto currentCompartment: this->compartmentList){
            currentCompartment.setCurrentTime(currentTime);
            currentCompartment.infectionCycle();
            cumulativeCount+=currentCompartment.getStateCounts();
        }
        this->ioHandle.writeState(this->compartmentList);
    }
}