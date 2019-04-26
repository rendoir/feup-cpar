#ifndef SEQUENTIAL_SIEVE_H
#define SEQUENTIAL_SIEVE_H

class SequentialSieveOfEratosthenes
{
public:
    static void run(unsigned long long exponent);
    static int test();
    static void print(bool *primes, unsigned long long n, double run_time);
};

#endif
