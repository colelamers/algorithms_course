package pa2;

import java.util.*;

public abstract class AStar extends Graph {

    public int numEdgesRelaxed;

    public AStar(Graph g) {
        super(g);
    }

    public int execute(int source, int target) {
        // Taken from P2PShortestPath.pdf
        // This is basically the same as pa2.Dijkstra_P2P except you als
        // track the heuristic to estimate the distance cost to the
        // target node.
        numEdgesRelaxed = 0;
        int[] dist = new int[numVertices];
        boolean[] closed = new boolean[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            dist[i] = Integer.MAX_VALUE;
            closed[i] = false;
        }

        dist[source] = 0;
        PriorityQueue<Element> open = new PriorityQueue<Element>(new ElementComparator());
        Element startElementNode = new Element(source, 0);
        open.add(startElementNode);

        // For tracking elements in the queue to ensure no duplicates exist
        while (open.size() > 0) {
            Element current = open.poll();
            int u = current.item;

            // If target found, return the distance to the target node
            if (u == target) {
                return dist[target];
            }

            // Skip if vertex is closed
            if (closed[u]) {
                continue;
            }

            closed[u] = true;

            // Check if it can be added to the open edges
            for (Edge edge : adjList.get(u)) {
                int v = edge.dest;
                if (closed[v]) {
                    continue;
                }

                int len = dist[u] + edge.weight;
                if (len < dist[v]) {
                    dist[v] = len;
                    ++numEdgesRelaxed;
                    open.add(new Element(v, len + heuristic(v, target)));
                }
            }
        }

        return Integer.MAX_VALUE; // Target unreachable
    }

    // Abstract heuristic method to be implemented by subclasses
    protected abstract int heuristic(int v, int target);
}
