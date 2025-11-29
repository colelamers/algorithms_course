#include "LZ77Element.h"

#ifndef LZ77_h
#define LZ77_h

class LZ77 {
    
private:
    
    static const int LOOKAHEAD_BUFFER = 128;
    static const int WINDOW = 1024;
    
public:
    
    static LZ77Element encode(const vector<char> &msg) {
        vector<int> deltas;
        vector<int> lengths;
        vector<char> nextChars;
        
        deltas.push_back(0);
        lengths.push_back(0);
        nextChars.push_back(msg.at(0));
        
        int c = 1; // current position in message
        while (c < msg.size()) {
            int length = 0, delta = 0;
            for (int j = c - 1; j >= 0; j--) {
                if (j < c - WINDOW) // don't look behind the left boundary of the window
                    break;
                int l = 0;
                // Find the longest match of the prefix starting at within the window.
                // However, don't look beyond lookahead buffer for finding the match.
                while (c + l < msg.size() && l < LOOKAHEAD_BUFFER && msg.at(c + l) == msg.at(j + l))
                    l++;
                if (l > length) {
                    length = l;
                    delta = c - j;
                }
            }
            if (length == LOOKAHEAD_BUFFER) {
                // if a complete match was found within the lookahead buffer with a position j in the window,
                // then extend the match until a mismatch occurs
                int j = c - delta;
                while (c + length < msg.size() && msg.at(c + length) == msg.at(j + length))
                    length++;
            }
            
            // add triplet
            deltas.push_back(delta);
            lengths.push_back(length);
            nextChars.push_back(msg.at(c + length));
            
            // jump to next unmatched character
            c += 1 + length;
        }
        return LZ77Element(deltas, lengths, nextChars);
    }
    
    static vector<char> decode(LZ77Element &lz77) {
        vector<char> msg;
        int numTriplets = lz77.length.size();
        for (int t = 0; t < numTriplets; t++) {
            int length = lz77.length.at(t);
            for (int j = 1; j <= length; j++) {
                // starting from delta characters behind, append length many characters from the decoded message
                char c = msg.at(msg.size() - lz77.delta.at(t));
                msg.push_back(c);
            }
            // append next character
            msg.push_back(lz77.next.at(t));
        }
        return msg;
    }
};

#endif /* LZ77_h */
