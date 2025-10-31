import java.util.ArrayList;

public class LZ78Element {

	public String nodeIDBits; // this is the bit-string representing the nodes in the LZ78 output
	public ArrayList<Character> chars; // these are the characters in the LZ78 output

	public LZ78Element(String nodeIDBits, ArrayList<Character> nextChars) {
		this.nodeIDBits = nodeIDBits;
		this.chars = nextChars;
	}

	public LZ78Element() {
	}

	public int size() {
		return this.chars.size();
	}
}
