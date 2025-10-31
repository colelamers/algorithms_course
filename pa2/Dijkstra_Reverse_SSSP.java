package pa2;

import java.util.PriorityQueue;

public class Dijkstra_Reverse_SSSP extends Graph {

	public Dijkstra_Reverse_SSSP(Graph g) {
		super(g);
	}

	public int[] execute(int source) {

		int[] distance = new int[numVertices];
		boolean[] closed = new boolean[numVertices];

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
			if (closed[minVertex])
				continue;
			closed[minVertex] = true;
			for (Edge adjEdge : revAdjList.get(minVertex)) {
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
		return distance;
	}
}
