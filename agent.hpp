#ifndef AGENT_HPP
#define AGENT_HPP


#include <vector>
#include <tuple>
#include <map>
#include <string>

using StateMap = std::map<std::string,int>;

class Agent{
    private:
    int state, globalIndex;
    StateMap stateMap;
    double infectiousIndex;

    public:
    int getGlobalIndex();
    int getState();
    std::tuple<int,int> position;
    Agent(int globalIndex, int state);
    void changeState(std::string targetState);
};

#endif