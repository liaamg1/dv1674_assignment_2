# Author: David Holmqvist <daae19@student.bth.se>

CXX=g++
CXXFLAGS=-std=c++17 -O2 -g -Wunused -Wall

.PHONY: all clean

all: pearson pearson_par verify

pearson: vector.o dataset.o analysis.o sequential/pearson.cpp sequential/analysis.hpp sequential/dataset.hpp sequential/vector.hpp
	$(CXX) $(CXXFLAGS) sequential/pearson.cpp vector.o dataset.o analysis.o -o pearson

analysis.o: sequential/analysis.hpp sequential/analysis.cpp sequential/vector.hpp
	$(CXX) $(CXXFLAGS) -c sequential/analysis.cpp -o analysis.o

dataset.o: sequential/dataset.hpp sequential/dataset.cpp sequential/vector.hpp
	$(CXX) $(CXXFLAGS) -c sequential/dataset.cpp -o dataset.o

vector.o: sequential/vector.hpp sequential/vector.cpp
	$(CXX) $(CXXFLAGS) -c sequential/vector.cpp -o vector.o

# Separate object files prevent mixing sequential and parallel code.
pearson_par: vector_par.o dataset_par.o analysis_par.o parallel/pearson.cpp parallel/analysis.hpp parallel/dataset.hpp parallel/vector.hpp
	$(CXX) $(CXXFLAGS) -pthread parallel/pearson.cpp vector_par.o dataset_par.o analysis_par.o -o pearson_par

analysis_par.o: parallel/analysis.hpp parallel/analysis.cpp parallel/vector.hpp
	$(CXX) $(CXXFLAGS) -pthread -c parallel/analysis.cpp -o analysis_par.o

dataset_par.o: parallel/dataset.hpp parallel/dataset.cpp parallel/vector.hpp
	$(CXX) $(CXXFLAGS) -pthread -c parallel/dataset.cpp -o dataset_par.o

vector_par.o: parallel/vector.hpp parallel/vector.cpp
	$(CXX) $(CXXFLAGS) -pthread -c parallel/vector.cpp -o vector_par.o

verify: verify.c
	$(CC) verify.c -o verify

clean:
	rm -f pearson pearson_par verify
	rm -f vector.o dataset.o analysis.o vector_par.o dataset_par.o analysis_par.o
