# Author: David Holmqvist <daae19@student.bth.se>

CXX=g++
CXXFLAGS=-std=c++17 -g -Wunused -Wall -Wunused

all: baseline_blur blur_optimization_threads

# baseline 
baseline_blur: matrix ppm filters baseline/blur.cpp
	$(CXX) $(CXXFLAGS) baseline/blur.cpp matrix.o ppm.o filters.o -o blur

filters: matrix baseline/filters.hpp baseline/filters.cpp
	$(CXX) $(CXXFLAGS) -c baseline/filters.cpp -o filters.o

matrix: baseline/matrix.hpp baseline/matrix.cpp
	$(CXX) $(CXXFLAGS) -c baseline/matrix.cpp -o matrix.o

ppm: baseline/ppm.hpp baseline/ppm.cpp
	$(CXX) $(CXXFLAGS) -c baseline/ppm.cpp -o ppm.o


# optimization_1
blur_optimization_one: matrix ppm filter_optimization_one optimization_1/blur.cpp
	$(CXX) $(CXXFLAGS) optimization_1/blur.cpp matrix.o ppm.o filters.o -o blur

filter_optimization_one: matrix optimization_1/filters.hpp optimization_1/filters.cpp
	$(CXX) $(CXXFLAGS) -c optimization_1/filters.cpp -o filters.o



# optimization_2
blur_optimization_two: matrix_optimization_two ppm_optimization_two filters_optimization_two optimization_2/blur.cpp
	$(CXX) $(CXXFLAGS) optimization_2/blur.cpp matrix.o ppm.o filters.o -o blur

filters_optimization_two: matrix_optimization_two optimization_2/filters.hpp optimization_2/filters.cpp
	$(CXX) $(CXXFLAGS) -c optimization_2/filters.cpp -o filters.o

matrix_optimization_two: optimization_2/matrix.hpp optimization_2/matrix.cpp
	$(CXX) $(CXXFLAGS) -c optimization_2/matrix.cpp -o matrix.o

ppm_optimization_two: optimization_2/ppm.hpp optimization_2/ppm.cpp
	$(CXX) $(CXXFLAGS) -c optimization_2/ppm.cpp -o ppm.o


# optimization_3
blur_optimization_three:matrix_optimization_two ppm_optimization_two filters_optimization_three optimization_2/blur.cpp
	$(CXX) $(CXXFLAGS) optimization_2/blur.cpp matrix.o ppm.o filters.o -o blur 

filters_optimization_three: matrix_optimization_two optimization_3/filters.hpp optimization_3/filters.cpp
	$(CXX) $(CXXFLAGS) -c optimization_3/filters.cpp -o filters.o


# optimization using pthreads 
blur_optimization_threads: matrix_optimization_two ppm_optimization_two filter_par optimization_threads/blur.cpp
	$(CXX) $(CXXFLAGS) optimization_threads/blur.cpp matrix.o ppm.o filters.o thread.o -o blur_par
threads_par: optimization_threads/Thread.hpp optimization_threads/Thread.cpp
	$(CXX) $(CXXFLAGS) -c optimization_threads/Thread.cpp -o thread.o

filter_par: matrix_optimization_two threads_par optimization_threads/filters.hpp optimization_threads/filters.cpp
	$(CXX) $(CXXFLAGS) -c optimization_threads/filters.cpp -o filters.o





clean:
	rm -rf blur blur_par *.ppm *.o *.dSYM 2> /dev/null


