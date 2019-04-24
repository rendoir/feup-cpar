.PHONY: default main mpi clean

MPI_ENTRY := mainMPI.cpp
MPI_SRC := OpenMPISieve.cpp

HYBRID_ENTRY := mainHybrid.cpp
HYBRID_SRC := HybridSieve.cpp

SRC := $(filter-out $(MPI_ENTRY) $(HYBRID_ENTRY), $(wildcard *.cpp))
FLAGS := -std=c++17 -O3

default: main mpi hybrid

main:
	mpiCC $(FLAGS) $(SRC) -o sieve -fopenmp

mpi:
	mpiCC $(FLAGS) $(MPI_SRC) $(MPI_ENTRY) -o mpisieve

hybrid: 
	mpiCC $(FLAGS) $(HYBRID_SRC) $(HYBRID_ENTRY) -o hybridsieve -fopenmp

clean:
	rm -rf sieve mpisieve
