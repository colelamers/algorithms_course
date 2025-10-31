import java.util.ArrayList;
import java.util.HashSet;

public class MinHash {

	private static int hashCode(String str, int prime) {
		int hashCode = 0;
		for (int i = 0; i < str.length(); ++i) {
			hashCode = (2 * hashCode + str.charAt(i)) % prime;
		}
		return hashCode;
	}


	public static int minHashCode(ArrayList<String> words, int shingles, int prime) {
		int minHash = Integer.MAX_VALUE;

		for (int i = 0; i <= words.size() - shingles; ++i) {
			StringBuilder shingle = new StringBuilder();
			for (int j = 0; j < shingles; ++j) {
				shingle.append(words.get(i + j));
			}
			int hash = hashCode(shingle.toString(), prime);
			if (hash < minHash) {
				minHash = hash;
			}
		}

		return minHash;
	}
}
