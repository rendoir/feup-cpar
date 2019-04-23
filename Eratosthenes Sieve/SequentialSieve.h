#ifndef SEQUENTIAL_SIEVE_H
#define SEQUENTIAL_SIEVE_H

class SequentialSieveOfEratosthenes
{
public:
    static void run(unsigned long long n);
    static void test();
    static void print(bool *primes, unsigned long long n);
};

#endif
