#include "Sequential.h"

#include <iostream>
#include <math.h>

using namespace std;


//Odd-only sequential sieve of Eratosthenes
pair<bool*, long long> SequentialSieveOfEratosthenes::run(long long n) 
{
    bool *primes = new bool[n/2];
    long long n_primes = n/2;
    long long k = 3;

    do {
        
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

void SequentialSieveOfEratosthenes::test()
{  
    long long n;
    pair<bool*, long long> primes;

    cout << "Upper bound: ";
    cin >> n;

    primes = run(n);
    
    cout << "Found " << primes.second << " prime numbers" << endl;
    cout << "1 2 ";
    for (int i=3; i<n; i+=2)
        if (!primes.first[i>>1])
            cout << i << " ";

    cout << endl;
}
