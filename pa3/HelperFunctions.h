#include <unordered_map>
#include <set>
#include <vector>
#include <string>
using namespace std;

#ifndef HELPERFUNCTIONS_H_
#define HELPERFUNCTIONS_H_

class HelperFunctions {
    
public:
    
    /**
     * Converts str, a bit-string, to decimal
     */
    static int binaryToDecimal(string &str) {
        int dec = 0;
        for (int i = str.size() - 1, k = 1; i >= 0; i--, k = k << 1)
            if (str.at(i) == '1')
                dec += k;
        return dec;
    }
    
    /**
     * Converts n into a binary string of length b.
     */
    static string decimalToBinary(int n, int b) {
        string bin;
        bin.reserve(b);
        for (int i = 0; i < b; i++)
            bin += '0';
        int k = b - 1;
        while (n > 0) {
            bin[k--] = 48 + n % 2;
            n = n >> 1;
        }
        return bin;
    }
    
    /**
     * Returns the distinct characters in sorted order.
     */
    template<typename F>
    static vector<F> getSortedAlphabet(vector<F> &arg) {
        set<F> sigma;
        for (int i = 0; i < arg.size(); i++)
            sigma.insert(arg.at(i));
        vector<F> sigmaAsArray;
        sigmaAsArray.reserve(sigma.size());
        for (typename set<F>::iterator it = sigma.begin(); it != sigma.end();
             it++)
            sigmaAsArray.push_back(*it);
        return sigmaAsArray;
    }
    
    /**
     * Returns frequency of each character.
     */
    template<typename F>
    static unordered_map<F, int> getFrequencies(vector<F> &arg) {
        unordered_map<F, int> freqMap;
        for (int i = 0; i < arg.size(); i++) {
            F &key = arg.at(i);
            if (freqMap.find(key) == freqMap.end())
                freqMap[key] = 1;
            else
                freqMap[key] = freqMap.at(key) + 1;
        }
        return freqMap;
    }
    
    /**
     * Segregates each character into a string vector
     */
    static vector<char> stringToVector(string &arg) {
        vector<char> stringAsList;
        for (int i = 0; i < arg.length(); i++) {
            stringAsList.push_back(arg.at(i));
        }
        return stringAsList;
    }
    
    /**
     * Concatenates all characters into a string.
     */
    template<typename F>
    static string vectorToString(vector<F> &list) {
        string sb = "";
        for (int i = 0; i < list.size(); i++)
            sb += list.at(i);
        return sb;
    }
    
    /**
     * Verifies if the content of both vectors are the same.
     */
    template<typename F>
    static void verifyEquality(vector<F> &arg1, vector<F> &arg2) {
        if (arg1.size() == arg2.size()) {
            for (int i = 0; i < arg1.size(); i++)
                if (arg1.at(i) != arg2.at(i)) {
                    throw "Something is wrong!!!";
                }
        } else {
            throw "Something is wrong!";
        }
    }
    
    /**
     * Converts an arraylist of characters to an arraylist of integers
     */
    static vector<int> charsToInts(vector<char> &arg) {
        vector<int> ret;
        ret.reserve(arg.size());
        for (int c : arg)
            ret.push_back(c);
        return ret;
    }
    
    /**
     * Converts an arraylist of integers to an arraylist of characters.
     * CAUTION: Conversion is only possible for integers in [0, 255]
     */
    static vector<char> intsToChars(vector<int> &arg) {
        vector<char> ret;
        ret.reserve(arg.size());
        for (int c : arg) {
            if (c < 256 && c >= 0)
                ret.push_back((char) c);
            else throw (to_string(c) + "is not in the range [0, 255]");
        }
        return ret;
    }
};

#endif
/* HELPERFUNCTIONS_H_ */
