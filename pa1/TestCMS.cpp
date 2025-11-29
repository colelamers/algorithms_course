#include "BigInt.hpp"
#include "CMS.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

static const int universe = 1000;
static BigInt n("0"); // Number of data items in the stream

/**
 * epsilon is the acceptable error. delta is the acceptable error probability. Both must be < 1.
 * Specifically, Pr(estimate - actual >= n*epsilon) <= delta
 */
static const double epsilon = 0.01;
static const double delta = 0.01;
static const int B = (int) ceil(exp(1)/epsilon); // Number of columns in CMS
static const int beta = (int) log(1 / delta); // Number of rows/hash functions in CMS
static const int k = 10000; // k for k-heavy hitters

/**
 * Since the data size can very large, it cannot be read or written in one shot.
 * This variable is for writing/reading as many numbers to/from the file in one shot.
 * So, CHUNK_SIZE numbers are accumulated and then written to the file.
 * Likewise, a prompt is given when CHUNK_SIZE numbers are read back from the file.
 */
static const int CHUNK_SIZE = 1000000;

/**
 * We do not want an even distribution of numbers to simulate real-world scenarios.
 * So, we add a SKEW that will (hopefully) generate some numbers very frequently.
 * This should simulate real-worlds scenarios to the best of our abilities.
 * (Well not really, as there are better ways :-|)
 */
static const int SKEW = 100000;

static const string DATA_PATH = "dataCMS.txt";

static void generateCMSData() {
    string out = "";

    ofstream bw(DATA_PATH, ios::out);
    char choice = 'Y';
    while (choice == 'Y' || choice == 'y') {
        for (int i = 0; i < CHUNK_SIZE ;) {
            int skew = rand() % SKEW;
            int val = rand() % universe;
            for (int j = 0; j < skew && i < CHUNK_SIZE; i++, j++) {
                out += to_string(val);
                out += "\n";
            }
        }
        bw << out;
        n = n + CHUNK_SIZE;
        cout << "Generated " << n << " elements. Do you want more (Yes: Y/y, No: any key)? ";
        cin >> choice;
        out = "";
    }
    cout << endl;
    bw.close();
}

static void testCMS() {

    CMS cms = CMS(beta, B, universe);
    unordered_map<int, int> hashSet;

    ifstream in(DATA_PATH, ios::in);
    n = BigInt("0");
    cout << endl;
    int key;
    while (in >> key) {
        cms.increment(key);
        int freq = hashSet[key];
        if (freq == 0)
            hashSet[key] = 1;
        else
            hashSet[key] = 1 + freq;
        n++;
        if (n % CHUNK_SIZE == 0)
            cout << "Read " << n << " values." << endl;
    }
    in.close();

    double probabilityError = 0; // for calculating % of cases where (estimate - actual >= n*epsilon)
    double avgDiff = 0; // for calculating avg of (estimate - actual)
    double avgFreq = 0; // for calculating average of actual frequencies
    double expectedFreqError = 0; // for calculating % of cases where (estimate >= actual + n/B)
    double avgErrorInComputingActualFromEstimate = 0; // We guess the actual as (estimate - n/B).
    // Then, we check how much it differs from the actual on average.
    int numUnder = 0; // to compute the number of underestimates

    vector<int> actualHH; // actual heavy-hitters
    vector<int> estimatedHH; // estimated heavy-hitters

    long epsInv = 1/epsilon;

    for (int key = 0; key < universe; key++) {
        int actual = hashSet[key];
        int estimate = cms.frequency(key);

        if (estimate < actual)
            numUnder++;

        avgFreq += actual;
        avgDiff += estimate - actual;


        if ((n/epsInv).to_int() <= estimate - actual)
            probabilityError++;

        if ((n/B).to_int() <= estimate - actual)
            expectedFreqError++;

        double actualFromEstimate = estimate - (n/B).to_long();
        if (actualFromEstimate < 0)
            actualFromEstimate = 0; // if negative, estimate as 0
        avgErrorInComputingActualFromEstimate += abs(actualFromEstimate - actual);

        if ((n/k).to_int() < actual)
            actualHH.push_back(key);
        if ((n/k).to_int() < estimate)
            estimatedHH.push_back(key);
    }

    cout << "\n\nNumber of data points (n): " <<  n << endl;
    cout << "Universe: " <<  universe << endl;
    cout << "Number of columns (B): " <<  B << endl;
    cout << "Number of rows (hash functions): " <<  beta << endl;
    cout << "Epsilon: " <<  epsilon << endl;
    cout << "Delta: " <<  delta << endl;
    cout << "n/B: " <<  n/B << endl;
    cout << "n*epsilon: " <<  n/epsInv << endl;

    cout << "\nNumber of underestimates: " <<  numUnder << endl;
    cout << "Average of actual: " <<  avgFreq / universe << endl;
    cout << "Average of (estimate - actual): " <<  avgDiff / universe << endl;
    cout << "% of cases where (estimate - actual >= n*epsilon): " <<  100 * probabilityError / universe << "%" << endl;
    cout << "% of cases where (estimate >= actual + n/B): " <<  100 * expectedFreqError / universe << "%" << endl;
    cout << "Average difference when we compute actual as (estimate - n/B): "
    <<  avgErrorInComputingActualFromEstimate / universe << endl;

    cout << "\nk for k-heavy hitters: " <<  k << endl;
    cout << "Number of actual heavy-hitters: "
    <<  actualHH.size() << endl;
    cout << "Number of estimated heavy-hitters: "
    <<  estimatedHH.size() << endl;

}

int main(int argc, const char * argv[]) {
    srand(clock()); // IMPORTANT: DO NOT COMMENT OUT THIS LINE
    generateCMSData();
    testCMS();
    return 0;
}
