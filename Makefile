CXX = clang++ 
CXXFLAGS = -O2 -std=c++17 -I/opt/homebrew/include

all: driver agent compartment io city

agent: agent.cpp
	$(CXX) $(CXXFLAGS) -c agent.cpp

compartment: agent.o
	$(CXX) $(CXXFLAGS) -c compartment.cpp

io: compartment.o
	$(CXX) $(CXXFLAGS) -c io.cpp

city: compartment.o io.o
	$(CXX) $(CXXFLAGS) -c city.cpp

driver: agent.o compartment.o io.o city.o
	$(CXX) $(CXXFLAGS) -o driver driver.cpp agent.cpp compartment.cpp io.cpp city.cpp

clean:
	rm driver driver.o compartment.o driver driver.o