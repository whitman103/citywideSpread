CXX = clang++ 
CXXFLAGS = -O2 -std=c++17 -I/opt/homebrew/include

all: city compartment agent driver

agent: agent.cpp
	$(CXX) $(CXXFLAGS) -c agent.cpp

compartment: agent.o
	$(CXX) $(CXXFLAGS) -c compartment.cpp

city: compartment.o io.o
	$(CXX) $(CXXFLAGS) -c city.cpp

driver: agent.o compartment.o io.o city.o
	$(CXX) $(CXXFLAGS) -o driver driver.cpp agent.cpp compartment.cpp city.cpp

clean:
	rm driver driver.o compartment.o driver driver.o