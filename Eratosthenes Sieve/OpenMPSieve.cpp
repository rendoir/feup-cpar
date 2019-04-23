#include "OpenMPSieve.h"

#include <iostream>
#include <omp.h>

using namespace std;


//Odd-only parallel (OpenMP) sieve of Eratosthenes
void OpenMPSieveOfEratosthenes::run(unsigned long long n, int threads) 
{
    bool *primes = new bool[n/2];
    fill_n(primes, n/2, true);
    unsigned long long k = 3;

    omp_set_num_threads(threads);

    do {
        #pragma omp parallel for
        for (unsigned long long j = k*k ; j<n ; j+=2*k)
            primes[j>>1]=false;
        
        do {
            k+=2;
        } while (k*k <= n && !primes[k>>1]);
        
    } while (k*k <= n);

    print(primes, n);

    delete primes;
}

void OpenMPSieveOfEratosthenes::test()
{  
    unsigned long long n = 0;
    int threads = 0;
    bool* primes;

    while(n <= 1) {
        cout << "Upper bound: ";
        cin >> n;
    }

    while(threads == 0 || threads > omp_get_max_threads()) {
        cout << "Threads: ";
        cin >> threads;
    }

    run(n, threads);
}

void OpenMPSieveOfEratosthenes::print(bool *primes, unsigned long long n)
{
    unsigned long long n_primes = n >= 2 ? 1 : 0;
    cout << (n >= 2 ? "2 " : "");
    for (unsigned long long i=3; i<n; i+=2) {
        if (primes[i>>1]) {
            n_primes++;
            cout << i << " ";
        }
    }
    cout << endl << "Found " << n_primes << " prime numbers" << endl;
}
