#include "LZSSElement.h"

#ifndef LZSS_h
#define LZSS_h

class LZSS {
    
private:
    
    static const int LOOKAHEAD_BUFFER = 128;
    static const int WINDOW = 1024;
    static const int LENGTH_THRESHOLD = 4; // set to 2 for correctness test
    
public:
    
    static LZSSElement encode(vector<char> &msg) {
        return LZSSElement(); // placeholder to ensure project compiles
    }
    
    static vector<char> decode(LZSSElement &lzss) {
        return vector<char>(); // placeholder to ensure project compiles
    }
};

#endif /* LZSS_h */
