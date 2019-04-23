#include "SequentialSieve.h"

#include <iostream>

using namespace std;


//Odd-only sequential sieve of Eratosthenes
void SequentialSieveOfEratosthenes::run(unsigned long long n) 
{
    bool *primes = new bool[n/2];
    fill_n(primes, n/2, true);
    unsigned long long k = 3;

    do {
        
        for (unsigned long long j = k*k ; j<n ; j+=2*k)
            primes[j>>1]=false;
        
        do {
            k+=2;
        } while (k*k <= n && !primes[k>>1]);
        
    } while (k*k <= n);

    print(primes, n);

    delete primes;
}

void SequentialSieveOfEratosthenes::test()
{  
    unsigned long long n = 0;

    while(n <= 1) {
        cout << "Upper bound: ";
        cin >> n;
    }

    run(n);
}

void SequentialSieveOfEratosthenes::print(bool *primes, unsigned long long n) {
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
