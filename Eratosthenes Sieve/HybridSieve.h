#ifndef HYBRID_SIEVE_H
#define HYBRID_SIEVE_H

#define BLOCK_LOW(i, n, p) ((i) * (n) / (p))
#define BLOCK_HIGH(i, n, p) (BLOCK_LOW((i) + 1, n, p) - 1)
#define BLOCK_SIZE(i, n, p) (BLOCK_LOW((i) + 1, n, p) - BLOCK_LOW(i, n, p))
#define IS_ROOT(n) (n == 0)


class HybridSieveOfEratosthenes
{
public:
    static void run(unsigned long long exponent, int threads);
    static int test();
    static void print(bool *marking, unsigned long long block_size, int rank, int size, unsigned long long lower_bound, unsigned long long n, double run_time);
};

#endif
