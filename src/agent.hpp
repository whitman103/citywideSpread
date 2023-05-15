#ifndef AGENT_HPP
#define AGENT_HPP

#include <ostream>
#include <vector>
#include <tuple>
#include <map>
#include <string>

using StateMap = std::map<std::string,int>;

class Agent{
    private:
    int state, globalIndex;
    double infectiousStrength, immuneStrength;
    int timeToRecover, timeToInfectious;

    public:
    const int getGlobalIndex();
    const int getState();
    void setInfectiousStrength(const double inValue);
    void setRecoveryTime(const int inValue);
    int getRecoveryTime();
    void setInfectiousTime(const int inValue);
    std::tuple<int,int> position;
    Agent(int globalIndex, int state);
    Agent(int globalIndex, int state, double immuneStrength);
    void changeState(std::string targetState, StateMap stateMap);
    void getInfected(const int timeToInfectious, const double infectiousStrength, const int newState);
    void becomeInfectious(const int timeToRecovery, const int newState);

    bool checkForInfectious(const int currentTime);
    bool checkToInfect(std::shared_ptr<Agent> targetAgent, double randPull);
    bool checkForRecovery(const int currentTime);
    friend std::ostream& operator<<(std::ostream& os, Agent& agent);
};


#endif