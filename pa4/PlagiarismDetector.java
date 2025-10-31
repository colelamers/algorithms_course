import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

public class PlagiarismDetector {
	private static final int SHINGLES = 3;
	//private static final double PLAGIARISM_JACCARD_SIMILARITY_THRESHOLD = 0.7;
	private static double PLAGIARISM_JACCARD_SIMILARITY_THRESHOLD = 0.9;

	public static void run(double jt, int[] primes, String folderPath) throws IOException {
		PLAGIARISM_JACCARD_SIMILARITY_THRESHOLD = jt;
		ArrayList<ArrayList<Integer>> allMinHashCodes = new ArrayList<>();
		ArrayList<String> docIDs = new ArrayList<>();

		File folder = new File(folderPath);
		File[] allFiles = folder.listFiles();
		List<File> txtFiles = new ArrayList<>();

		// Must do this because of the JaccardSimiliarty CSV's. We just
		if (allFiles != null) {
			for (File file : allFiles) {
				if (file.isFile() && file.getName().endsWith(".txt")) {
					txtFiles.add(file);
				}
			}
		}
		// We know the folderPath contains files so I'm ignoring the
		// null checks simply for the experiment.
		for (File file : txtFiles) {
			String cleaned = GetParsedFile(file).toLowerCase(); // just convert all to lower
			// Below filters out auxiliaries and articles if true,
			// false just adds if not empty
			ArrayList<String> words = GetWordsSet(cleaned, false);
			ArrayList<Integer> minHashCodesInThisDoc = new ArrayList<>();
			for (int prime : primes) {
				int minHash = MinHash.minHashCode(words, SHINGLES, prime);
				minHashCodesInThisDoc.add(minHash);
			}

			allMinHashCodes.add(minHashCodesInThisDoc);
			docIDs.add(file.getName());
		}

		HashSet<Integer> codes = new HashSet<>();
		int numDocs = allMinHashCodes.size();

		// Prepare output file to save similarity scores
		String folderName = new File(folderPath).getName();
		Path saveScorePath = Paths.get("Data/SimilarityScores/");
		if (!Files.exists(saveScorePath) && Files.isDirectory(saveScorePath)) {
			Files.createDirectories(saveScorePath);
		}

		// Save data to files
		BufferedWriter writer = new BufferedWriter(new FileWriter(
				String.format("%s/%.1f_%s.txt", saveScorePath,
						PLAGIARISM_JACCARD_SIMILARITY_THRESHOLD, folderName)));

		for (int i = 0; i < numDocs; ++i) {
			for (int j = i + 1; j < numDocs; ++j) {
				codes.clear();
				codes.addAll(allMinHashCodes.get(i));

				int matches = 0;
				for (int hashCode : allMinHashCodes.get(j)) {
					if (codes.contains(hashCode)) {
						++matches;
					}
				}

				double similarity = (double) matches / primes.length;
				if (similarity >= PLAGIARISM_JACCARD_SIMILARITY_THRESHOLD) {
					// Write the similarity results to the file
					writer.write(String.format("%s %s %.2f\n",
							docIDs.get(i), docIDs.get(j), similarity));
				}
			}
		}
		writer.close();
	}

	private static ArrayList<String> GetWordsSet(String cleaned, boolean ignoreCommonWords){
		String[] wordsArray = cleaned.trim().split("\\s+"); // split at space
		ArrayList<String> words = new ArrayList<>();

		// This if check only exist for me to test with the removal of
		// auxiliaries, definite articles, and suffixes
		// This is ugly "code-wise" but it is a simple way to alternate between
		// the two types of words lists.
		if (ignoreCommonWords) {
			Set<String> auxiliaryAndArticleSet = new HashSet<>(Arrays.asList(
					"is", "are", "am", "was", "were", "will", "be", "being", "been", "become",
					"became", "do", "doing", "did", "done", "had", "has", "had", "have",
					"the", "a", "an", "this", "them", "those", "these"
			));

			// This doesn't hold up for words like "thing", "sing", "ring" or
			// strong verbs like run-ran, eat-ate, speak-spoke, etc., and
			// plurals with "s", so there will be false positives.
			List<String> suffixList = Arrays.asList(
					"s", "ed", "ly", "es", "en", "er", "al",
					"ing", "est", "ful", "ive", "less", "ment",
					"ness", "tion"
			);

			for (String word : wordsArray) {
				// Don't add if auxiliary and don't add if empty just in case
				if (!word.isEmpty() && !auxiliaryAndArticleSet.contains(word)) {
					String tWord = word;
					// Algorithmically this could totally be streamlined with a hash
					// map or something to be faster however because the data set is
					// not very large, I'm keeping it this way.
					for (String suffix : suffixList) {
						// If word ends with the current suffix
						if (word.endsWith(suffix)) {
							// Strip the suffix
							tWord = word.substring(0, word.length() - suffix.length());
							break;
						}
					}
					words.add(tWord);
				}
			}
		}
		else{
			for (String word : wordsArray) {
				if (!word.isEmpty()){
					words.add(word);
				}
			}

		}
		return words;
	}

	private static String GetParsedFile(File file) throws IOException {
		StringBuilder content = new StringBuilder();
		BufferedReader br = new BufferedReader(new FileReader(file));
		int c = br.read();
		while (c != -1) {
			if (c == '\n') {
				content.append(' ');
			}
			// This looks only for ASCII characters A-z,0-9
			// which basically enforces English Charset
			else if ((c >= 32 && c <= 126) &&
					(Character.isLetterOrDigit(c)) ||
					(c == ' ')) {
				// Cast as char enforcing lettering and not numbers
				content.append((char) c);
			}
			// Read next line for loop to continue
			c = br.read();
		}
		br.close();
		return content.toString();
	}
}
