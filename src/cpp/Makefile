CXXFLAGS = -std=c++20 -O2 -march=native -DNDEBUG -isystem /usr/include/eigen3

bin/main: build/main.o build/graph.o
	mkdir -p bin
	$(CXX) build/main.o build/graph.o -o bin/main

build/main.o: main.cpp graph.hpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

build/graph.o: graph.cpp graph.hpp
	mkdir -p build
	$(CXX) $(CXXFLAGS) -c graph.cpp -o build/graph.o

clean:
	rm -rf bin build
