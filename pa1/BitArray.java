package pa1;

public class BitArray {

    private byte[] arr;
    private int m;

    private int _arrSize;

    public BitArray(int _size) {
        this.m = _size;
        _arrSize = _size % 8 != 0 ? 1 + _size / 8 : _size / 8;
        arr = new byte[_arrSize];
    }

    public boolean access(int index) {
        if (index >= m || index < 0)
            throw new IndexOutOfBoundsException(
                    String.format("Index %d is out of bounds. It must be in [0,%d]", index, m - 1));
        return ((arr[index / 8] >> (7 - index % 8)) & 1) == 1;
    }

    public void set(int index) {
        if (index >= m || index < 0)
            throw new IndexOutOfBoundsException(
                    String.format("Index %d is out of bounds. It must be in [0,%d]", index, m - 1));
        arr[index / 8] |= (1 << (7 - index % 8));
    }

    public void clear(int index) {
        if (index >= m || index < 0)
            throw new IndexOutOfBoundsException(
                    String.format("Index %d is out of bounds. It must be in [0,%d]", index, m - 1));
        arr[index / 8] &= ~(1 << (7 - index % 8));
    }

    public int size() {
        return m;
    }

    public static void main(String[] args) {
        BitArray bf = new BitArray(12);
        bf.set(0);
        bf.set(1);
        bf.set(5);
        bf.set(8);
        for (int i = 0; i < 12; i++)
            System.out.println(i + ":" + bf.access(i));

        bf.clear(1);
        System.out.println();
        for (int i = 0; i < 12; i++)
            System.out.println(i + ":" + bf.access(i));
    }
}
