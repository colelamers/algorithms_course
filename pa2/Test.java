package pa2;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.*;

public class Test {

	static final String DATA_FOLDER = "Data/";
	static final String GRID_LANDMARK_FOLDER = DATA_FOLDER + "LandmarksGrid/";
	static final String RANDOM_LANDMARK_FOLDER = DATA_FOLDER + "LandmarksRandom/";

	//static final int NUM_PAIRS = 10;
	static final int NUM_PAIRS = 25;
	static final int NUM_GRID_SIZES = 5;

	static final String[] REGIONS = {"NewYork", "Colorado", "NorthWest", "California", "East", "West"}; // "Central", "USA"

	static final String LENGTH_FILE_EXTENSION = ".len";
	static final String COORDINATES_FILE_EXTENSION = ".co";

	static final String FROM_GRID_LANDMARK_FILE_EXTENSION = ".grid.from";
	static final String TO_GRID_LANDMARK_FILE_EXTENSION = ".grid.to";
	static final String FROM_RANDOM_LANDMARK_FILE_EXTENSION = ".random.from";
	static final String TO_RANDOM_LANDMARK_FILE_EXTENSION = ".random.to";

	static final Random rand = new Random();

	private static Graph loadGraph(int regionIndex) throws FileNotFoundException {
		System.out.printf("Loading %s...", REGIONS[regionIndex]);
		Graph g = GraphReader.readWeightedGraph(DATA_FOLDER + REGIONS[regionIndex] + LENGTH_FILE_EXTENSION);
		g.coordinates = GraphReader.readCoordinates(DATA_FOLDER + REGIONS[regionIndex] + COORDINATES_FILE_EXTENSION);
		System.out.println("Done!\n");
		return g;
	}

	private static void compare(int regionIndex, Graph g) throws Exception {
		int[] sources = new int[NUM_PAIRS];
		int[] targets = new int[NUM_PAIRS];
		System.out.printf("Testing with %d source-target pairs for %s", NUM_PAIRS, REGIONS[regionIndex]);
		for (int i = 0; i < NUM_PAIRS; i++) {
			sources[i] = rand.nextInt(g.numVertices);
			targets[i] = rand.nextInt(g.numVertices);
		}
		Dijkstra_P2P p2p = new Dijkstra_P2P(g);
		Dijkstra_Bidirectional bidir = new Dijkstra_Bidirectional(g);
		AStar_Euclidean euclidean = new AStar_Euclidean(g);
		AStar_Landmark[] gridLandmarks = new AStar_Landmark[NUM_GRID_SIZES];
		AStar_Landmark[] randomLandmarks = new AStar_Landmark[NUM_GRID_SIZES];
		for (int i = 0; i < NUM_GRID_SIZES; i++) {
			int n = i + 2;
			String fileFromGridLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_GRID_LANDMARK_FILE_EXTENSION + "." + (n * n);
			String fileToGridLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_GRID_LANDMARK_FILE_EXTENSION + "." + (n * n);
			String fileFromRandomLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_RANDOM_LANDMARK_FILE_EXTENSION + "." + (n * n);
			String fileToRandomLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_RANDOM_LANDMARK_FILE_EXTENSION + "." + (n * n);
			gridLandmarks[i] = new AStar_Landmark(g, fileFromGridLandmark, fileToGridLandmark);
			randomLandmarks[i] = new AStar_Landmark(g, fileFromRandomLandmark, fileToRandomLandmark);
		}

		double p2pTime = 0, p2pEdges = 0;
		double bidirectionalTime = 0, bidirectionalEdges = 0;
		double euclideanTime = 0, euclideanEdges = 0;
		double[] gridTime = new double[NUM_GRID_SIZES];
		double[] gridEdges = new double[NUM_GRID_SIZES];
		double[] randomTime = new double[NUM_GRID_SIZES];
		double[] randomEdges = new double[NUM_GRID_SIZES];
		long start;

		for (int i = 0; i < NUM_PAIRS; i++) {
			int s = sources[i];
			int t = targets[i];

			start = System.currentTimeMillis();
			int p2p_Distance = p2p.execute(s, t);
			p2pTime += System.currentTimeMillis() - start;
			p2pEdges += p2p.numEdgesRelaxed;

			start = System.currentTimeMillis();
			int bidirectional_Distance = bidir.execute(s, t);
			bidirectionalTime += System.currentTimeMillis() - start;
			bidirectionalEdges += bidir.numEdgesRelaxed;

			if (p2p_Distance != bidirectional_Distance)
				throw new Exception("Bidirectional Dijkstra code is wrong!");

			start = System.currentTimeMillis();
			int euclidean_Distance = euclidean.execute(s, t);
			euclideanTime += System.currentTimeMillis() - start;
			euclideanEdges += euclidean.numEdgesRelaxed;

			if (p2p_Distance != euclidean_Distance)
				throw new Exception("Euclidean A* code is wrong!");

			for (int j = 0; j < NUM_GRID_SIZES; j++) {
				start = System.currentTimeMillis();
				int gridDistance = gridLandmarks[j].execute(s, t);
				gridTime[j] += System.currentTimeMillis() - start;
				gridEdges[j] += gridLandmarks[j].numEdgesRelaxed;
				if (p2p_Distance != gridDistance)
					throw new Exception("Grid Landmark A* code is wrong!");

				start = System.currentTimeMillis();
				int randomDistance = randomLandmarks[j].execute(s, t);
				randomTime[j] += System.currentTimeMillis() - start;
				randomEdges[j] += randomLandmarks[j].numEdgesRelaxed;
				if (p2p_Distance != randomDistance)
					throw new Exception("Random Landmark A* code is wrong!");
			}
		}

		System.out.println("\n\nP2P: Avg. Time = " + p2pTime / NUM_PAIRS
				+ ", Avg. no. of edges relaxed = " + p2pEdges / NUM_PAIRS);
		System.out.println("Bi-directional: Avg. Time = " + bidirectionalTime / NUM_PAIRS
				+ ", Avg. no. of edges relaxed = " + bidirectionalEdges / NUM_PAIRS);
		System.out.println("Euclidean: Avg. Time = " + euclideanTime / NUM_PAIRS
				+ ", Avg. no. of edges relaxed = " + euclideanEdges / NUM_PAIRS);
		for (int j = 0; j < NUM_GRID_SIZES; j++) {
			int n = j + 2;
			System.out.println("\nGrid Landmark(" + n * n + "): Avg. Time = " + gridTime[j] / NUM_PAIRS
					+ ", Avg. no. of edges relaxed = " + gridEdges[j] / NUM_PAIRS);
			System.out.println("Random Landmark(" + n * n + "): Avg. Time = " + randomTime[j] / NUM_PAIRS
					+ ", Avg. no. of edges relaxed = " + randomEdges[j] / NUM_PAIRS);
		}
	}

	private static void preComputeGrid(int regionIndex, int gridDim, Graph g) throws IOException {
		System.out.printf("Creating %d grid landmarks for %s...", gridDim * gridDim, REGIONS[regionIndex]);
		String fileFromLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_GRID_LANDMARK_FILE_EXTENSION + "." + (gridDim * gridDim);
		String fileToLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_GRID_LANDMARK_FILE_EXTENSION + "." + (gridDim * gridDim);
		LandmarkGenerator.makeGridLandmarks(g, gridDim, fileFromLandmark, fileToLandmark);
		System.out.println("Done!");
	}

	private static void preComputeRandom(int regionIndex, int numLandmarks, Graph g) throws IOException {
		System.out.printf("Creating %d random landmarks for %s...", numLandmarks, REGIONS[regionIndex]);
		String fileFromLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_RANDOM_LANDMARK_FILE_EXTENSION + "." + (numLandmarks);
		String fileToLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_RANDOM_LANDMARK_FILE_EXTENSION + "." + (numLandmarks);
		LandmarkGenerator.makeRandomLandmarks(g, numLandmarks, fileFromLandmark, fileToLandmark);
		System.out.println("Done!");
	}

	private static void generateRandomLandmarks(int regionIndex, Graph g) throws IOException {
		preComputeRandom(regionIndex, 4, g);
		preComputeRandom(regionIndex, 9, g);
		preComputeRandom(regionIndex, 16, g);
		preComputeRandom(regionIndex, 25, g);
		preComputeRandom(regionIndex, 36, g);
		System.out.println();
	}

	private static void generateGridLandmarks(int regionIndex, Graph g) throws IOException {
		preComputeGrid(regionIndex, 2, g);
		preComputeGrid(regionIndex, 3, g);
		preComputeGrid(regionIndex, 4, g);
		preComputeGrid(regionIndex, 5, g);
		preComputeGrid(regionIndex, 6, g);
		System.out.println();
	}

	public static void main(String[] args) throws Exception {

		// 0: "NewYork"
		// 1: "Colorado"
		// 2: "NorthWest"
		// 3: "California"
		// 4: "East"
		// 5: "West"
		//for (int i = 5; i >= 0; --i){
		for (int i = 0; i < 6; ++i){

		//int regionIndex = i;
		int regionIndex = i;
		Graph g = loadGraph(regionIndex);

		/**
		 * The generate calls should be executed once per region to ensure the landmarks are created.
		 * Then, comment out the calls.
		 */
		generateRandomLandmarks(regionIndex, g);
		generateGridLandmarks(regionIndex, g);

		compare(regionIndex, g);
		}

	}
}
