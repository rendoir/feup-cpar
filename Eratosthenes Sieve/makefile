.PHONY: default main mpi clean

MPI := OpenMPISieve.cpp
SRC := $(filter-out $(MPI), $(wildcard *.cpp))
FLAGS := -std=c++17 -O3

default: main mpi

main:
	g++ $(FLAGS) $(SRC) -o sieve -fopenmp

mpi:
	mpiCC $(FLAGS) $(MPI) -o mpisieve

clean:
	rm -rf sieve mpisieve
