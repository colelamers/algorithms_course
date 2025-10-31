package pa1;
import java.util.*;

/**
 * Created By Cole Lamers
 */
public class BloomFilter
{
    private final BitSet _bitArray;
    private final UniversalHashing[] _hashCollection;

    public BloomFilter(int tableSize, int hashNum, int universeSize) throws Exception
    {
        _bitArray = new BitSet(tableSize);
        _hashCollection = new UniversalHashing[hashNum];
        int universeFloor = (int) (1.25 * universeSize);
        int universeCeil = (int) Math.ceil(1.5 * universeSize);
        int primeNum = PrimeGenerator.getPrime(universeFloor, universeCeil);
        for (int i = 0; i < hashNum; ++i)
        {
            // Get hashes based on table size and prime retrieved
            _hashCollection[i] = new UniversalHashing(primeNum, tableSize);
        }
    }

    public void insert(int key)
    {
        for (UniversalHashing hf : _hashCollection)
        {
            _bitArray.set(hf.hash(key));
        }
    }

    public boolean search(int key)
    {
        for (UniversalHashing hf : _hashCollection)
        {
            if (!_bitArray.get(hf.hash(key)))
            {
                return false;
            }
        }
        return true;
    }
}


