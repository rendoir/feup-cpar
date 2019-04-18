#include "OpenMPSieve.h"

#include <iostream>
#include <math.h>
#include <omp.h>
#include <algorithm>

using namespace std;

void OpenMPSieveOfEratosthenes::run(long long exponent, unsigned int threads) 
{
    long long n = pow(2, exponent);
    bool *marking = new bool[n];
    fill_n(marking, n, true);

    omp_set_num_threads(threads);

    double run_time = clock();

    long long k = 2;
    do {
        #pragma omp parallel for
        for (long long j = k*k ; j<n ; j+=k)
            marking[j]=false;
        
        do {
            ++k;
        } while (k*k <= n && !marking[k]);
    } while (k*k <= n);

    run_time = clock() - run_time;

    long long counter = 0;
    for (unsigned long i = 2; i < n; i++)
		if (marking[i])
			++counter;
    
    cout << n << ";" << exponent << ";" << run_time << ";" << counter << endl;
}

void OpenMPSieveOfEratosthenes::test()
{  
    long long n = 0;
    unsigned int threads = 0;

    while(n <= 0) {
        cout << "Upper bound: ";
        cin >> n;
    }

    while(threads == 0 || threads > omp_get_max_threads()) {
        cout << "Threads: ";
        cin >> threads;
    }

    run(n, threads);
}
