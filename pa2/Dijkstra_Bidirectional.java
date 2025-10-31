package pa2;

import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;

public class Dijkstra_Bidirectional extends Graph {

	public int numEdgesRelaxed;

	public Dijkstra_Bidirectional(Graph g) {
		super(g);
	}

	public int execute(int source, int target) {
		// Interpreted from P2PShortestPath.pdf document
		// If the source and target are the same, the distance is 0
		if (source == target) {
			return 0;
		}

		// Initialize distances, open and closed sets, and shortestPath
		// Match dikstra_P2P
		numEdgesRelaxed = 0;
		int[] distSource = new int[numVertices];
		int[] distTarget = new int[numVertices];
		boolean[] closedSource = new boolean[numVertices];
		boolean[] closedTarget = new boolean[numVertices];
		for (int i = 0; i < numVertices; ++i) {
			distSource[i] = Integer.MAX_VALUE;
			distTarget[i] = Integer.MAX_VALUE;
			closedSource[i] = false;
			closedTarget[i] = false;
		}

		distSource[source] = 0;
		distTarget[target] = 0;

		PriorityQueue<Element> pqSource = new PriorityQueue<Element>(new ElementComparator());
		PriorityQueue<Element> pqTarget = new PriorityQueue<Element>(new ElementComparator());
		pqSource.add(new Element(source, 0));
		pqTarget.add(new Element(target, 0));

		int shortestPath = Integer.MAX_VALUE;
		while (pqSource.size() > 0 || pqTarget.size() > 0) {
			int minSource = getMinVal(pqSource.peek());
			int minTarget = getMinVal(pqTarget.peek());

			if (minSource + minTarget >= shortestPath) {
				// Path found, send back the best Distance
				return shortestPath;
			}
			else if (minSource <= minTarget) {
				// Relax edges for the source side
				shortestPath = Dijkstra(pqSource, adjList, closedSource, distSource, distTarget, shortestPath);
			}
			else {
				// Relax edges from the target side (just swapping target with source as args)
				shortestPath = Dijkstra(pqTarget, revAdjList, closedTarget, distTarget, distSource, shortestPath);
			}
		}
		// No path found
		return -1;
	}

	private int getMinVal(Element qElement){
		// If the peek() element is not null, then return that value,
		// otherwise just set the max integer value as the number
		if (qElement != null){
			return qElement.priority;
		}
		else {
			return Integer.MAX_VALUE;
		}
	}

	private int Dijkstra(PriorityQueue<Element> pQueue, List<ArrayList<Edge>> tAdjEdge,
						 boolean[] closed, int[] distSource, int[] distTarget, int shortestPath){
		Element minVertex = pQueue.poll();
		int u = minVertex.item;
		if (closed[u]) {
			return shortestPath;
		}

		closed[u] = true;
		this.numEdgesRelaxed += tAdjEdge.get(u).size();
		for (Edge adjEdge : tAdjEdge.get(u)) {
			int v = adjEdge.dest;
			if (!closed[v]) {
				int len = distSource[u] + adjEdge.weight;
				if (len < distSource[v]) {
					distSource[v] = len;
					pQueue.add(new Element(v, distSource[v]));

					// Check if we can update shortestPath
					if (distTarget[v] != Integer.MAX_VALUE &&
							distSource[v] + distTarget[v] < shortestPath) {
						shortestPath = distSource[v] + distTarget[v];
					}
				}
			}
		}

		// Return the best distance to update outside of
		// the dijkstra function's scope
		return shortestPath;
	}
}