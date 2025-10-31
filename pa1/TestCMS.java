package pa1;

import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;

public class TestCMS {

    static final int universe = 1000;
    static BigInteger n = new BigInteger("0"); // Number of data items in the stream
    /**
     * epsilon is the acceptable error. delta is the acceptable error probability. Both must be < 1.
     * Specifically, Pr(estimate - actual >= n*epsilon) <= delta
     */
    static final double epsilon = 0.01;
    static final double delta = 0.01;
    static final int B = (int) Math.ceil(Math.exp(1)/epsilon); // Number of columns in CMS
    static final int beta = (int) Math.log(1 / delta); // Number of rows/hash functions in CMS
    static final int k = 10000; // k for k-heavy hitters
    static final Random rand = new Random(System.currentTimeMillis());

    /**
     * Since the data size can very large, it cannot be read or written in one shot.
     * This variable is for writing/reading as many numbers to/from the file in one shot.
     * So, CHUNK_SIZE numbers are accumulated and then written to the file.
     * Likewise, a prompt is given when CHUNK_SIZE numbers are read back from the file.
     */
    static final int CHUNK_SIZE = 1000000;

    /**
     * We do not want an even distribution of numbers to simulate real-world scenarios.
     * So, we add a SKEW that will (hopefully) generate some numbers very frequently.
     * This should simulate real-worlds scenarios to the best of our abilities.
     * (Well not really, as there are better ways :-|)
     */
    static final int SKEW = 100000;
    static final String DATA_PATH = "dataCMS.txt";
    private static void generateCMSData() throws IOException {
        StringBuilder out = new StringBuilder();

        BufferedWriter bw = new BufferedWriter(new FileWriter(DATA_PATH));
        Scanner in = new Scanner(System.in);
        char choice = 'Y';
        while (choice == 'Y' || choice == 'y') {
            for (int i = 0; i < CHUNK_SIZE; ) {
                int skew = rand.nextInt(SKEW);
                int val = rand.nextInt(universe);
                for (int j = 0; j < skew && i < CHUNK_SIZE; i++, j++)
                    out.append(val).append("\n");
            }
            bw.write(out.toString());
            n = n.add(BigInteger.valueOf(CHUNK_SIZE));
            System.out.print("Generated " + n + " elements. Do you want more (Yes: Y/y, No: any key)? ");
            choice = in.next().charAt(0);
            out = new StringBuilder();
        }
        System.out.println();
        in.close();
        bw.close();
    }
    private static void testCMS() throws Exception {

        CMS cms = new CMS(beta, B, universe);
        HashMap<Integer, Integer> hashSet = new HashMap<Integer, Integer>();

        Scanner in = new Scanner(new FileReader(DATA_PATH));
        n = new BigInteger("0");
        System.out.println();
        while (in.hasNextInt()) {
            int key = in.nextInt();
            cms.increment(key);

            Integer freq = hashSet.get(key);
            if (freq == null)
                hashSet.put(key, 1);
            else
                hashSet.put(key, 1 + freq);
            n = n.add(BigInteger.valueOf(1));
            if (n.mod(BigInteger.valueOf(CHUNK_SIZE)).compareTo(BigInteger.valueOf(0)) == 0)
                System.out.println("Read " + n + " values.");
        }
        in.close();

        double probabilityError = 0; // for calculating % of cases where (estimate - actual >= n*epsilon)
        double avgDiff = 0; // for calculating avg of (estimate - actual)
        double avgFreq = 0; // for calculating average of actual frequencies
        double expectedFreqError = 0; // for calculating % of cases where (estimate >= actual + n/B)
        double avgErrorInComputingActualFromEstimate = 0; // We guess the actual as (estimate - n/B).
        // Then, we check how much it differs from the actual on average.
        int numUnder = 0; // to compute the number of underestimates

        ArrayList<Integer> actualHH = new ArrayList<>(); // actual heavy-hitters
        ArrayList<Integer> estimatedHH = new ArrayList<>(); // estimated heavy-hitters

        for (int key = 0; key < universe; key++) {
            Integer actual = hashSet.get(key);
            if (actual == null)
                actual = 0;
            int estimate = cms.frequency(key);

            if (estimate < actual)
                numUnder++;

            avgFreq += actual;
            avgDiff += estimate - actual;

            if (n.divide(BigInteger.valueOf((long) (1 / epsilon))).compareTo(BigInteger.valueOf(estimate - actual)) <= 0)
                probabilityError++;

            if (n.divide(BigInteger.valueOf(B)).compareTo(BigInteger.valueOf(estimate - actual)) <= 0)
                expectedFreqError++;

            double actualFromEstimate = estimate - n.divide(BigInteger.valueOf(B)).intValue();
            if (actualFromEstimate < 0)
                actualFromEstimate = 0; // if negative, estimate as 0
            avgErrorInComputingActualFromEstimate += Math.abs(actualFromEstimate - actual);

            if (n.divide(BigInteger.valueOf(k)).compareTo(BigInteger.valueOf(actual)) < 0)
                actualHH.add(key);
            if (n.divide(BigInteger.valueOf(k)).compareTo(BigInteger.valueOf(estimate)) < 0)
                estimatedHH.add(key);
        }
        System.out.println("\nNumber of data points (n): " + n);
        System.out.println("Universe: " + universe);
        System.out.println("Number of columns (B): " + B);
        System.out.println("Number of rows (hash functions): " + beta);
        System.out.println("Epsilon: " + epsilon);
        System.out.println("Delta: " + delta);
        System.out.println("n/B: " + n.divide(BigInteger.valueOf(B)));
        System.out.println("n*epsilon: " + n.divide(BigInteger.valueOf((long) (1 / epsilon))));

        System.out.println("\nNumber of underestimates: " + numUnder);
        System.out.println("Average of actual: " + avgFreq / universe);
        System.out.println("Average of (estimate - actual): " + avgDiff / universe);
        System.out.println("% of cases where (estimate - actual >= n*epsilon): " + 100 * probabilityError / universe + "%");
        System.out.println("% of cases where (estimate >= actual + n/B): " + 100 * expectedFreqError / universe + "%");
        System.out.println("Average difference when we compute actual as (estimate - n/B): "
                + avgErrorInComputingActualFromEstimate / universe);

        System.out.println("\nk for k-heavy hitters: " + k);
        System.out.println("Number of actual heavy-hitters: "
                + actualHH.size());
        System.out.println("Number of estimated heavy-hitters: "
                + estimatedHH.size());
    }

    public static void main(String[] args) throws Exception {
        //generateCMSData();
        testCMS();
    }
}
