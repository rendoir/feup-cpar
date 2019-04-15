#include <utility>

class OpenMPSieveOfEratosthenes
{
public:
    static std::pair<bool*, long long> run(long long n, unsigned int threads);
    static void test();
};
