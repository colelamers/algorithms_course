package pa2;

import java.util.PriorityQueue;

public class Dijkstra_P2P extends Graph {

	public int numEdgesRelaxed;

	public Dijkstra_P2P(Graph g) {
		super(g);
	}

	public int execute(int source, int target) {

		int[] distance = new int[numVertices];
		boolean[] closed = new boolean[numVertices];
		numEdgesRelaxed = 0;

		for (int i = 0; i < numVertices; i++) {
			distance[i] = Integer.MAX_VALUE;
			closed[i] = false;
		}

		distance[source] = 0;
		PriorityQueue<Element> open = new PriorityQueue<Element>(new ElementComparator());
		open.add(new Element(source, 0));

		while (open.size() > 0) {
			Element minElement = open.remove();
			int minVertex = minElement.item;
			if (minVertex == target)
				break;
			if (closed[minVertex])
				continue;
			closed[minVertex] = true;
			numEdgesRelaxed += adjList.get(minVertex).size();
			for (Edge adjEdge : adjList.get(minVertex)) {
				int adjVertex = adjEdge.dest;
				if (!closed[adjVertex]) {
					int dist = distance[minVertex] + adjEdge.weight;
					if (dist < distance[adjVertex]) {
						distance[adjVertex] = dist;
						open.add(new Element(adjVertex, dist));
					}
				}
			}
		}
		return distance[target];
	}
}
