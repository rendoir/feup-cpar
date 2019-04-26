#ifndef OPENMP_SIEVE_H
#define OPENMP_SIEVE_H

class OpenMPSieveOfEratosthenes
{
public:
    static void run(unsigned long long exponent, int threads);
    static int test();
    static void print(bool *primes, unsigned long long n, double run_time);
};

#endif
