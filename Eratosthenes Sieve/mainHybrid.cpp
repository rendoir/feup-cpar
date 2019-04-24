#include "HybridSieve.h"
#include <mpi.h>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

	unsigned long long exponent = atoll(argv[1]);
	int threads = atoi(argv[2]);
    HybridSieveOfEratosthenes::run(exponent, threads);

	MPI_Finalize();

	return 0;
}