.PHONY: default main mpi clean

MPI_ENTRY := mainMPI.cpp
MPI_SRC := OpenMPISieve.cpp
SRC := $(filter-out $(MPI_ENTRY), $(wildcard *.cpp))
FLAGS := -std=c++17 -O3

default: main mpi

main:
	mpiCC $(FLAGS) $(SRC) -o sieve -fopenmp

mpi:
	mpiCC $(FLAGS) $(MPI_SRC) $(MPI_ENTRY) -o mpisieve

clean:
	rm -rf sieve mpisieve
