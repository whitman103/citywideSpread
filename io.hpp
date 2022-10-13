#ifndef IO_HPP
#define IO_HPP

#include <vector>
#include <fstream>
#include <string>

#include "compartment.hpp"

class IOHandler{

    public:
    IOHandler(std::string streamName);
    ~IOHandler();
    void writeState(std::vector<Compartment> setOfCompartments);
    void writeState(Compartment inputCompartment);
    void initStateOutputs(Compartment inputCompartment);
    private:
    std::ofstream outputStream;
};

#endif