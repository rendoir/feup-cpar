#ifndef OPENMPMPI_SIEVE_H
#define OPENMPMPI_SIEVE_H

#define BLOCK_LOW(i, n, p) ((i) * (n) / (p))
#define BLOCK_HIGH(i, n, p) (BLOCK_LOW((i) + 1, n, p) - 1)
#define BLOCK_SIZE(i, n, p) (BLOCK_LOW((i) + 1, n, p) - BLOCK_LOW(i, n, p))
#define IS_ROOT(n) (n == 0)

class OpenMPMPISieveOfEratosthenes
{
public:
    static void run(long long exponent, unsigned int threads);
    //static void test();
};

#endif
