#include "Primes.h"

uint64_t Primes::GetPrime(uint64_t n)
{
    uint64_t num_primes = 0;
    memset(sieve, true, N);
    sieve[0] = false;
    sieve[1] = false;

    for (size_t index = 0; index < N; ++index)
    {
        if (sieve[index])
        {
            ++num_primes;

            if (num_primes == n)
            {
                return index;
            }

            for (size_t selector = index + index; selector < N; selector += index)
            {

            }
        }
    }
}
