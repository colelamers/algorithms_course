package pa2;

import java.util.ArrayList;
import java.util.List;

class Vertex {
	public double x;
	public double y;

	public Vertex(double xArg, double yArg) {
		x = xArg;
		y = yArg;
	}
}

class Edge {

	int src, dest, weight;

	public Edge(int src, int dest, int weight) {
		this.src = src;
		this.dest = dest;
		this.weight = weight;
	}

	public Edge(int src, int dest) {
		this.src = src;
		this.dest = dest;
		this.weight = 1;
	}

	public String toString() {
		return String.format("<%d, %d, %d>", src, dest, weight);
	}
}

class Graph {

	public int numVertices;
	public int numEdges;
	public List<ArrayList<Edge>> adjList;
	public List<ArrayList<Edge>> revAdjList;
	public List<Vertex> coordinates;
	public boolean is_undirected;

	public Graph(Graph g) {
		numVertices = g.numVertices;
		numEdges = g.numEdges;
		adjList = g.adjList;
		revAdjList = g.revAdjList;
		coordinates = g.coordinates;
		is_undirected = g.is_undirected;
	}

	public Graph() {}
}
