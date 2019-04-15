#include "OpenMPSieve.h"

#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;


//Odd-only parallel (OpenMP) sieve of Eratosthenes
bool* OpenMPSieveOfEratosthenes::run(long long n, unsigned int threads) 
{
    bool *primes = new bool[n/2];
    long long k = 3;

    omp_set_num_threads(threads);

    do {
        #pragma omp parallel for
        for (long long j = k*k ; j<n ; j+=2*k)
            primes[j>>1]=true;
        
        do {
            k+=2;
        } while (k*k <= n && primes[k>>1]);
        
    } while (k*k <= n);

    return primes;
}

void OpenMPSieveOfEratosthenes::test()
{  
    long long n = 0;
    unsigned int threads = 0;
    bool* primes;

    while(n <= 0) {
        cout << "Upper bound: ";
        cin >> n;
    }

    while(threads == 0 || threads > omp_get_max_threads()) {
        cout << "Threads: ";
        cin >> threads;
    }

    primes = run(n, threads);
    
    long long n_primes = n > 2 ? 2 : n > 1 ? 1 : 0;
    cout << (n > 2 ? "1 2 " : n > 1 ? "1 " : "");
    for (int i=3; i<n; i+=2)
        if (!primes[i>>1]) {
            n_primes++;
            cout << i << " ";
        }
    cout << endl << "Found " << n_primes << " prime numbers" << endl;
}
