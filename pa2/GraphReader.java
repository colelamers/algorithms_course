package pa2;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.*;

public class GraphReader {

    public static Graph readWeightedGraph(String filePath) throws FileNotFoundException {
        Scanner fileReader = new Scanner(new FileInputStream(filePath));
        Graph g = new Graph();
        g.numVertices = fileReader.nextInt();
        g.numEdges = fileReader.nextInt();

        g.adjList = new ArrayList<>(g.numVertices);
        for (int i = 0; i < g.numVertices; i++)
            g.adjList.add(new ArrayList<Edge>());

        while (fileReader.hasNext()) {
            int src = fileReader.nextInt();
            int dest = fileReader.nextInt();
            int weight = fileReader.nextInt();
            Edge edge = new Edge(src, dest, weight);
            g.adjList.get(src).add(edge);
        }
        fileReader.close();
        if (isUndirected(g.adjList)) {
            g.is_undirected = true;
            g.revAdjList = g.adjList;
        } else {
            g.is_undirected = false;
            g.revAdjList = new ArrayList<>(g.numVertices);
            for (int i = 0; i < g.numVertices; i++)
                g.revAdjList.add(new ArrayList<Edge>());
            for (ArrayList<Edge> edges : g.adjList)
                for (Edge e : edges)
                    g.revAdjList.get(e.dest).add(new Edge(e.dest, e.src, e.weight));
        }
        return g;
    }

    private static boolean isUndirected(List<ArrayList<Edge>> adjList) {
        TreeSet<Edge> fwdEdges = new TreeSet<>((o1, o2) -> {
            if (o1.src != o2.src)
                return o1.src - o2.src;
            if (o1.dest != o2.dest)
                return o1.dest - o2.dest;
            return o1.weight - o2.weight;
        });

        for (ArrayList<Edge> edges : adjList)
            fwdEdges.addAll(edges);

        for (ArrayList<Edge> edges : adjList)
            for (Edge e : edges)
                if (!fwdEdges.contains(new Edge(e.dest, e.src, e.weight)))
                    return false;
        return true;
    }

    public static List<Vertex> readCoordinates(String filePath) throws FileNotFoundException {
        Scanner fileReader = new Scanner(new FileInputStream(filePath));
        int numVertices = fileReader.nextInt();
        List<Vertex> coordinates = new ArrayList<>(numVertices);
        while (fileReader.hasNext()) {
            fileReader.nextInt();
            coordinates.add(new Vertex(fileReader.nextDouble(), fileReader.nextDouble()));
        }
        return coordinates;
    }
}
