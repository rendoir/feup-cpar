#ifndef OPENMPI_SIEVE_H
#define OPENMPI_SIEVE_H

#define BLOCK_LOW(i, n, p) ((i) * (n) / (p))
#define BLOCK_HIGH(i, n, p) (BLOCK_LOW((i) + 1, n, p) - 1)
#define BLOCK_SIZE(i, n, p) (BLOCK_LOW((i) + 1, n, p) - BLOCK_LOW(i, n, p))

class OpenMPISieveOfEratosthenes
{
public:
    static void run(long long n);
    //static void test();
};

#endif
