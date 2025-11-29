#ifndef UniversalHashing_h
#define UniversalHashing_h

#include "BigInt.hpp"
#include "PrimeGenerator.h"
#include <time.h>
#include <stdio.h>

class UniversalHashing {
    
private:
    
    int a, b, p, m;
    static const bool LOGGER = true;

public:
    
    UniversalHashing(int _prime, int _tableSize) {
        p = _prime;
        m = _tableSize;
        a = 1 + rand() % (p-1);
        b = rand() % p;
        
        if (LOGGER)
            printf("Prime = %8d, a = %8d, b = %8d\n", p, a, b);
    }

    int hash(int key) {
        BigInt x = a;
        x = x * key + b;
        int hashCode = ((x % p) % m).to_int();
        return hashCode;
    }
};

#endif /* UniversalHashing_h */
