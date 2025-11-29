#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#ifndef SuffixArray_h
#define SuffixArray_h

/**
 * To compare two Indexes based on the suffix starting at those Indexes.
 * Used for brute-force implementation.
 */
class Index {
    
public:
    
    int i;
    
    Index(int i) {
        this->i = i;
    }
    
    Index() {
        this->i = 0;
    }
    
    string toString() {
        return to_string(i);
    }
};

/**
 * To keep track of the triplets formed during Manber-Myers.
 *
 * Ideally, we should not use this to make it more space-efficient. If I ever
 * get over my laziness, I will get rid of it to save about 3 bytes of space per
 * input character.
 *
 */
class Triplet {

public:

    int firstRank;
    int secondRank;
    int index;

    string toString() {
        return "(" + to_string(firstRank) + ", " + to_string(secondRank) + ", "
                + to_string(index) + ")";
    }
};

int compare(Triplet &a, Triplet &b) {
    if (a.firstRank < b.firstRank)
        return 1;
    if (a.firstRank > b.firstRank)
        return 0;
    if (a.secondRank < b.secondRank)
        return 1;
    return 0;
}

class SuffixArray {
    
private:
    
    static const bool USE_MANBER_MYERS = true; // set to true for Manber-Myers, false for brute-force

    static int binarySearch(vector<char> &arg, char key) {
        int l = 0, r = arg.size() - 1;
        while (l <= r) {
            int m = l + ((r - l) >> 1);
            if (arg[m] == key)
                return m;
            else if (key > arg[m])
                l = m + 1;
            else
                r = m - 1;
        }
        return -1;
    }
    
public:
    
    static vector<int> compute(vector<char> &str) {
        if (USE_MANBER_MYERS)
            return manberMyers(str);
        return bruteforce(str);
    }
    
    /**
     * Should run in O(n log^2 n) expected time. Much more space-efficient than Manber-Myers.
     * Practically faster as well.
     */
    static vector<int> bruteforce(vector<char> &str) {
        vector<Index> indexes;
        indexes.reserve(str.size());
        for (int i = 0; i < str.size(); i++)
            indexes.push_back(Index(i));
        
        sort(indexes.begin(), indexes.end(), [&str](Index &o1, Index &o2) {
            int x = o1.i;
            int y = o2.i;
            
            if (y == x) // same; so, x is not smaller
                return false;
            int i = 0;
            // whichever is earlier: x reaches end or y reaches end (both cannot happen), or mismatch
            while (x + i < str.size() && y + i < str.size() && str.at(x + i) == str.at(y + i))
                i++;
            // if x reached end, x is smaller
            if (x + i == str.size())
                return true;
            // if y reached end, y is smaller
            if (y + i == str.size())
                return false;
            // compare
            return str.at(x + i) < str.at(y + i);
        });
        
        vector<int> SA;
        SA.resize(str.size());
        for (int i = 0; i < SA.size(); i++)
            SA[i] = indexes[i].i;
        return SA;
    }

    /**
     * A Manber-Myers implementation that runs in O(n log^2 n) expected time due to the use
     * of Introsort instead of radix-sort.
     *
     * Although this is worse asymptotically, due to the use of hybrid sorting
     * algorithm, its performance has been found to be superior to radix-sort (about
     * 2-3 times faster on average).
     *
     * Moreover, it uses far less space than radix sort.
     *
     */
    static vector<int> manberMyers(vector<char> &str) {
        int n = str.size();
        int *RANK = new int[n]; // Stores current suffix ranks; basically base-1 indexed inverse suffix array
        vector<Triplet> triplets;
        triplets.reserve(n);
        for (int i = 0; i < n; i++)
            triplets.push_back(Triplet());

        vector<char> sigma = HelperFunctions().getSortedAlphabet(str);

        for (int i = 0; i < n; i++)
            RANK[i] = 1 + binarySearch(sigma, str.at(i));

        int e = 1;        // will grow in powers of 2
        int rank;// to keep track of suffix ranks based on the first e characters
        do {

            int i;
            for (i = 0; i + e < n; i++) {
                // (current rank = ISA[i], next rank = ISA[i + e], current index)
                triplets[i].firstRank = RANK[i];
                triplets[i].secondRank = RANK[i + e];
                triplets[i].index = i;
            }
            for (; i < n; i++) {
                // if i + e >= n, then next rank = -1 (simulates $)
                triplets[i].firstRank = RANK[i];
                triplets[i].secondRank = -1;
                triplets[i].index = i;
            }

//            for (int i = 0; i < n; i++)
//                cout << triplets[i].toString() << " ";

            std::sort(triplets.begin(), triplets.end(), compare);

//            cout << endl;
//            for (int i = 0; i < n; i++)
//                cout << triplets[i].toString() << " ";

            rank = 1;        // smallest suffix has rank 1
            RANK[triplets[0].index] = 1;
            for (i = 1; i < n; i++) {
                if (triplets[i].firstRank != triplets[i - 1].firstRank
                        || triplets[i].secondRank != triplets[i - 1].secondRank) // if current triplet ranks are
                                                                                 // different from previous triplet
                                                                                 // ranks, then increment rank
                    rank++;
                RANK[triplets[i].index] = rank;
            }
            e *= 2;
        } while (rank < n); // if rank reaches n, all suffixes have achieved distinct rank
        vector<int> SA;
        SA.reserve(n);
        for (int i = 0; i < n; i++)
            SA.push_back(i);
        for (int i = 0; i < n; i++)
            SA[RANK[i] - 1] = i;
        delete[] RANK;
        return SA;
    }
};

#endif /* SuffixArray_h */
