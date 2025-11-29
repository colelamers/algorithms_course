#include <string>
using namespace std;

#ifndef FILEPATHS_H_
#define FILEPATHS_H_

class FilePaths {
    
public:
    
    static const string DATA_DIRECTORY;
    static const string OUTPUT_DIRECTORY;
    static const string HUFFMAN_IO_TEST;
    
    static const string BWT_COMPRESSED_DIRECTORY;
    static const string LZ78_COMPRESSED_DIRECTORY;
    static const string LZ77_COMPRESSED_DIRECTORY;
    static const string LZSS_COMPRESSED_DIRECTORY;
    
    static const string DATA[];
    static const int NUM_DATA;
    
    static const string ALPHABET_EXTENSION;
    
    static const string HUFFMAN_ENCODING_EXTENSION;
    static const string HUFFMAN_MAP_EXTENSION;
    
    static const string LZ78_NODE_ENCODING_EXTENSION;
    static const string LZ78_CHARS_EXTENSION;
    
    static const string LZ77_DELTA_EXTENSION;
    static const string LZ77_LENGTH_EXTENSION;
    static const string LZ77_NEXT_EXTENSION;
    
    static const string LZSS_IDENTIFIER_EXTENSION;
    static const string LZSS_DELTA_EXTENSION;
    static const string LZSS_LENGTH_EXTENSION;
    static const string LZSS_NEXT_EXTENSION;
};

#endif /* FILEPATHS_H_ */
