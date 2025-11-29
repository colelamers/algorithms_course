#include <vector>
#include <string>
using namespace std;

#ifndef LZSSElement_h
#define LZSSElement_h

class LZSSElement {
    
public:
    
    string identifier;
    vector<int> delta;
    vector<int> length;
    vector<char> next;
    
    LZSSElement(string &identifier, vector<int> &delta, vector<int> &length, vector<char> &next) {
        this->identifier = identifier;
        this->delta = delta;
        this->length = length;
        this->next = next;
    }
    
    LZSSElement() {
        identifier = "";
    }
    
    string toString() {
        string ret = "";
        for (int i = 0, d = 0, n = 0; i < identifier.length(); i++) {
            if (identifier.at(i) == '0') {
                ret += "<";
                ret += next.at(n);
                ret += "> ";
                n++;
            }
            else {
                ret += "<" + to_string(delta.at(d)) + "," + to_string(length.at(d)) + "," + next.at(n) + "> ";
                n++;
                d++;
            }
        }
        return ret;
    }
};

#endif /* LZSSElement_h */
