#ifndef OPENMP_SIEVE_H
#define OPENMP_SIEVE_H

class OpenMPSieveOfEratosthenes
{
public:
    static bool* run(long long n, unsigned int threads);
    static void test();
};

#endif
