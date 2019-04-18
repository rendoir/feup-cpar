#include "SequentialSieve.h"

#include <iostream>
#include <math.h>
#include <time.h>
#include <algorithm>

using namespace std;

void SequentialSieveOfEratosthenes::run(long long exponent) 
{
    long long n = pow(2, exponent);
    bool *marking = new bool[n];
    fill_n(marking, n, true);

    double run_time = clock();

    long long k = 2;
    do {
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

void SequentialSieveOfEratosthenes::test()
{  
    long long n = 0;

    while(n <= 0) {
        cout << "Upper bound: ";
        cin >> n;
    }

   run(n);
}
