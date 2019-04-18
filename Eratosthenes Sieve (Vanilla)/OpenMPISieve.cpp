#include "OpenMPISieve.h"

#include <mpi.h>
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

void OpenMPISieveOfEratosthenes::run(long long exponent) 
{
	unsigned long counter = 0, nr_primes = 0, n = pow(2, exponent);

    int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	unsigned long block_size = BLOCK_SIZE(rank, n - 1, size);
	unsigned long lower_bound = BLOCK_LOW(rank, n - 1, size) + 2;
	unsigned long upper_bound = BLOCK_HIGH(rank, n - 1, size) + 2;

	bool* marking = new bool[block_size];
    fill_n(marking, block_size, true);

    double run_time = 0;
	if(IS_ROOT(rank)) {
		cout << size << ";" << n << ";" << exponent << ";";
		run_time = MPI_Wtime();
	}

    unsigned long start_value, k = 2;
	do {
		//Antecipate uneven block size allocation and calculate offset if necessary
		if (k*k < lower_bound)
            start_value = (lower_bound % k == 0 ? lower_bound : lower_bound + (k - (lower_bound % k)));
        else
			start_value = k*k;

		for (unsigned long i = start_value; i <= upper_bound; i += k)
			marking[i - lower_bound] = false;

		if (IS_ROOT(rank)) {
			do {
				k++;
			} while (!marking[k - lower_bound] && k*k < upper_bound);
		}

		MPI_Bcast(&k, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	}while(k*k <= n);

	if(IS_ROOT(rank)) {
		run_time = MPI_Wtime() - run_time;
		cout << run_time << ";";
	}

	for (unsigned long i = 0; i < block_size; i++)
		if (marking[i])
			counter++;

	MPI_Reduce(&counter, &nr_primes, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0)
		cout << nr_primes << endl;

	free(marking);
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
    
	long long n = atoll(argv[1]);
	OpenMPISieveOfEratosthenes::run(n);

	MPI_Finalize();

	return 0;
}
