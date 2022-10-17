#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include <string>

#include "compartment.hpp"
#include "io.hpp"

class City{

    private:
    const int endT;

    public:
    std::vector<Compartment> compartmentList;
    IOHandler ioHandle;
    City(const int endT, std::ofstream* outStream);

    void runSimulation();
};

#endif