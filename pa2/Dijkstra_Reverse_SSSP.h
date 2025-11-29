#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#include "Element.h"
#include "Graph.h"
using namespace std;

#ifndef RevDijkstra_h
#define RevDijkstra_h

class Dijkstra_Reverse_SSSP: public Graph {
    
public:
    
    int numEdgesRelaxed;

    Dijkstra_Reverse_SSSP(Graph &g) : Graph(g) {
    }

    ~Dijkstra_Reverse_SSSP() {
    }

    vector<int> execute(int source) {
        
        numEdgesRelaxed = 0;
        
        vector<bool> closed;
        vector<int> distance;
        closed.resize(numVertices);
        distance.reserve(numVertices);

        for (int i = 0; i < numVertices; i++) {
            distance.push_back(INT_MAX);
            closed[i] = false;
        }
        
        distance[source] = 0;
        priority_queue<Element, vector<Element>, ElementComparator> open;
        open.push(Element(source, 0));
        
        while (open.size() > 0) {
            Element minElement = open.top();
            open.pop();
            int minVertex = minElement.item;
            if (closed[minVertex])
                continue;
            closed[minVertex] = true;
            for (Edge &adjEdge : revAdjList->at(minVertex)) {
                int adjVertex = adjEdge.dest;
                if (!closed[adjVertex]) {
                    int dist = distance[minVertex] + adjEdge.weight;
                    if (dist < distance[adjVertex]) {
                        distance[adjVertex] = dist;
                        open.push(Element(adjVertex, dist));
                    }
                }
            }
        }
        return distance;
    }
};

#endif /* RevDijkstra_h */
