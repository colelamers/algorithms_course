package pa2;

import java.io.*;
import java.util.Scanner;

public class LandmarkReaderWriter {

    public static void writeDistances(int[][] arr, int numLandmarks, int numVertices, String filePath) throws IOException
    {
        StringBuilder out = new StringBuilder();
        out.append(numLandmarks).append(" ").append(numVertices).append("\n");
        for (int l = 0; l < numLandmarks; l++) {
            for (int a = 0; a < numVertices; a++) {
                out.append(arr[l][a]);
                if (a != numVertices - 1)
                    out.append(" ");
            }
            if (l != numLandmarks - 1)
                out.append("\n");
        }
        BufferedWriter bw = new BufferedWriter(new FileWriter(filePath));
        bw.write(out.toString());
        bw.close();
    }

    public static int[][] readDistances(String fromLandmarkFilePath) throws FileNotFoundException
    {
        Scanner in = new Scanner(new FileReader(fromLandmarkFilePath));
        int numLandmarks = in.nextInt();
        int numVertices = in.nextInt();
        int[][] distances = new int[numLandmarks][];
        for (int i = 0; i < numLandmarks; i++) {
            distances[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) {
                distances[i][j] = in.nextInt();
            }
        }
        return distances;
    }
}
