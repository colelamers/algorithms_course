#include "BitPacker.h"
#include "FilePaths.h"
#include "IOHelper.h"
#include "HelperFunctions.h"
#include "Huffman.h"

#ifndef HUFFMANIOHELPER_H_
#define HUFFMANIOHELPER_H_

class HuffmanIOHelper {

public:

	/**
	 * Writes the Huffman object into a file.
	 *
	 * The encoding part is written as a byte file. So, the bits need to packed.
	 *
	 * The map is written using the writeMap function.
	 */
    static void writeHuffman(HuffmanElement &obj, const string &filePath) {
        vector<char> bytes = BitPacker::pack(obj.encoding);
        string fileEncoding = filePath + FilePaths::HUFFMAN_ENCODING_EXTENSION;
        string fileMap = filePath + FilePaths::HUFFMAN_MAP_EXTENSION;
        IOHelper::writeBytes(bytes, fileEncoding);
        IOHelper::writeMap(obj.mappingTable, fileMap);
    }

	/**
	 * Reads the Huffman object from the file.
	 *
	 * The encoding part is read from the byte file; note that the byte file needs
	 * to unpacked.
	 *
	 * The map is read using the readMap function.
	 */
    static HuffmanElement readHuffman(const string &filePath) {
        string fileEncoding = filePath + FilePaths::HUFFMAN_ENCODING_EXTENSION;
        string fileMap = filePath + FilePaths::HUFFMAN_MAP_EXTENSION;
        vector<char> bytes = IOHelper::readBytes(fileEncoding);
        string decompressed = BitPacker::unpack(bytes);
        unordered_map<int, string> decodedHuffMap = IOHelper::readMap(fileMap);
        HuffmanElement decodedHuffObj(decompressed, decodedHuffMap);
        return decodedHuffObj;
    }
};

#endif /* HUFFMANIOHELPER_H_ */
