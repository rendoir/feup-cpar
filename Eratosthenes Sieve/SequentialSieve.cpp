#include "SequentialSieve.h"

#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;


//Odd-only sequential sieve of Eratosthenes
bool* SequentialSieveOfEratosthenes::run(long long n) 
{
    bool *primes = new bool[n/2];
    fill_n(primes, n/2, true);
    long long k = 3;

    do {
        
        for (long long j = k*k ; j<n ; j+=2*k)
            primes[j>>1]=false;
        
        do {
            k+=2;
        } while (k*k <= n && !primes[k>>1]);
        
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
