#ifndef OPENMP_SIEVE_H
#define OPENMP_SIEVE_H

class OpenMPSieveOfEratosthenes
{
public:
    static void run(long long exponent, unsigned int threads);
    static void test();
};

#endif
