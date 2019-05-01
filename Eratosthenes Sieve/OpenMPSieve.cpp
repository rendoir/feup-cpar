#include "OpenMPSieve.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
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
    double begin = omp_get_wtime();

    do {
        #pragma omp parallel for
        for (unsigned long long j = k*k ; j<n ; j+=2*k)
            primes[j>>1]=false;
        
        do {
            k+=2;
        } while (k*k <= n && !primes[k>>1]);
        
    } while (k*k <= n);

    double run_time = (double)(omp_get_wtime() - begin);
    print(primes, n, run_time);

    delete primes;
}

int OpenMPSieveOfEratosthenes::test()
{  
    unsigned long long exponent = 0;
    int threads = 0;

    if(Parameters::automatic) {
        exponent = Parameters::current_exponent;
        threads = Parameters::threads;
    } else {
        while(exponent <= 1) {
            cout << "Exponent: ";
            cin >> exponent;
        }

        while(threads <= 0 || threads > omp_get_max_threads()) {
            cout << "Threads: ";
            cin >> threads;
        }
    }

    run(exponent, threads);

    return 0;
}

void OpenMPSieveOfEratosthenes::print(bool *primes, unsigned long long n, double run_time)
{
    if(Parameters::automatic) {
        ofstream ofs(Parameters::output_file, ofstream::app);
        ofs << "omp" << ';' << Parameters::current_exponent << ';' << run_time << endl;
        ofs.close();
    } else {
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
}
