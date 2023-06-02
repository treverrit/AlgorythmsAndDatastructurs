#pragma once

#include<cstdint>
#include<stdio.h>
#include<string.h>

class Primes
{
private:
	static const size_t N = 250000;
	bool sieve[N];
public: 
	uint64_t GetPrime(uint64_t n);
};

