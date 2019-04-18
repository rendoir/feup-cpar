.PHONY: default main mpi clean

MPI := OpenMPISieve.cpp
MPMPI := OpenMPMPISieve.cpp
SRC := $(filter-out $(MPI), $(wildcard *.cpp))

default: main mpi

main:
	g++ -std=c++17 -O3 $(SRC) -o sieve -fopenmp

mpi:
	mpiCC $(MPI) -o mpisieve

mpmpi:
	mpic++ -o mpmpisieve $(MPMPI) -fopenmp

clean:
	rm -rf sieve mpisieve
