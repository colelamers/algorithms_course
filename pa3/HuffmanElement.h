#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

#ifndef HuffmanPair_H_
#define HuffmanPair_H_

class HuffmanElement{

public:

	string encoding;
	unordered_map<int, string> mappingTable;

    HuffmanElement(string &encoding, unordered_map<int, string> &mappingTable) {
		this->encoding = encoding;
		this->mappingTable = mappingTable;
	}
    
    HuffmanElement() {
        encoding = "";
    }
    
    HuffmanElement(int character, int length) {
        string out = "";
        for (int i = 0; i < length; i++)
            out += '0';
        mappingTable[character] = "0";
    }
    
    int size() {
        int _size = 0;
        unordered_map<int, string>::iterator it = mappingTable.begin();
        while (it != mappingTable.end()) {
            _size += to_string(it->first).size() + 1 + mappingTable[it->first].length();
            it++;
        }
        _size += mappingTable.size() - 1; // for newline characters
        return 1 + ceil(encoding.length()/8.0) + _size;
    }
};

#endif /* HuffmanPair_H_ */
