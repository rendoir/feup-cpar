#ifndef OPENMP_SIEVE_H
#define OPENMP_SIEVE_H

#include <cstdint>


class OpenMPSieveOfEratosthenes
{
public:
    static void run(unsigned long long n, int threads);
    static void test();
    static void print(bool *primes, unsigned long long n);
};

#endif
