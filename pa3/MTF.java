import java.util.ArrayList;
import java.util.Collections;

public class MTF {

	public static MTFElement encode(ArrayList<Character> str) {
		ArrayList<Character> alphabet = HelperFunctions.getSortedAlphabet(str);
		ArrayList<Integer> mtf = new ArrayList<>();
		ArrayList<Character> currentAlphabet = new ArrayList<>(alphabet);

		for (int i = 0; i < str.size(); ++i) {
			char c = str.get(i);
			int j = currentAlphabet.indexOf(c);
			mtf.add(j);

			// Shift elements from 0 to jth position, right
			for (int k = j; k > 0; --k) {
				currentAlphabet.set(k, currentAlphabet.get(k - 1));
			}
			currentAlphabet.set(0, c);
		}

		return new MTFElement(alphabet, mtf);
	}

	public static ArrayList<Character> decode(MTFElement mtf) {
		ArrayList<Character> alphabet = new ArrayList<>(mtf.alphabet);
		Collections.sort(alphabet);
		ArrayList<Character> decoded = new ArrayList<>();

		for (int i = 0; i < mtf.mtf.size(); ++i){
			int j = mtf.mtf.get(i);
			char c = alphabet.get(j);
			decoded.add(c);

			// Shift elements from 0 to jth position, right
			for (int k = j; k > 0; --k) {
				alphabet.set(k, alphabet.get(k - 1));
			}
			alphabet.set(0, c);
		}

		return decoded;
	}
}
