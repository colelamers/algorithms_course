#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
using namespace std;

#ifndef IOHELPER_H_
#define IOHELPER_H_

class IOHelper {
    
public:
    
    /**
     Reads the data. Appends EOF '\0' at the end.
     */
    static vector<char> readFile(const string &filePath) {
        vector<char> content;
        ifstream fileReader(filePath);
        if (fileReader.is_open()) {
            char c;
            while (fileReader >> noskipws >> c) {
                content.push_back(c);
            }
            fileReader.close();
        }
        content.push_back('\0');
        return content;
    }
    
    /**
     * Writes a byte array to the file.
     * In C++, a byte is represented by a char.
     */
    static void writeBytes(vector<char> &bytes, string &filePath) {
        ofstream fileWriter(filePath, ios::binary);
        for (int i = 0; i < bytes.size(); i++) {
            fileWriter << bytes[i];
        }
        fileWriter.close();
    }
    
    /**
     * Reads bytes from the file into a vector.
     * In C++, a byte is represented by a char.
     */
    static vector<char> readBytes(string &filePath) {
        ifstream fileReader;
        
        fileReader.open(filePath, ios::binary);
        
        vector<char> bytes;
        if (fileReader.is_open()) {
            char c;
            while (fileReader >> noskipws >> c) {
                bytes.push_back(c);
            }
            fileReader.close();
        }
        return bytes;
    }
    
    /**
     * Writes an Integer-String map to a file.
     */
    static void writeMap(unordered_map<int, string> &map, string &filePath) {
        ofstream fileWriter(filePath, std::ios::out);
        unordered_map<int, string>::iterator it = map.begin();
        if (it != map.end()) {
            fileWriter << (it->first) << ":" << it->second;
            it++;
        }
        for (; it != map.end(); ++it) {
            fileWriter << endl << (it->first) << ":" << it->second;
        }
        fileWriter.close();
    }
    
    /**
     * Reads an Integer-String map from a file.
     */
    static unordered_map<int, string> readMap(string &filePath) {
        ifstream fileReader(filePath);
        unordered_map<int, string> map;
        if (fileReader.is_open()) {
            string line;
            while (std::getline(fileReader, line)) {
                int delimeterIndex = line.find(":");
                int key = stoi(line.substr(0, delimeterIndex));
                string value = line.substr(1 + delimeterIndex, line.size());
                map[key] = value;
            }
        }
        fileReader.close();
        return map;
    }
    
    static void writeAlphabet(vector<char> &alphabet, string &filePath) {
        string sb = "";
        for (char c : alphabet) {
            sb += to_string((int) c);
            sb += "\n";
        }
        sb.erase(sb.size() - 1);
        ofstream fileWriter(filePath, std::ios::out);;
        fileWriter << sb;
        fileWriter.close();
    }
    
    static vector<char> readAlphabet(string &filePath) {
        vector<char> alphabet;
        ifstream fileReader(filePath);
        int ascii;
        while (fileReader >> ascii)
            alphabet.push_back((char)ascii);
        fileReader.close();
        return alphabet;
    }
    
    static long filesize(string filePath) {
        return std::filesystem::file_size(filePath);
    }
};

#endif /* IOHELPER_H_ */
