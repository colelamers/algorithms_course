#include <vector>
#include <string>
using namespace std;

#ifndef LZ77Element_h
#define LZ77Element_h

class LZ77Element {
    
public:
    
    vector<int> delta;
    vector<int> length;
    vector<char> next;
    
    LZ77Element(vector<int> &delta, vector<int> &length, vector<char> &next) {
        this->delta = delta;
        this->length = length;
        this->next = next;
    }
    
    string toString() {
        string ret = "";
        for (int i = 0; i < delta.size(); i++)
            ret += "<" + to_string(delta.at(i)) + "," + to_string(length.at(i)) + "," + next.at(i) + "> ";
        return ret;
    }
};

#endif /* LZ77Element_h */
