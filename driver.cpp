#include <iostream>
#include <memory>



#include "agent.hpp"
#include "compartment.hpp"


int main(){

    auto testAgent = std::make_shared<Agent>(10,0);

    testAgent->changeState("Infected");

    std::cout<<testAgent->getState()<<std::endl;

    return 0;
}