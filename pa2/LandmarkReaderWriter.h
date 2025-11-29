#include <vector>

using namespace std;

#ifndef LandmarkReaderWriter_h
#define LandmarkReaderWriter_h

class LandmarkReaderWriter {
    
public:
    
    static void writeDistances(vector<vector<int>> &arr, int numLandmarks, int numVertices, string filePath) {
        string out = "";
        out = out + to_string(numLandmarks) + " " + to_string(numVertices) + "\n";
        for (int l = 0; l < numLandmarks; l++) {
            for (int a = 0; a < numVertices; a++) {
                out += to_string(arr[l][a]);
                if (a != numVertices - 1)
                    out += " ";
            }
            if (l != numLandmarks - 1)
                out += "\n";
        }
        ofstream bw(filePath, ios::out);
        bw << out;
        bw.close();
    }
    
    static vector<vector<int>> readDistances(string fromLandmarkFilePath) {
        ifstream reader(fromLandmarkFilePath, ios::in);
        int numLandmarks, numVertices;
        reader >> numLandmarks;
        reader >> numVertices;
        vector<vector<int>> distances;
        distances.reserve(numLandmarks);
        int val;
        for (int i = 0; i < numLandmarks; i++) {
            distances.push_back(vector<int>());
            distances[i].reserve(numVertices);
            for (int j = 0; j < numVertices; j++) {
                reader >> val;
                distances[i].push_back(val);
            }
        }
        return distances;
    }
};

#endif /* LandmarkReaderWriter_h */
