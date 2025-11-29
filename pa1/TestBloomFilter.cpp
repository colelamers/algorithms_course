#include "BloomFilter.h"
#include <fstream>
#include <cmath>
#include <unordered_set>

using namespace std;

static int n = 1000000; // Number of insertions (data size).
static int universe = 4*n; // Universe size. Also, number of searches.
static int alpha = 16; // Load factor. So, the table size is n*alpha bits.
static int beta = ceil(log(2) * alpha); // Number of hash functions. Optimized for load factor.

static string DATA_PATH = "dataBloom.txt";

static long CLOCKS_PER_MILLISEC = CLOCKS_PER_SEC/1000;


static void generateBloomData() {
    string out = "";
    for (int i = 0; i < n; i++)
        out += to_string(rand() % universe) + "\n";
    ofstream bw(DATA_PATH, ios::out);
    bw << out;
    bw.close();
}

static void testBloomFilter() {

    BloomFilter bf = BloomFilter(alpha * n, beta, universe);
    unordered_set<int> hashSet;

    ifstream in(DATA_PATH, ios::in);
    double totalInsTimeHash = 0; // to compute average insertion time in unordered_set
    double totalInsTimeBF = 0; // to compute average insertion time in Bloom Filter
    long currTime;
    int key;
    while (in >> key) {
        currTime = clock();
        bf.insert(key);
        totalInsTimeBF += clock() - currTime;

        currTime = clock();
        hashSet.insert(key);
        totalInsTimeHash += clock() - currTime;
    }
    in.close();

    double falsePos = 0; // to compute the false positive rate
    int success = 0; // to compute the number of successful searches
    double falseNeg = 0; // to compute the false negative rate
    double totalSearchTimeHash = 0; // to compute average search time in unordered_set
    double totalSearchTimeBF = 0; // to compute average search time in Bloom Filter

    for (int key = 0; key < universe; key++) {
        currTime = clock();
        bool bfContains = bf.search(key);
        totalSearchTimeBF += clock() - currTime;

        currTime = clock();
        bool hashContains = hashSet.contains(key);
        totalSearchTimeHash += clock() - currTime;

        if (bfContains && !hashContains)
            falsePos++;
        else if (hashContains) {
            success++;
            if (!bfContains)
                falseNeg++;
        }
    }

    totalInsTimeBF /= n;
    totalInsTimeHash /= n;
    totalSearchTimeBF /= universe;
    totalSearchTimeHash /= universe;

    cout << "\nData size = " << n << endl;
    cout << "Universe size = " << universe << endl;
    cout << "Load factor = " <<  alpha << endl;
    cout << "Number of hash functions = " << beta << endl;
    
    cout << "\n% of Successful Searches = " << 100.00 * success / universe
    << "% (" << success << " out of " << universe << ")" << endl;
    cout <<"False Positive Rate = " << 100 * falsePos / universe << "%" << endl ;
    cout <<"False Negative Rate = " << 100 * falseNeg / universe << "%" << endl;
    
    cout << "\nAverage Insertion Time: Hash = " << totalInsTimeHash / (CLOCKS_PER_MILLISEC)
    << "; BF = " << totalInsTimeBF / (CLOCKS_PER_MILLISEC) << endl;
    cout << "Average Search Time: Hash = " << totalSearchTimeHash / CLOCKS_PER_MILLISEC
    << "; BF = " << totalSearchTimeBF / CLOCKS_PER_MILLISEC << endl;
}

int main(int argc, const char * argv[]) {
    srand(clock()); // IMPORTANT: DO NOT COMMENT OUT THIS LINE
    
    generateBloomData();
    testBloomFilter();
    return 0;
}
