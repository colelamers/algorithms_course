#include "BitArray.h"
#include "PrimeGenerator.h"


#include <iostream>

/**
 This is to test Bit Array and Prime Generation code.
 */
int main(int argc, const char * argv[]) {
    BitArray bf = BitArray(12);
    bf.set(0);
    bf.set(1);
    bf.set(5);
    bf.set(8);
    for (int i = 0; i < 12; i++)
        cout << i << ":" << bf.access(i) << endl;

    bf.clear(1);
    cout << endl;
    for (int i = 0; i < 12; i++)
        cout << i << ":" << bf.access(i) << endl;

    cout << endl << PrimeGenerator::getPrime(100, 115) << endl;

    return 0;
}
