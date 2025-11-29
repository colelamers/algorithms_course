#ifndef BitArray_h
#define BitArray_h

#include <iostream>
#include <format>
using namespace std;

class BitArray {
    
private:
    
    char *arr;
    int m;
    int _arrSize;
    
public:
    
    BitArray() {
        m = 0;
        _arrSize = 0;
    }
    
    BitArray(int _size) {
        m = _size;
        _arrSize = _size % 8 != 0 ? 1 + _size / 8 : _size / 8;
        arr = new char[_arrSize];
        for(int i = 0; i < _size; i++)
            clear(i);
    }
    
    bool access(int index) {
        if (index >= m || index < 0) {
            string err = "Index " + to_string(index) + " is out of bounds. It must be in [0," + to_string(m) + "]";
            throw (err);
        }
            
        return ((arr[index / 8] >> (7 - index % 8)) & 1) == 1;
    }
    
    void set(int index) {
        if (index >= m || index < 0) {
            string err = "Index " + to_string(index) + " is out of bounds. It must be in [0," + to_string(m) + "]";
            throw (err);
        }
        arr[index / 8] |= (1 << (7 - index % 8));
    }
    
    void clear(int index) {
        if (index >= m || index < 0) {
            string err = "Index " + to_string(index) + " is out of bounds. It must be in [0," + to_string(m) + "]";
            throw (err);
        }
        arr[index / 8] &= ~(1 << (7 - index % 8));
    }
    
    int size() {
        return m;
    }
};

#endif /* BitArray_h */
