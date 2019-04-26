#include "OpenMPISieve.h"
#include "Utils.h"
#include <mpi.h>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

	unsigned long long exponent = atoll(argv[1]);
	Parameters::automatic = argc > 2;
	Parameters::current_exponent = exponent;
    OpenMPISieveOfEratosthenes::run(exponent);

	MPI_Finalize();

	return 0;
}