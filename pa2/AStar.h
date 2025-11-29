#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

#include "Element.h"
#include "Graph.h"
using namespace std;

#ifndef AStar_h
#define AStar_h

class AStar : public Graph {
    
public:
    
    int numEdgesRelaxed;
    
    AStar() {
    }
    
    AStar(Graph &g) : Graph(g) {
    }
    
    ~AStar() {
    }
    
    int execute(int source, int target) { // complete this function
    }
    
protected:
    
    virtual int heuristic(int source, int target) = 0;
};

#endif /* AStar_h */
