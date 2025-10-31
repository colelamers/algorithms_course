package pa2;

import java.io.FileNotFoundException;

public class AStar_Landmark extends AStar {

	// stores the shortest path lengths from each landmark (row index) to each vertex (column index)
	private int[][] from;

	// stores the shortest path lengths to each landmark (row index) from each vertex (column index)
	// this is relevant for directed graphs only
	private int[][] to;

	public AStar_Landmark(Graph g, String fromLandmarkFilePath, String toLandmarkFilePath) throws FileNotFoundException {
		super(g);
		from = LandmarkReaderWriter.readDistances(fromLandmarkFilePath);
		if (!g.is_undirected) {
			to = LandmarkReaderWriter.readDistances(toLandmarkFilePath);
		}
	}


	protected int heuristic(int v, int target) {
		// From PA2 pdf
		// Set Heuristic score and then loop through all
		// landmarks to find the best heuristic estimate
		int H = 0;
		for (int i = 0; i < from.length; ++i) {
			int hScore = Math.abs(from[i][target] - from[i][v]);
			if (hScore > H) {
				H = hScore;
			}
		}

		return H;
	}
}
