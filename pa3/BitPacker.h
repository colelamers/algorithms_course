#include <string>
#include <vector>
#include <math.h>
#include "HelperFunctions.h"
using namespace std;

#ifndef BITPACKER_H_
#define BITPACKER_H_

class BitPacker {
    
public:
    
    /**
     * Packs 8 bits at a time into a byte. bits must contain only 1 & 0. The total
     * number of bytes = 1 + ceil(bits.length/8). Last byte indicates length of the
     * last packed byte.
     */
    static vector<char> pack(string &bits) {
        return vector<char>(); // placeholder to ensure project compiles
    }
    
    /**
     * Unpacks each byte into a bit representation. All representations are in 8
     * bits, except possibly the last one.
     */
    static string unpack(vector<char> &bytes) {
        return ""; // placeholder to ensure project compiles
    }
};

#endif /* BITPACKER_H_ */
