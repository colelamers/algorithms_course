#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#include "Element.h"
#include "AStar.h"
#include "LandmarkReaderWriter.h"
using namespace std;

#ifndef GridLandmark_h
#define GridLandmark_h

class AStar_Landmark: public AStar {
    
private:
    
    // stores the shortest path lengths from each landmark (row index) to each vertex (column index)
    vector<vector<int>> fromLandmarks;
    
    // stores the shortest path lengths to each landmark (row index) from each vertex (column index)
    // this is relevant for directed graphs only
    vector<vector<int>> toLandmarks;
    
public:
    
    AStar_Landmark() : AStar() {
    }
    
    AStar_Landmark(Graph &g, string fromLandmarkFilePath, string toLandmarkFilePath) : AStar(g) {
        fromLandmarks = LandmarkReaderWriter::readDistances(fromLandmarkFilePath);
        if (g.is_undirected)
            toLandmarks = LandmarkReaderWriter::readDistances(toLandmarkFilePath);
    }
    
    ~AStar_Landmark() {
    }
    
protected:
    
    int heuristic(int v, int target) { // complete this function
    }
};

#endif /* GridLandmark_h */
