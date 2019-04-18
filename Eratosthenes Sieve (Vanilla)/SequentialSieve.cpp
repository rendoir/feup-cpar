#include "SequentialSieve.h"

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;


//Odd-only sequential sieve of Eratosthenes
bool* SequentialSieveOfEratosthenes::run(long long n) 
{
    long long size = pow(2,n);
    bool *primes = new bool[size];
    fill_n(primes, size, true);
    long long k = 2;

    do {
        for (long long j = k*k ; j<n ; j+=k)
            primes[j]=false;
        
        do {
            ++k;
        } while (k*k <= n && !primes[k]);
    } while (k*k <= n);

    return primes;
}

void SequentialSieveOfEratosthenes::test()
{  
    long long n = 0;
    bool* primes;

    while(n <= 0) {
        cout << "Upper bound: ";
        cin >> n;
    }

    primes = run(n);
    
    long long n_primes = n > 2 ? 2 : n > 1 ? 1 : 0;
    cout << (n > 2 ? "1 2 " : n > 1 ? "1 " : "");
    for (int i=3; i<n; i+=2)
        if (primes[i>>1]) {
            n_primes++;
            cout << i << " ";
        }
    cout << endl << "Found " << n_primes << " prime numbers" << endl;

}
