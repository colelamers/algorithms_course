package pa1;

import java.io.*;
import java.util.*;

public class TestBloomFilter {

    //static final int n = 1000000; // Number of insertions (data size).
    static final int n = 2000000; // Number of insertions (data size).
    //static final int universe = 4*n; // Universe size. Also, number of searches.
    static final int universe = 8*n; // Universe size. Also, number of searches.
    //static final int alpha = 16; // Load factor. So, the table size is n*alpha bits.
    static final int alpha = 32; // Load factor. So, the table size is n*alpha bits.
    static final int beta = (int) Math.ceil(Math.log(2) * alpha); // Number of hash functions. Optimized for load factor.
    static final Random rand = new Random(System.currentTimeMillis());

    static final String DATA_PATH = "dataBloom.txt";

    private static void generateBloomData() throws IOException {
        StringBuilder out = new StringBuilder();
        for (int i = 0; i < n; i++)
            out.append(rand.nextInt(universe)).append("\n");

        BufferedWriter bw = new BufferedWriter(new FileWriter(DATA_PATH));
        bw.write(out.toString());
        bw.close();
    }

    private static void testBloomFilter() throws Exception {

        BloomFilter bf = new BloomFilter(alpha * n, beta, universe);
        HashSet<Integer> hashSet = new HashSet<>();

        Scanner in = new Scanner(new FileInputStream(DATA_PATH));
        double totalInsTimeHash = 0; // to compute average insertion time in HashSet
        double totalInsTimeBF = 0; // to compute average insertion time in Bloom Filter

        while (in.hasNextInt()) {
            int key = in.nextInt();

            long currTime = System.currentTimeMillis();
            bf.insert(key);
            totalInsTimeBF += System.currentTimeMillis() - currTime;

            currTime = System.currentTimeMillis();
            hashSet.add(key);
            totalInsTimeHash += System.currentTimeMillis() - currTime;
        }
        in.close();

        double falsePos = 0; // to compute the false positive rate
        int success = 0; // to compute the number of successful searches
        double falseNeg = 0; // to compute the false negative rate
        double totalSearchTimeHash = 0; // to compute average search time in HashSet
        double totalSearchTimeBF = 0; // to compute average search time in Bloom Filter

        for (int key = 0; key < universe; key++) {

            long currTime = System.currentTimeMillis();
            boolean bfContains = bf.search(key);
            totalSearchTimeBF += System.currentTimeMillis() - currTime;

            currTime = System.currentTimeMillis();
            boolean hashContains = hashSet.contains(key);
            totalSearchTimeHash += System.currentTimeMillis() - currTime;

            if (bfContains && !hashContains)
                falsePos++;
            else if (hashContains) {
                success++;
                if (!bfContains)
                    falseNeg++;
            }
        }

        System.out.println("\nData size = " + n);
        System.out.println("Universe size = " + universe);
        System.out.println("Load factor = " + alpha);
        System.out.println("Number of hash functions = " + beta);

        System.out.println("\n% of Successful Searches = " + 100.00 * success / universe
                + "% (" + success + " out of " + universe + ")");
        System.out.println("False Positive Rate = " + 100 * falsePos / universe + "%");
        System.out.println("False Negative Rate = " + 100 * falseNeg / universe + "%");

        System.out.println("\nAverage Insertion Time: Hash = " + totalInsTimeHash / n
                + "; BF = " + totalInsTimeBF / n);
        System.out.println("Average Search Time: Hash = " + totalSearchTimeHash / universe
                + "; BF = " + totalSearchTimeBF / universe);
    }



    public static void main(String[] args) throws Exception {
        //generateBloomData();
        testBloomFilter();
    }
}
