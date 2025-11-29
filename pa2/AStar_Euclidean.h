#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

#include "AStar.h"
using namespace std;

#ifndef Euclidean_h
#define Euclidean_h

class AStar_Euclidean: public AStar {
    
public:

    AStar_Euclidean(Graph &g) : AStar(g) {
    }

    ~AStar_Euclidean() {
    }
    
protected:
    
    int heuristic(int v, int target) { // complete this function
    }
};

#endif /* Euclidean_h */
