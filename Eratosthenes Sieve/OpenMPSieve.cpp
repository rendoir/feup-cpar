#include "OpenMPSieve.h"

#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;


//Odd-only parallel (OpenMP) sieve of Eratosthenes
pair<bool*, long long> OpenMPSieveOfEratosthenes::run(long long n, unsigned int threads) 
{
    bool *primes = new bool[n/2];
    long long n_primes = n/2;
    long long k = 3;

    omp_set_num_threads(threads);

    do {
        #pragma omp parallel for reduction(-:n_primes)
        for (long long j = k*k ; j<n ; j+=2*k) {
            primes[j>>1]=true;
            n_primes--;
        }
        
        do {
            k+=2;
        } while (k*k <= n && primes[k>>1]);
        
    } while (k*k <= n);

    return pair<bool*, long long>(primes, n_primes+1);
}

void OpenMPSieveOfEratosthenes::test()
{  
    long long n;
    unsigned int threads;
    pair<bool*, long long> primes;

    cout << "Upper bound: ";
    cin >> n;

    cout << "Threads: ";
    cin >> threads;

    primes = run(n, threads);
    
    cout << "Found " << primes.second << " prime numbers" << endl;
    cout << "1 2 ";
    for (int i=3; i<n; i+=2)
        if (!primes.first[i>>1])
            cout << i << " ";

    cout << endl;
}
