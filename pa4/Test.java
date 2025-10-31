import java.io.IOException;

public class Test {

	private static final int MAX_PRIME_LENGTH_IN_BITS = 24; // DO NOT EXCEED 30. Currently supported up to primes <= 2^30
	private static final int NUM_PRIMES = 20;
	private static final String DIRECTORY = "Data/";

	public static void main(String[] args) throws IOException {

		int[] primes = PrimeGenerator.largePrimes(MAX_PRIME_LENGTH_IN_BITS, NUM_PRIMES);
		for (double jaccard_threshold : new double[]{0.3,0.5, 0.7, 0.9}){
			System.out.printf("== JACCARD THRESHOLD: %.2f ==\n", jaccard_threshold);
			System.out.print("--- articles100\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "articles100/");
			System.out.print("--- articles1000\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "articles1000/");
			System.out.print("--- articles2500\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "articles2500/");
			System.out.print("--- articles10000\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "articles10000/");
			System.out.print("--- setA\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "setA/");
			System.out.print("--- setB\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "setB/");
			System.out.print("--- setC\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "setC/");
			System.out.print("--- setD\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "setD/");
			System.out.print("--- setE\n");
			PlagiarismDetector.run(jaccard_threshold, primes, DIRECTORY + "setE/");
		}
	}
}
