#include "SequentialSieve.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


//Odd-only sequential sieve of Eratosthenes
void SequentialSieveOfEratosthenes::run(unsigned long long exponent) 
{
    unsigned long long n = pow(2, exponent);

    bool *primes = new bool[n/2];
    fill_n(primes, n/2, true);
    unsigned long long k = 3;

    clock_t begin = clock();

    do {
        
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

int SequentialSieveOfEratosthenes::test()
{  
    unsigned long long exponent = 0;

    if(Parameters::automatic) {
        exponent = Parameters::current_exponent;
    } else {
        while(exponent <= 1) {
            cout << "Exponent: ";
            cin >> exponent;
        }
    }

    run(exponent);

    return 0;
}

void SequentialSieveOfEratosthenes::print(bool *primes, unsigned long long n, double run_time) {
    if(Parameters::automatic) {
        ofstream ofs(Parameters::output_file, ofstream::app);
        ofs << "sequencial" << ';' << Parameters::current_exponent << ';' << run_time << endl;
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
