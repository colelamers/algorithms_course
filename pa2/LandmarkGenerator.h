#include "Dijkstra_SSSP.h"
#include "Dijkstra_Reverse_SSSP.h"
#include "LandmarkReaderWriter.h"
#include <vector>
#include <unordered_set>

using namespace std;

#ifndef LandmarkGenerator_h
#define LandmarkGenerator_h

class LandmarkGenerator {
    
    static int euclidean(vector<Vertex> &coordinates, int vertex, double xCenter, double yCenter) {
        double diffX = coordinates.at(vertex).x - xCenter;
        double diffY = coordinates.at(vertex).y - yCenter;
        return (int) sqrt(diffX * diffX + diffY * diffY);
    }
    
    static void precomputeLandmarkDistances(Graph g, string fromLandmarkPath, string toLandmarkPath, unordered_set<int> &landmarks) { // complete this function
    }
    
public:
    
    static void makeRandomLandmarks(Graph &g, int n, string fromLandmarkPath, string toLandmarkPath) {
        unordered_set<int> landmarks;
        while (landmarks.size() != n)
            landmarks.insert(rand() % g.numVertices);
        precomputeLandmarkDistances(g, fromLandmarkPath, toLandmarkPath, landmarks);
    }
    
    static void makeGridLandmarks(Graph &g, int gridDim, string fromLandmarkPath, string toLandmarkPath) { // complete this function
    }
};

#endif /* LandmarkGenerator_h */
