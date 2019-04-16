#include "OpenMPISieve.h"

#include <mpi.h>
#include <iostream>

using namespace std;

//Odd-only parallel (OpenMPI) sieve of Eratosthenes
bool* OpenMPISieveOfEratosthenes::run(long long n) 
{
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    long long blockSize;
    long long lowerBound;
    long long upperBound;

    if( rank == 0 ) {
        blockSize = n/size;
        lowerBound = (n/size)*rank + 2;
        upperBound = lowerBound + blockSize - 2;
    } else {
        blockSize = n/size;
        lowerBound = (n/size)*rank;
        upperBound = lowerBound + blockSize;
    }

    bool *primes = new bool[blockSize];
    fill_n(primes, blockSize, true);
  
    for (int p=lowerBound; p*p<=upperBound; p++) 
        if (primes[p - lowerBound]) 
            for (int i=p*p; i<=upperBound; i += p) 
                primes[i - lowerBound] = false; 
  
    // Print all prime numbers 
    cout << "----- " << rank << " -----" << endl;
    for (int p=0; p < blockSize; p++) 
       if (primes[p]) 
          cout << p + lowerBound << " ";
    cout << endl;

    return primes;
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
    
	long long n = atoll(argv[1]);
	OpenMPISieveOfEratosthenes::run(n);

	MPI_Finalize();

	return 0;
}
