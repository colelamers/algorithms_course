#include <vector>
using namespace std;

#ifndef MTFElement_h
#define MTFElement_h

class MTFElement {

public:
    
    vector<char> alphabet;
    vector<int> mtf;

    MTFElement(vector<char> &alphabet, vector<int> &mtf) {
        this->alphabet = alphabet;
        this->mtf = mtf;
    }
    
    MTFElement() {
    }
};

#endif /* MTFElement_h */
