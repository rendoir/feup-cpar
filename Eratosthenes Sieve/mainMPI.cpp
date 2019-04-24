#include "OpenMPISieve.h"
#include <mpi.h>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

	unsigned long long exponent = atoll(argv[1]);
    OpenMPISieveOfEratosthenes::run(exponent);

	MPI_Finalize();

	return 0;
}