#include "Graph.h"
#include <set>

#ifndef GraphReader_h
#define GraphReader_h

class GraphReader {

public:

    static Graph readWeightedGraph(string filePath) {
        Graph g;
        ifstream fileReader(filePath, ios::in);
        
        fileReader >> g.numVertices;
        fileReader >> g.numEdges;
        
        g.adjList.reserve(g.numVertices);
        for (int i = 0; i < g.numVertices; i++)
            g.adjList.push_back(vector<Edge>());
        
        while (fileReader) {
            int src, dest, weight;
            fileReader >> src;
            fileReader >> dest;
            fileReader >> weight;
            Edge edge(src, dest, weight);
            g.adjList.at(src).push_back(edge);
        }
        fileReader.close();
        
        if (isUndirected(g.adjList)) {
            g.revAdjList = &g.adjList;
            g.is_undirected = true;
        }
        else {
            g.is_undirected = false;
            g.revAdjList = new vector<vector<Edge>>();
            g.revAdjList->reserve(g.numVertices);
            for (int i = 0; i < g.numVertices; i++)
                g.revAdjList->push_back(vector<Edge>());
            for (vector<Edge> edges : g.adjList)
                for (Edge e : edges)
                    g.revAdjList->at(e.dest).push_back(Edge(e.dest, e.src, e.weight));
        }
        return g;
    }
    
    static bool isUndirected(vector<vector<Edge>> &adjList) {
        auto edge_compare = [](const Edge &o1, const Edge &o2){
            if (o1.src != o2.src)
                return o1.src < o2.src;
            if (o1.dest != o2.dest)
                return o1.dest < o2.dest;
            return o1.weight < o2.weight;
        };
        set<Edge, decltype(edge_compare)> fwdEdges;
        
        for (vector<Edge> edges : adjList)
            for (Edge e : edges)
                fwdEdges.insert(e);
        
        for (vector<Edge> edges : adjList)
            for (Edge e : edges)
                if (fwdEdges.find(Edge(e.dest, e.src, e.weight)) == fwdEdges.end())
                    return false;
        return true;
    }

    static vector<Vertex> readCoordinates(string filePath) {
        ifstream fileReader(filePath, ios::in);
        int numVertices;
        fileReader >> numVertices;
        vector<Vertex> coordinates;
        coordinates.reserve(numVertices);
        int identifier;
        double x, y;
        while (fileReader >> identifier) {
            fileReader >> x;
            fileReader >> y;
            coordinates.push_back(Vertex(x, y));
        }
        return coordinates;
    }
};

#endif /* GraphReader_h */
