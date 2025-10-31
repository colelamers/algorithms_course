package pa1;

import java.math.BigInteger;
import java.util.Random;

public class UniversalHashing {
    private int a, b, p, m;
    private static final boolean LOGGER = true;
    private static Random rand = new Random(System.currentTimeMillis());

    public UniversalHashing(int _prime, int _tableSize) {
        p = _prime;
        m = _tableSize;
        a = rand.nextInt(1, p);
        b = rand.nextInt(p);
        if (LOGGER)
            System.out.printf("Prime = %8d, a = %8d, b = %8d\n", p, a, b);
    }

    public int hash(int key) {
        BigInteger x = BigInteger.valueOf(a * key + b);
        int hashCode = x.mod(BigInteger.valueOf(p)).mod(BigInteger.valueOf(m)).intValue();
        return hashCode;
    }
}
