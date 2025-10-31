import java.util.*;

public class BWT {
	public static ArrayList<Character> encode(ArrayList<Character> data) {
		int[] suffixArray = SuffixArray.compute(data);
		ArrayList<Character> bwt = new ArrayList<>();
		int n = data.size();

		for (int i = 0; i < n; ++i) {
			int j = n - 1; // use as default
			if (suffixArray[i] > 0) {
				j = suffixArray[i] - 1;
			}
			bwt.add(data.get(j));
		}

		return bwt;
	}

	public static ArrayList<Character> decode(ArrayList<Character> bwt) {
		HashMap<Character, Integer> freq = HelperFunctions.getFrequencies(bwt);
		HashMap<Character, Integer> C = new HashMap<Character, Integer>();
		int counter = 0;

		List<Character> sortedAlphabet = HelperFunctions.getSortedAlphabet(bwt);
		for (char key : sortedAlphabet) {
			C.put(key, counter);
			counter += freq.get(key);
		}

		int n = bwt.size();
		int[] R = new int[n];
		HashMap<Character, Integer> indexCounter = new HashMap<Character, Integer>();
		int terminatorChar = -1; // position of '\0'

		for (int i = 0; i < n; i++) {
			char c = bwt.get(i);
			indexCounter.put(c, indexCounter.getOrDefault(c, 0) + 1);
			R[i] = indexCounter.get(c);

			if (c == '\0') {
				terminatorChar = i;
			}
		}

		ArrayList<Character> decoded = new ArrayList<Character>(bwt);
		for (int i = n - 1; i >= 0; --i) {
			char c = bwt.get(terminatorChar);
			decoded.set(i, c);
			terminatorChar = C.get(c) + (R[terminatorChar] - 1);
		}
		return decoded;
	}

}