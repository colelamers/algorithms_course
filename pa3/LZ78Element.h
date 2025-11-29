#include <vector>
#include <string>
using namespace std;

#ifndef LZ78PAIR_H_
#define LZ78PAIR_H_

class LZ78Element {

public:

	string nodeIDBits; // this is the bit-string representing the nodes in the LZ78 output
	vector<char> chars; // these are the characters in the LZ78 output

	LZ78Element() {
		this->nodeIDBits = "";
	}

	LZ78Element(string &nodeIDBits, vector<char> &nextChars) {
		this->nodeIDBits = nodeIDBits;
		this->chars = nextChars;
	}

	int size() {
		return this->chars.size();
	}
};

#endif /* LZ78PAIR_H_ */
