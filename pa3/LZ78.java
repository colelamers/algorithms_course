import java.util.ArrayList;
import java.util.Hashtable;

class TrieNode {

	public Hashtable<Character, TrieNode> edges;
	public int id;

	public TrieNode(int id) {
		edges = new Hashtable<Character, TrieNode>();
		this.id = id;
	}

	public TrieNode getChild(char ch) {
		return edges.get(ch);
	}

	public void addChild(int id, char edgeLabel) {
		edges.put(edgeLabel, new TrieNode(id));
	}
}


public class LZ78 {

	// Encoding function for LZ78
	public static LZ78Element encode(ArrayList<Character> str) {
		TrieNode root = new TrieNode(0);
		int k = 1;
		TrieNode curr = root;
		StringBuilder nodeBits = new StringBuilder();
		ArrayList<Character> nextChars = new ArrayList<>();
		for (int c = 0; c < str.size(); ++c){
			char T = str.get(c);
			TrieNode child = curr.getChild(T);

			if (child != null) {
				curr = child;
			} else {
				// log base 2
				int numBits = 1 + (int) Math.floor(Math.log(k) / Math.log(2));
				String nodeIdBinary = String.format("%" + numBits + "s", Integer.toBinaryString(curr.id)).replace(' ', '0');
				nodeBits.append(nodeIdBinary);
				nextChars.add(T);
				curr.addChild(k, T);
				++k;
				curr = root;
			}
		}
		return new LZ78Element(nodeBits.toString(), nextChars);
	}

	// Improved LZ78 Decoding
	public static ArrayList<Character> decode(LZ78Element pair) {
		Hashtable<Integer, Tuple> DICT = new Hashtable<Integer, Tuple>();
		DICT.put(0, new Tuple(0, 0));
		ArrayList<Character> S = new ArrayList<Character>();
		int k = 1, j = 0;
		for (int t = 0; t < pair.chars.size(); ++t) {
			int onePlusLogK = 1 + (int) Math.floor(Math.log(k) / Math.log(2));
			String nodeIDBinary = pair.nodeIDBits.substring(j, j + onePlusLogK);
			int alpha = HelperFunctions.binaryToDecimal(nodeIDBinary);
			StringBuilder X = new StringBuilder();

			if (alpha < DICT.size()) {
				Tuple tuple = DICT.get(alpha);
				int start = tuple.start;
				int end = start + tuple.length;
				for (int i = start; i < end; ++i) {
					X.append(S.get(i));
				}
			}

			StringBuilder Y = X.append(pair.chars.get(t));
			DICT.put(k, new Tuple(S.size(), Y.length()));

			for (char c : Y.toString().toCharArray()) {
				S.add(c);
			}
			j += onePlusLogK;
			k++;
		}
		return S;
	}

	public static class Tuple {
		int start;
		int length;

		public Tuple(int start, int length) {
			this.start = start;
			this.length = length;
		}
	}
}
