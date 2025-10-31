package pa1;

import java.util.Random;

public class PrimeGenerator {

	private static Random rand = new Random(System.currentTimeMillis());

	static public boolean deterministicPrimalityTest(int n) {

		if (n <= 1)
			return false;
		if (n <= 3)
			return true;
		if ((n & 1) == 0)
			return false;
		if (n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19)
			return true;
		if (n <= 21)
			return false;

		int sqrt_n = (int) Math.sqrt(n);

		for (int i = 3; i <= sqrt_n; i += 2)
			if (n % i == 0)
				return false; // definitely composite
		return true; // definitely prime
	}

	/**
	 * This method generates returns a random prime in [LB, UB].
	 * CAUTION: The range must be sufficiently large.
	 */
	static public int getPrime(int LB, int UB) throws Exception {
		if (UB < LB)
			throw new Exception("Lower bound must not be larger than upper bound.");
		int prime;
		do {
			prime = rand.nextInt(LB, UB);
			if (deterministicPrimalityTest(prime))
				break;
		}
		while (true);
		return prime;
	}
}
