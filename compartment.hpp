#ifndef COMPARTMENT_HPP
#define COMPARTMENT_HPP


#include <vector>
#include <memory>
#include <map>
#include <string>

using StateMap = std::map<std::string,int>;

#include "agent.hpp"
#include "randDrivers.hpp"

class Compartment{
    private:
    int currentTime;
    RandDrivers* randDrivers;
    double infectiousScaling;

    public:
    void setCurrentTime(const int currentTime);
    double getInfectiousScaling();
    void setInfectiousScaling(double inValue);
    std::vector<std::shared_ptr<Agent> > currentAgentSet;
    Compartment(const int size, RandDrivers* randDrivers);
    const StateMap stateMap;

    void infectionCycle();
};

#endif