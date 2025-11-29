#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#include "Element.h"
#include "Graph.h"
using namespace std;

#ifndef Dijkstra_Bidirectional_h
#define Dijkstra_Bidirectional_h

class Dijkstra_Bidirectional: public Graph {
    
public:
    
    int numEdgesRelaxed;

    Dijkstra_Bidirectional(Graph &g) : Graph(g) {
    }

    ~Dijkstra_Bidirectional() {
    }

    int execute(int source, int target) { // complete this function
    }
};

#endif /* Dijkstra_Bidirectional_h */
