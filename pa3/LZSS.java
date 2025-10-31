import java.util.ArrayList;

public class LZSS {

    private static final int LOOKAHEAD_BUFFER = 128;
    private static final int WINDOW = 1024;
    private static final int LENGTH_THRESHOLD = 4; // set to 2 for correctness test

    public static LZSSElement encode(ArrayList<Character> msg) {
        ArrayList<Integer> deltas = new ArrayList<Integer>();
        ArrayList<Integer> lengths = new ArrayList<Integer>();
        ArrayList<Character> nextChars = new ArrayList<Character>();
        StringBuilder identifier = new StringBuilder();

        nextChars.add(msg.get(0));
        identifier.append('0');

        int c = 1;
        while (c < msg.size()) {
            int length = 0, delta = 0;
            for (int j = c - 1; j >= 0 && j >= c - WINDOW; j--) {
                if (j < c - WINDOW)
                    break;
                int l = 0;
                while (c + l < msg.size() && l < LOOKAHEAD_BUFFER && msg.get(c + l).equals(msg.get(j + l))) {
                    l++;
                }
                if (l > length) {
                    length = l;
                    delta = c - j;
                }
            }

            // If length exceeds threshold, encode as a reference
            if (length > LENGTH_THRESHOLD) {
                identifier.append('1');
                deltas.add(delta);
                lengths.add(length);
                nextChars.add(msg.get(c + length));
            } else {
                for (int j = 0; j <= length; ++j) {
                    identifier.append('0');
                    nextChars.add(msg.get(c + j));
                }
            }
            c += length + 1;
        }
        return new LZSSElement(identifier.toString(), deltas, lengths, nextChars);
    }

    public static ArrayList<Character> decode(LZSSElement lzss) {
        ArrayList<Character> msg = new ArrayList<>();
        int d = 0;
        for (int t = 0; t < lzss.identifier.length(); ++t) {
            if (lzss.identifier.charAt(t) == '1') {
                for (int j = 0; j < lzss.length.get(d); ++j) {
                    char c = msg.get(msg.size() - lzss.delta.get(d));
                    msg.add(c);
                }
                ++d;
            }
            msg.add(lzss.next.get(t));
        }
        return msg;
    }
}