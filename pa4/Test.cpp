#include "PlagiarismDetector.h"
#include "PrimeGenerator.h"

static const int MAX_PRIME_LENGTH_IN_BITS = 24; // DO NOT EXCEED 30. Currently supported up to primes <= 2^30
static const int NUM_PRIMES = 20;
static const string DIRECTORY = "PA4/Data/";

int main() {
	vector<int> primes = PrimeGenerator().largePrimes(MAX_PRIME_LENGTH_IN_BITS,
			NUM_PRIMES);
	PlagiarismDetector().run(primes, DIRECTORY + "articles100/");
	PlagiarismDetector().run(primes, DIRECTORY + "articles1000/");
	PlagiarismDetector().run(primes, DIRECTORY + "articles2500/");
	PlagiarismDetector().run(primes, DIRECTORY + "articles10000/");
	PlagiarismDetector().run(primes, DIRECTORY + "setA/");
	PlagiarismDetector().run(primes, DIRECTORY + "setB/");
	PlagiarismDetector().run(primes, DIRECTORY + "setC/");
	PlagiarismDetector().run(primes, DIRECTORY + "setD/");
	PlagiarismDetector().run(primes, DIRECTORY + "setE/");
}

