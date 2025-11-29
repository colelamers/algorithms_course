#include <vector>
#include <string>
#include <unordered_map>
#include "LZ78Element.h"
#include "HelperFunctions.h"
using namespace std;

#ifndef LZ78_H_
#define LZ78_H_

/**
 * This class is used for the LZ78 trie
 */
class TrieNode {

public:

    unordered_map<char, TrieNode*> edges;
    int id;

    TrieNode(int id) {
        this->id = id;
    }

    ~TrieNode() {
        deepClean(this);
    }

    TrieNode *getChild(char ch) {
        if (edges.find(ch) != edges.end())
            return edges.at(ch);
        return NULL;
    }

    void addChild(int id, char edgeLabel) {
        edges[edgeLabel] = new TrieNode(id);
    }

private:

    void deepClean(TrieNode *node) {
        for (unordered_map<char, TrieNode*>::iterator it = edges.begin();
                it != edges.end(); it++) {
            delete it->second;
        }
    }
};

class LZ78 {

public:

    static LZ78Element encode(vector<char> &str) {
        return LZ78Element(); // placeholder to ensure project compiles
    }

    static vector<char> decode(LZ78Element &pair) {
        return vector<char>(); // placeholder to ensure project compiles
    }
};

#endif /* LZ78_H_ */
