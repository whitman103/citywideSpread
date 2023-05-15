CXX = clang++ 
CXXFLAGS = -O2 -std=c++17 -I/opt/homebrew/include

default: all

all: city compartment agent driver

agent.o: agent.cpp
	$(CXX) $(CXXFLAGS) -c agent.cpp agent.o

compartment.o: agent.o
	$(CXX) $(CXXFLAGS) -c compartment.cpp agent.o -o compartment.o

city.o: compartment
	$(CXX) $(CXXFLAGS) -c city.cpp compartment.o -o city.o

driver: agent.o compartment.o city.o
	$(CXX) $(CXXFLAGS) -o driver driver.cpp agent.o compartment.o city.o

clean:
	rm driver compartment.o driver driver.o