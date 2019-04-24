#include "OpenMPISieve.h"

#include <mpi.h>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

void OpenMPISieveOfEratosthenes::run(unsigned long long exponent) 
{
	unsigned long long n = pow(2, exponent);

    int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	unsigned long long block_size = BLOCK_SIZE(rank, (n-1)/2, size);
	unsigned long long lower_bound = 2*BLOCK_LOW(rank, (n-1)/2, size) + 3;
	unsigned long long upper_bound = 2*BLOCK_HIGH(rank, (n-1)/2, size) + 3;

	bool* marking = new bool[block_size];
    fill_n(marking, block_size, true);

    double run_time = 0;
	if(IS_ROOT(rank)) {
		run_time = MPI_Wtime();
	}

    unsigned long long start_value, k = 3;
	do {
		//Antecipate uneven block size allocation and calculate offset if necessary
		if (k*k < lower_bound) {
            start_value = (lower_bound % k == 0 ? lower_bound : lower_bound + (k - (lower_bound % k))); //Guarantee start value is a multiple of k
            start_value += (start_value % 2 == 0 ? k : 0); //Guarantee start value is an ODD multiple of k
        }
        else
			start_value = k*k;

		for (unsigned long long i = start_value; i <= upper_bound; i += 2*k)
			marking[(i - lower_bound)>>1] = false;

		if (IS_ROOT(rank)) {
			do {
				k += 2;
			} while (!marking[(k - lower_bound)>>1] && k*k < upper_bound);
		}

		MPI_Bcast(&k, 1, MPI_LONG, 0, MPI_COMM_WORLD);
	}while(k*k <= n);

	if(IS_ROOT(rank)) {
		run_time = MPI_Wtime() - run_time;
	}

	print(marking, block_size, rank, size, lower_bound, n, run_time);
	
	free(marking);
}

void OpenMPISieveOfEratosthenes::print(bool *marking, unsigned long long block_size, int rank, int size, unsigned long long lower_bound, unsigned long long n, double run_time) 
{
	unsigned long long counter = 0, nr_primes = 0;

	for (unsigned long long i = 0; i < block_size; i++)
        if (marking[i])
            counter++;

	MPI_Reduce(&counter, &nr_primes, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);                
	
	if(rank == 0) {
		if(n>=2) {
			nr_primes++;
			cout << "2" << endl;
		}
	}

	for ( unsigned long long i = 0; i < size; ++i ) {
		if ( rank == i ) {
			for (unsigned long long j = 0; j < block_size; j++)
				if(marking[j])
					cout << j*2 + lower_bound << " ";
			cout << endl;
		}
    	MPI_Barrier(MPI_COMM_WORLD);
	}

	if(rank == 0) {
		cout << "Run time: " << run_time << " seconds" << endl;
	    cout << "Found " << nr_primes << " prime numbers" << endl;
	}
}

int OpenMPISieveOfEratosthenes::test(int argc, char** argv)
{
	unsigned long long exponent = 0;
    int processes = 0;

	while(exponent <= 1) {
		cout << "Exponent: ";
		cin >> exponent;
    }

    while(processes <= 0) {
        cout << "Processes: ";
        cin >> processes;
    }

	string command = "mpirun -np " + to_string(processes) + " mpisieve " + to_string(exponent);

	return system(command.c_str());
}
