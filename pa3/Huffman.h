#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include "HuffmanElement.h"
#include "HelperFunctions.h"
using namespace std;

#ifndef HUFFMANENCODER_H_
#define HUFFMANENCODER_H_

class BinaryTreeNode {

public:

    int id;
    int value;
    BinaryTreeNode *left, *right;

    ~BinaryTreeNode() {
        deepClean(this);
    }

    BinaryTreeNode(int id, int value) {
        this->id = id;
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }
    
    string toString() {
        string out = "<" + to_string(value) + (id == -1 ? "" : ", " + to_string(id));
        out += ", " + (left == NULL ? "null" : to_string(left->value));
        out += ", " + (right == NULL ? "null" : to_string(right->value));
        out += ">";
        return out;
    }

private:

    void deepClean(BinaryTreeNode *node) {
        if (node->left != NULL)
            delete node->left;
        if (node->right != NULL)
            delete node->right;
    }
};

class BinaryTreeNodeComparator {

public:

    bool operator()(const BinaryTreeNode *arg1,
            const BinaryTreeNode *arg2) const {
        return arg1->value > arg2->value;
    }
};

class Huffman {

private:
    
	unordered_map<string, string> mappingTable;
    
    static void preOrder(BinaryTreeNode *root) {
        if (root == NULL)
            return;
        cout << root->toString() << endl;
        preOrder(root->left);
        preOrder(root->right);
    }

public:
    
    static HuffmanElement encode(vector<int> &msg) {
        if (msg.size() == 0)
            return HuffmanElement();
        vector<int> alphabet = HelperFunctions::getSortedAlphabet(msg);
        if (alphabet.size() == 1) {
            return HuffmanElement(alphabet.at(0), msg.size());
        }
        
        unordered_map<int, int> freqMap = HelperFunctions::getFrequencies(msg);
        priority_queue<BinaryTreeNode*, vector<BinaryTreeNode*>,
        BinaryTreeNodeComparator> pq;
        int id = 0;
        for (int i = 0; i < alphabet.size(); i++) {
            BinaryTreeNode *btNode = new BinaryTreeNode(id++,
                                                        freqMap[alphabet.at(i)]);
            pq.push(btNode);
        }
        while (pq.size() > 1) {
            BinaryTreeNode *min = pq.top();
            pq.pop();
            BinaryTreeNode *secondMin = pq.top();
            pq.pop();
            BinaryTreeNode *parent = new BinaryTreeNode(-1,
                                                        min->value + secondMin->value);
            parent->left = min;
            parent->right = secondMin;
            pq.push(parent);
        }
        // preOrder(pq.top());
        unordered_map<int, string> mappingTable;
        createTable(mappingTable, alphabet, pq.top(), "");
        string bitString = "";
        for (int i = 0; i < msg.size(); i++)
            bitString += mappingTable[msg.at(i)];
        delete pq.top();
        return HuffmanElement(bitString, mappingTable);
    }
    
    static vector<int> decode(HuffmanElement &huffObj) {
        unordered_map<string, int> reverseMap;
        unordered_map<int, string> mappingTable = huffObj.mappingTable;
        for (unordered_map<int, string>::iterator it = mappingTable.begin();
             it != mappingTable.end(); ++it) {
            reverseMap[it->second] = it->first;
        }
        vector<int> decodedMsg;
        string encode = "";
        for (int i = 0; i < huffObj.encoding.length(); i++) {
            encode += huffObj.encoding.at(i);
            if (reverseMap.find(encode) != reverseMap.end()) {
                decodedMsg.push_back(reverseMap[encode]);
                encode = "";
            }
        }
        return decodedMsg;
    }

private:

    static void createTable(unordered_map<int, string> &mappingTable, vector<int> &alphabet, BinaryTreeNode *node, string encoding) {
        if (node->left == nullptr && node->right == nullptr)
            mappingTable[alphabet[node->id]] = encoding;
        else {
            if (node->left != nullptr)
                createTable(mappingTable, alphabet, node->left, encoding + "0");
            if (node->right != nullptr)
                createTable(mappingTable, alphabet, node->right, encoding + "1");
        }
    }
};

#endif /* HUFFMANENCODER_H_ */
