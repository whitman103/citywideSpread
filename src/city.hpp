#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include <string>

#include "compartment.hpp"

class City{

    private:
    const int endT;

    public:
    std::vector<Compartment> compartmentList;
    City(const int endT, std::ofstream* streamName);
    std::ofstream* outStream;
    void writeState(std::vector<Compartment> setOfCompartments);
    void writeState(Compartment inputCompartment);
    void initStateOutputs(Compartment inputCompartment);

    ~City();

    void runSimulation();
};

#endif