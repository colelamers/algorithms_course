#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#ifndef GRAPH_H_
#define GRAPH_H_

class Vertex {
    
public:
    
    double x;
    double y;
    
    Vertex() {
        
    }
    
    Vertex(double xArg, double yArg) {
        x = xArg;
        y = yArg;
    }
};

class Edge {

public:

    int src, dest, weight;
    
    Edge() {
        
    }

    Edge(int src, int dest, int weight) {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }

    string toString() {
        return "<" + std::to_string(src) + ", " + std::to_string(dest) + ", "
                + std::to_string(weight) + ">";
    }
};

class EdgeComparator {

public:

    bool operator()(const Edge &arg1, const Edge &arg2) const {
        if (arg1.src != arg2.src)
            return arg1.src < arg2.src;
        if (arg1.dest != arg2.dest)
            return arg1.dest < arg2.dest;
        if (arg1.weight != arg2.weight)
            return arg1.weight < arg2.weight;
        return true;
    }
};

class Graph {
    
public:
    
    int numVertices;
    int numEdges;
    vector<vector<Edge>> adjList;
    vector<vector<Edge>> *revAdjList;
    vector<Vertex> coordinates;
    bool is_undirected;
    
    Graph() {
        numVertices = 0;
        numEdges = 0;
    }
    
    Graph(Graph &g) {
        numVertices = g.numVertices;
        numEdges = g.numEdges;
        adjList = g.adjList;
        revAdjList = g.revAdjList;
        coordinates = g.coordinates;
        is_undirected = g.is_undirected;
    }
    
    ~Graph() {
        if (!is_undirected)
            delete revAdjList;
    }
};

#endif /* GRAPH_H_ */
