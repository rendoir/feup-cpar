.PHONY: default main mpi hybrid clean

MAIN_SRC := main.cpp
MPI_SRC := OpenMPISieve.cpp Utils.cpp
HYBRID_SRC := HybridSieve.cpp Utils.cpp

SRC := $(wildcard *.cpp)
FLAGS := -std=c++17 -O3

default: main mpi hybrid

main:
	mpiCC $(FLAGS) $(SRC) -o sieve -fopenmp

mpi:
	mpiCC $(FLAGS) $(MPI_SRC) $(MAIN_SRC) -DMPI_SIEVE -o mpisieve

hybrid: 
	mpiCC $(FLAGS) $(HYBRID_SRC) $(MAIN_SRC) -DHYBRID_SIEVE -o hybridsieve -fopenmp

clean:
	rm -rf sieve mpisieve hybridsieve
