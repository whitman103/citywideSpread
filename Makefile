CXX = clang++ 
CXXFLAGS = -g -O2 -std=c++17 -I/opt/homebrew/include

all: driver agent compartment

driver: compartment.o agent.o compartment.cpp agent.cpp 
	$(CXX) $(CXXFLAGS) -o driver driver.cpp compartment.cpp agent.cpp

agent:
	$(CXX) $(CXXFLAGS) -c agent.cpp

compartment: compartment.o agent.o
	$(CXX) $(CXXFLAGS) -c compartment.cpp agent.hpp randDrivers.hpp

clean:
	rm driver.o compartment.o driver driver.o