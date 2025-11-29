#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include "MinHash.h"
using namespace std;

#ifndef PLAGIARISMDETECTOR_H_
#define PLAGIARISMDETECTOR_H_

class PlagiarismDetector {

private:

	static const int SHINGLES = 3;
	static const double PLAGIARISM_JACCARD_SIMILARITY_THRESHOLD = 0.7;

	/**
	 * C++ 14 and below do not provide to iterator over files in a directory.
	 * So, I am providing this method.
	 * Given the directory path, it will return the name of all files within that directory.
	 * You can filter the required files from the names.
	 */
	static vector<string> listAllFilesInDir(const string &folderPath) {
		struct dirent *entry;
		char *path = new char[folderPath.length()];
		for (int i = 0; i < folderPath.length(); i++) {
			path[i] = folderPath.at(i);
		}
		DIR *dir = opendir(path);

		vector<string> files;

		if (dir != NULL) {
			while ((entry = readdir(dir)) != NULL) {
				char c = entry->d_name[0];
				string file = "";
				int i = 0;
				while (c != '\0') {
					file += c;
					c = entry->d_name[++i];
				}
				files.push_back(file);
			}
			closedir(dir);
		}
		delete[] path;
		return files;
	}

public:

	static void run(vector<int> &primes, const string &folderPath) { // Task 3
	}
};

#endif /* PLAGIARISMDETECTOR_H_ */
