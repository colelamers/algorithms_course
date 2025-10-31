package pa1;

/**
 * Created By Cole Lamers
 */
public class CMS
{
    private final int _hashes;
    private final int[][] _cmsTable;
    private final UniversalHashing[] _hashCollection;

    public CMS(int beta, int columns, int universe) throws Exception
    {
        _hashes = beta;
        _cmsTable = new int[_hashes][columns];
        _hashCollection = new UniversalHashing[_hashes];
        int primeNum = PrimeGenerator.getPrime(20 * universe, 25 * universe);
        for (int i = 0; i < _hashes; ++i)
        {
            _hashCollection[i] = new UniversalHashing(primeNum, columns);
        }
    }

    public void increment(int key)
    {
        for (int i = 0; i < _hashes; ++i)
        {
            // You are incrementing the index item in the array here.
            // Ignore the fact that it looks odd and abnormal.
            // This is just for simplicity.
            ++_cmsTable[i][_hashCollection[i].hash(key)];
        }
    }

    public int frequency(int key)
    {
        // Use MAX_VALUE because we need to assume that upon initialization,
        // it is ALWAYS greater than the CMS index item from the hash, so that
        // future checks can be performed.
        int freqCount = Integer.MAX_VALUE;
        for (int i = 0; i < _hashes; ++i)
        {
            // You are fetching frequency count here, compares and
            // returns the lesser of the two
            freqCount = Math.min(freqCount, _cmsTable[i][_hashCollection[i].hash(key)]);
        }
        return freqCount;
    }
}
