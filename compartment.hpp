#ifndef COMPARTMENT_HPP
#define COMPARTMENT_HPP


#include <vector>
#include <memory>

#include "agent.hpp"

class Compartment{
    public:
    std::vector<std::shared_ptr<Agent> > currentAgentSet;
    Compartment(const int size);

};

#endif