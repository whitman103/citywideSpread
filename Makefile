CXX = clang++ 
CXXFLAGS = -O2 -std=c++17 -I/opt/homebrew/include

all: driver agent compartment io

driver: compartment.o agent.o compartment.cpp agent.cpp 
	$(CXX) $(CXXFLAGS) -o driver driver.cpp compartment.cpp agent.cpp io.cpp

agent:
	$(CXX) $(CXXFLAGS) -c agent.cpp

compartment: compartment.o agent.o
	$(CXX) $(CXXFLAGS) -c compartment.cpp agent.hpp randDrivers.hpp

io: compartment.o
	$(CXX) $(CXXFLAGS) -c io.cpp compartment.hpp

clean:
	rm driver.o compartment.o driver driver.o