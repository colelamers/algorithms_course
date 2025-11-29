#ifndef PrimeGenerator_h
#define PrimeGenerator_h

#include <time.h>
#include <cmath>

class PrimeGenerator {
    
public:
    
    static bool deterministic(int n) {
        
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;
        if ((n & 1) == 0)
            return false;
        if (n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19)
            return true;
        if (n <= 21)
            return false;
        
        int sqrt_n = (int) sqrt(n);
        
        for (int i = 3; i <= sqrt_n; i += 2)
            if (n % i == 0)
                return false; // definitely composite
        return true; // definitely prime
    }
    
    /**
     * This method generates returns a random prime in [LB, UB].
     * CAUTION: The range must be sufficiently large.
     */
    static int getPrime(int LB, int UB) {
        int prime;
        do {
            int diff = UB - LB;
            prime = LB + rand() % diff;
            if (deterministic(prime))
                break;
        }
        while (true);
        return prime;
    }
};

#endif /* PrimeGenerator_h */
