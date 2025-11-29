#include "GraphReader.h"
#include "Dijkstra_Bidirectional.h"
#include "Dijkstra_P2P.h"
#include "AStar_Euclidean.h"
#include "AStar_Landmark.h"
#include "LandmarkGenerator.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

static const string DATA_FOLDER = "Data/";
static const string GRID_LANDMARK_FOLDER = DATA_FOLDER + "LandmarksGrid/";
static const string RANDOM_LANDMARK_FOLDER = DATA_FOLDER + "LandmarksRandom/";

static const int NUM_PAIRS = 25;
static const int NUM_GRID_SIZES = 5;

static const string REGIONS[] = {"NewYork", "Colorado", "NorthWest", "California", "East", "West"}; // "Central", "USA"

static const string LENGTH_FILE_EXTENSION = ".len";
static const string COORDINATES_FILE_EXTENSION = ".co";

static const string FROM_GRID_LANDMARK_FILE_EXTENSION = ".grid.from";
static const string TO_GRID_LANDMARK_FILE_EXTENSION = ".grid.to";
static const string FROM_RANDOM_LANDMARK_FILE_EXTENSION = ".random.from";
static const string TO_RANDOM_LANDMARK_FILE_EXTENSION = ".random.to";

static const long CLOCKS_PER_MILLISEC = CLOCKS_PER_SEC/1000;

static Graph loadGraph(int regionIndex) {
    cout << "Loading " << REGIONS[regionIndex] << "...";
    Graph g = GraphReader::readWeightedGraph(DATA_FOLDER + REGIONS[regionIndex] + LENGTH_FILE_EXTENSION);
    g.coordinates = GraphReader::readCoordinates(DATA_FOLDER + REGIONS[regionIndex] + COORDINATES_FILE_EXTENSION);
    cout << "Done!\n\n";
    return g;
}

static void compare(int regionIndex, Graph &g) {
    
    int sources[NUM_PAIRS];
    int targets[NUM_PAIRS];
    printf("Testing with %d source-target pairs for ", NUM_PAIRS);
    cout << REGIONS[regionIndex];
    for (int i = 0; i < NUM_PAIRS; i++) {
        sources[i] = rand() % g.numVertices;
        targets[i] = rand() % g.numVertices;
    }

    Dijkstra_P2P p2p = Dijkstra_P2P(g);
    Dijkstra_Bidirectional bidir = Dijkstra_Bidirectional(g);
    AStar_Euclidean euclidean = AStar_Euclidean(g);
    AStar_Landmark gridLandmarks[NUM_GRID_SIZES];
    AStar_Landmark randomLandmarks[NUM_GRID_SIZES];
    
    for (int i = 0; i < NUM_GRID_SIZES; i++) {
        int n = i + 2;
        string fileFromGridLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_GRID_LANDMARK_FILE_EXTENSION + "." + to_string(n * n);
        string fileToGridLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_GRID_LANDMARK_FILE_EXTENSION + "." + to_string(n * n);
        string fileFromRandomLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_RANDOM_LANDMARK_FILE_EXTENSION + "." + to_string(n * n);
        string fileToRandomLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_RANDOM_LANDMARK_FILE_EXTENSION + "." + to_string(n * n);
        
        AStar_Landmark gl(g, fileFromGridLandmark, fileToGridLandmark);
        AStar_Landmark rl(g, fileFromRandomLandmark, fileToRandomLandmark);
        gridLandmarks[i] = gl;
        randomLandmarks[i] = rl;
    }

    double p2pTime = 0, p2pEdges = 0;
    double bidirectionalTime = 0, bidirectionalEdges = 0;
    double euclideanTime = 0, euclideanEdges = 0;
    double gridTime[NUM_GRID_SIZES];
    double gridEdges[NUM_GRID_SIZES];
    double randomTime[NUM_GRID_SIZES];
    double randomEdges[NUM_GRID_SIZES];
    for (int i = 0; i < NUM_GRID_SIZES; i++) {
        gridTime[i] = 0;
        gridEdges[i] = 0;
        randomTime[i] = 0;
        randomEdges[i] = 0;
    }
    clock_t start;

    for (int i = 0; i < NUM_PAIRS; i++) {
        int s = sources[i];
        int t = targets[i];

        start = clock();
        int p2p_Distance = p2p.execute(s, t);
        p2pTime += clock() - start;
        p2pEdges += p2p.numEdgesRelaxed;
        
        start = clock();
        int bidirectional_Distance = bidir.execute(s, t);
        bidirectionalTime += clock() - start;
        bidirectionalEdges += bidir.numEdgesRelaxed;

        start = clock();
        int euclidean_Distance = euclidean.execute(s, t);
        euclideanTime += clock() - start;
        euclideanEdges += euclidean.numEdgesRelaxed;

        if (p2p_Distance != euclidean_Distance)
            throw ("Euclidean A* code is wrong!");

        for (int j = 0; j < NUM_GRID_SIZES; j++) {
            start = clock();
            int gridDistance = gridLandmarks[j].execute(s, t);
            gridTime[j] += clock() - start;
            gridEdges[j] += gridLandmarks[j].numEdgesRelaxed;
            if (p2p_Distance != gridDistance)
                throw ("Grid Landmark A* code is wrong!");
            
            start = clock();
            int randomDistance = randomLandmarks[j].execute(s, t);
            randomTime[j] += clock() - start;
            randomEdges[j] += randomLandmarks[j].numEdgesRelaxed;
            if (p2p_Distance != randomDistance)
                throw ("Random Landmark A* code is wrong!");
        }
    }

    p2pTime /= CLOCKS_PER_MILLISEC;
    bidirectionalTime /= CLOCKS_PER_MILLISEC;
    euclideanTime /= CLOCKS_PER_MILLISEC;

    cout << "\n\nP2P: Avg. Time = " << p2pTime / NUM_PAIRS
    << ", Avg. no. of edges relaxed = " << p2pEdges / NUM_PAIRS << endl;
    cout << "Bi-directional: Avg. Time = " << bidirectionalTime / NUM_PAIRS
    << ", Avg. no. of edges relaxed = " << bidirectionalEdges / NUM_PAIRS << endl;
    cout << "Euclidean: Avg. Time = " << euclideanTime / NUM_PAIRS
    << ", Avg. no. of edges relaxed = " << euclideanEdges / NUM_PAIRS << endl;
    
    for (int j = 0; j < NUM_GRID_SIZES; j++) {
        int n = j + 2;
        gridTime[j] /= CLOCKS_PER_MILLISEC;
        randomTime[j] /= CLOCKS_PER_MILLISEC;
        cout << "\nGrid Landmark(" << n * n << "): Avg. Time = " << gridTime[j] / NUM_PAIRS
        <<", Avg. no. of edges relaxed = " << gridEdges[j] / NUM_PAIRS << endl;
        cout << "Random Landmark(" << n * n << "): Avg. Time = " << randomTime[j] / NUM_PAIRS
        <<", Avg. no. of edges relaxed = " << randomEdges[j] / NUM_PAIRS << endl;
    }
}

static void preComputeGrid(int regionIndex, int gridDim, Graph &g) {
    printf("Creating %d grid landmarks for ", gridDim * gridDim);
    cout << REGIONS[regionIndex] << "...";
    string fileFromLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_GRID_LANDMARK_FILE_EXTENSION + "." + to_string(gridDim * gridDim);
    string fileToLandmark = GRID_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_GRID_LANDMARK_FILE_EXTENSION + "." + to_string(gridDim * gridDim);
    LandmarkGenerator::makeGridLandmarks(g, gridDim, fileFromLandmark, fileToLandmark);
    cout << "Done!" << endl;
}

static void preComputeRandom(int regionIndex, int numLandmarks, Graph &g) {
    printf("Creating %d random landmarks for ", numLandmarks);
    cout << REGIONS[regionIndex] << "...";
    string fileFromLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + FROM_RANDOM_LANDMARK_FILE_EXTENSION + "." + to_string(numLandmarks);
    string fileToLandmark = RANDOM_LANDMARK_FOLDER + REGIONS[regionIndex] + TO_RANDOM_LANDMARK_FILE_EXTENSION + "." + to_string(numLandmarks);
    LandmarkGenerator::makeRandomLandmarks(g, numLandmarks, fileFromLandmark, fileToLandmark);
    cout << "Done!" << endl;
}

static void generateRandomLandmarks(int regionIndex, Graph &g) {
    preComputeRandom(regionIndex, 4, g);
    preComputeRandom(regionIndex, 9, g);
    preComputeRandom(regionIndex, 16, g);
    preComputeRandom(regionIndex, 25, g);
    preComputeRandom(regionIndex, 36, g);
    cout << endl;
}

static void generateGridLandmarks(int regionIndex, Graph &g) {
    preComputeGrid(regionIndex, 2, g);
    preComputeGrid(regionIndex, 3, g);
    preComputeGrid(regionIndex, 4, g);
    preComputeGrid(regionIndex, 5, g);
    preComputeGrid(regionIndex, 6, g);
    cout << endl;
}

int main(int argc, const char * argv[]) {
    srand(clock());
    // 0: "NewYork"
    // 1: "Colorado"
    // 2: "NorthWest"
    // 3: "California"
    // 4: "East"
    // 5: "West"
    int regionIndex = 5;
    Graph g = loadGraph(regionIndex);
    
    /**
     * The generate calls should be executed once per region to ensure the landmarks are created.
     * Then, comment out the calls.
     */
//    generateRandomLandmarks(regionIndex, g);
//    generateGridLandmarks(regionIndex, g);
    
    compare(regionIndex, g);
    return 0;
}
