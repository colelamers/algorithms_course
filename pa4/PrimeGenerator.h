#include <math.h>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <vector>
using namespace std;

#ifndef PRIMEGENERATOR_H_
#define PRIMEGENERATOR_H_

class PrimeGenerator {

public:

	static const int MAX_ITERATIONS = 5; // increase for higher accuracy
	static const bool DETERMISTIC_MODE = true; // set to true for a deterministic test after Rabin-Miller, and false to return the answer from Miller-Rabin

	static bool millerRabin(int n) {

		int r = 0;
		int d = n - 1; // Write n = (2^r)*d + 1
		while ((d & 1) == 0) { // as long as d is even
			d = d >> 1; // d = d/2
			r++;
		}

		for (int numIter = 0; numIter < MAX_ITERATIONS; numIter++) {
			int a = (2 + rand() % (n - 3)) % n;
			int d_temp = d; // Store d
			int r_temp = r; // Store r
			bool iterateAgain = false;

			int x = 1; // x = (a^d)%n
			while (d > 0) {
				if ((d & 1) == 1)
					x = (x * a) % n;
				d = d >> 1;
				a = (a * a) % n;
			}

			if (x != 1 && x != n - 1) {
				while (r > 0) {
					x = (x * x) % n;
					if (x == n - 1) {
						iterateAgain = true;
						break;
					}
					r--;
				}
				if (!iterateAgain)
					return false; // definitely composite
			}

			d = d_temp; // Retrieve d
			r = r_temp; // Retrieve r
		}
		return true; // probably prime
	}

	static bool isPrime(int n) {

		if (n <= 1)
			return false;
		if ((n & 1) == 0)
			return false;
		int sqrt_n = sqrt(n);
		if (n <= 10000) {
			// deterministic test for small primes
			for (int i = 3; i <= sqrt_n; i += 2)
				if (n % i == 0)
					return false; // definitely composite
			return true; // definitely prime
		}

		bool answerMR = millerRabin(n);
		if (!DETERMISTIC_MODE)
			return answerMR;

		if (!answerMR)
			return false; // definitely composite

		// deterministic test for prime
		for (int i = 3; i <= sqrt_n; i += 2)
			if (n % i == 0)
				return false; // definitely composite
		return true; // definitely prime
	}

public:

	/**
	 * This method generates 4*numPrimes many primes, each having at most maxBits in
	 * its binary representation. Then, the method returns numPrimes random primes
	 * among the generated ones.
	 */
	static vector<int> largePrimes(int maxBits, int numPrimes) {

		int max = 1;
		while (maxBits > 0) { // TODO: Change to fast exponentiation
			maxBits -= 1;
			max = max << 1;
		}
		max--;
		vector<int> primes;
		while (primes.size() < 4 * numPrimes && max >= 2) {
			int p = max;
			if (isPrime(p)) {
				primes.push_back(p);

			}
			max -= 2;
		}
		vector<int> answer(numPrimes);
		unordered_set<int> alreadyIn;
		int i = 0;
		while (i < numPrimes) {
			int index = rand() % primes.size();
			if (alreadyIn.find(index) == alreadyIn.end()) {
				answer[i++] = primes.at(index);
				alreadyIn.insert(index);
			}
		}
		return answer;
	}
};

#endif /* PRIMEGENERATOR_H_ */
