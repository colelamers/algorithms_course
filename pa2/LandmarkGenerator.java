package pa2;

import java.io.IOException;
import java.util.HashSet;
import java.util.List;
import java.util.Random;

public class LandmarkGenerator {

    private static int euclidean(List<Vertex> coordinates, int vertex, double xCenter, double yCenter) {
        double diffX = coordinates.get(vertex).x - xCenter;
        double diffY = coordinates.get(vertex).y - yCenter;
        return (int) Math.sqrt(diffX * diffX + diffY * diffY);
    }

    private static void precomputeLandmarkDistances(Graph g, String fromLandmarkPath, String toLandmarkPath, HashSet<Integer> landmarks) throws IOException
    {
        // Compute distances using pa2.Dijkstra_SSSP to get
        // the distances from the current landmark.
        // Then store them in a 2D array
        int[][] from = new int[landmarks.size()][g.numVertices];
        int index = 0;
        for (int landmark : landmarks) {
            from[index] = new Dijkstra_SSSP(g).execute(landmark);
            ++index;
        }
        // And Write to file
        LandmarkReaderWriter.writeDistances(from, landmarks.size(), g.numVertices, fromLandmarkPath);
    }

    /**
     * Creates n random landmarks.
     */
    public static void makeRandomLandmarks(Graph g, int n, String fromLandmarkPath, String toLandmarkPath) throws IOException {

        HashSet<Integer> landmarks = new HashSet<>();
        Random rand = new Random();
        while (landmarks.size() != n)
            landmarks.add(rand.nextInt(g.numVertices));
        precomputeLandmarkDistances(g, fromLandmarkPath, toLandmarkPath, landmarks);
    }

    /**
     * Creates nxn grid landmarks.
     */
    public static void makeGridLandmarks(Graph g, int gridDim, String fromLandmarkPath, String toLandmarkPath) throws IOException {
        // From PA2.pdf
        // Create landmarks in a grid using the graph's
        // coordinates and vertices
        double maxX = 0.0;
        double maxY = 0.0;
        double minY = Double.MAX_VALUE;
        double minX = Double.MAX_VALUE;

        // Find min-max's of x and y
        List<Vertex> coordinates = g.coordinates;
        for (Vertex v : coordinates) {
            maxX = Math.max(maxX, v.x);
            maxY = Math.max(maxY, v.y);
            minX = Math.min(minX, v.x);
            minY = Math.min(minY, v.y);
        }

        // Calculate grid cell sizes
        double gridXSize = (maxX - minX) / gridDim;
        double gridYSize = (maxY - minY) / gridDim;

        // For each center point of the grid cell
        HashSet<Integer> landmarks = new HashSet<>();
        for (int i = 0; i < gridDim; ++i) {
            for (int j = 0; j < gridDim; ++j) {
                // Find the center of the grid
                double gridCenterX = minX + (i + 0.5) * gridXSize;
                double gridCenterY = minY + (j + 0.5) * gridYSize;
                // Find the vertex closest to the center point
                // using the euclidean function
                double minDist = Double.MAX_VALUE;
                int closestVertex = -1;
                for (int k = 0; k < coordinates.size(); ++k) {
                    int distance = euclidean(coordinates, k, gridCenterX, gridCenterY);
                    if (distance < minDist) {
                        minDist = distance;
                        closestVertex = k;
                    }
                }
                landmarks.add(closestVertex);
            }
        }
        precomputeLandmarkDistances(g, fromLandmarkPath, toLandmarkPath, landmarks);
    }
}
