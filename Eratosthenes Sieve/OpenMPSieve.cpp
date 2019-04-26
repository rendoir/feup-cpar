#include "OpenMPSieve.h"

#include <iostream>
#include <ctime>
#include <omp.h>
#include <cmath>

using namespace std;


//Odd-only parallel (OpenMP) sieve of Eratosthenes
void OpenMPSieveOfEratosthenes::run(unsigned long long exponent, int threads) 
{
    unsigned long long n = pow(2, exponent);

    bool *primes = new bool[n/2];
    fill_n(primes, n/2, true);
    unsigned long long k = 3;

    omp_set_num_threads(threads);
    clock_t begin = clock();

    do {
        #pragma omp parallel for
        for (unsigned long long j = k*k ; j<n ; j+=2*k)
            primes[j>>1]=false;
        
        do {
            k+=2;
        } while (k*k <= n && !primes[k>>1]);
        
    } while (k*k <= n);

    double run_time = (double)(clock() - begin) / CLOCKS_PER_SEC;
    print(primes, n, run_time);

    delete primes;
}

int OpenMPSieveOfEratosthenes::test()
{  
    unsigned long long n = 0;
    int threads = 0;

    while(n <= 1) {
        cout << "Exponent: ";
        cin >> n;
    }

    while(threads <= 0 || threads > omp_get_max_threads()) {
        cout << "Threads: ";
        cin >> threads;
    }

    run(n, threads);

    return 0;
}

void OpenMPSieveOfEratosthenes::print(bool *primes, unsigned long long n, double run_time)
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
    cout << "Run time: " << run_time << " seconds" << endl;
}
