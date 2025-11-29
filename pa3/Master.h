#include <iostream>
#include <time.h>
#include "BitPacker.h"
#include "BWT.h"
#include "FilePaths.h"
#include "IOHelper.h"
#include "HelperFunctions.h"
#include "Huffman.h"
#include "HuffmanIOHelper.h"
#include "LZ78.h"
#include "LZ77.h"
#include "LZSS.h"
#include "MTF.h"
using namespace std;

#ifndef MASTER_H_
#define MASTER_H_

class Master {
    
public:
    
    static void lz77() {
        lz77_compress();
        lz77_expand();
    }
    
    static void lzss() {
        lzss_compress();
        lzss_expand();
    }
    
    static void bwt() {
        bwt_compress();
        bwt_expand();
    }
    
    static void lz78() {
        lz78_compress();
        lz78_expand();
    }
    
private:
    
    static void lz77_compress() {
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            clock_t startTime = clock();
            
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            string lz77DeltaPath = FilePaths::LZ77_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ77_DELTA_EXTENSION;
            string lz77LengthPath = FilePaths::LZ77_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ77_LENGTH_EXTENSION;
            string lz77NextPath = FilePaths::LZ77_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ77_NEXT_EXTENSION;
            
            
            cout << "\n**********************" << endl;
            cout << "\nReading file: " << path << endl;
            
            vector<char> data = IOHelper::readFile(path);
            
            cout << "File loaded." << endl;
            
            cout << "Data -> LZ77 Phase..." << endl;
            LZ77Element lz77 = LZ77::encode(data);
            
            cout << "LZ77 -> Huffman Phase..." << endl;
            HuffmanElement huff_Delta = Huffman::encode(lz77.delta);
            HuffmanElement huff_Length = Huffman::encode(lz77.length);
            vector<int> nextAsInt = HelperFunctions::charsToInts(lz77.next);
            HuffmanElement huff_Next = Huffman::encode(nextAsInt);
            
            cout << "Writing compressed files..." << endl;
            HuffmanIOHelper::writeHuffman(huff_Delta, lz77DeltaPath);
            HuffmanIOHelper::writeHuffman(huff_Length, lz77LengthPath);
            HuffmanIOHelper::writeHuffman(huff_Next, lz77NextPath);
            
            printf("\nCompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            long filesize = IOHelper::filesize(path);
            cout << "\nOriginal File Size = " << filesize << " bytes" << endl;
            long compressedSize = IOHelper::filesize(lz77DeltaPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lz77DeltaPath + FilePaths::HUFFMAN_ENCODING_EXTENSION) +
            IOHelper::filesize(lz77LengthPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lz77LengthPath + FilePaths::HUFFMAN_ENCODING_EXTENSION) +
            IOHelper::filesize(lz77NextPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lz77NextPath + FilePaths::HUFFMAN_ENCODING_EXTENSION);
            cout << "Compressed File Size = " << compressedSize << " bytes" << endl;
            printf("Compression Ratio = %.2f\n", 1.00 * data.size() / compressedSize);
        }
    }
    
    static void lz77_expand() {
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            cout << "\n**********************" << endl;
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            cout << "\nReading file for verification: " << path << endl;
            vector<char> data = IOHelper::readFile(path);
            cout << "File loaded." << endl;
            
            string lz77DeltaPath = FilePaths::LZ77_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ77_DELTA_EXTENSION;
            string lz77LengthPath = FilePaths::LZ77_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ77_LENGTH_EXTENSION;
            string lz77NextPath = FilePaths::LZ77_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ77_NEXT_EXTENSION;
            
            clock_t startTime = clock();
            
            cout << "Reading compressed files..." << endl;
            HuffmanElement huffFromFile_Delta = HuffmanIOHelper::readHuffman(lz77DeltaPath);
            HuffmanElement huffFromFile_Length = HuffmanIOHelper::readHuffman(lz77LengthPath);
            HuffmanElement huffFromFile_Next = HuffmanIOHelper::readHuffman(lz77NextPath);
            
            cout << "Huffman -> LZ77 Phase..." << endl;
            vector<int> decoded_Delta = Huffman::decode(huffFromFile_Delta);
            vector<int> decoded_Length = Huffman::decode(huffFromFile_Length);
            vector<int> decoded_Next_Ints = Huffman::decode(huffFromFile_Next);
            vector<char> decoded_Next = HelperFunctions::intsToChars(decoded_Next_Ints);
            
            cout << "LZ77 -> Decoded Data Phase..." << endl;
            LZ77Element decodedTriplet = LZ77Element(decoded_Delta, decoded_Length, decoded_Next);
            vector<char> decodedData = LZ77::decode(decodedTriplet);
            
            printf("\nDecompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            
            HelperFunctions::verifyEquality(data, decodedData);
        }
    }
    
    static void lzss_compress() {
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            clock_t startTime = clock();
            
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            string lzssIdentifierPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_IDENTIFIER_EXTENSION;
            string lzssDeltaPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_DELTA_EXTENSION;
            string lzssLengthPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_LENGTH_EXTENSION;
            string lzssNextPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_NEXT_EXTENSION;
            
            
            cout << "\n**********************" << endl;
            cout << "\nReading file: " << path << endl;
            
            vector<char> data = IOHelper::readFile(path);
            
            cout << "File loaded." << endl;
            
            cout << "Data -> LZSS Phase..." << endl;
            LZSSElement lzss = LZSS::encode(data);
            
            cout << "LZSS -> Huffman Phase..." << endl;
            HuffmanElement huff_Delta = Huffman::encode(lzss.delta);
            HuffmanElement huff_Length = Huffman::encode(lzss.length);
            vector<int> nextAsInts = HelperFunctions::charsToInts(lzss.next);
            HuffmanElement huff_Next = Huffman::encode(nextAsInts);
            
            cout << "Writing compressed files..." << endl;
            vector<char> compressedIdentifiers = BitPacker::pack(lzss.identifier);
            IOHelper::writeBytes(compressedIdentifiers, lzssIdentifierPath);
            HuffmanIOHelper::writeHuffman(huff_Delta, lzssDeltaPath);
            HuffmanIOHelper::writeHuffman(huff_Length, lzssLengthPath);
            HuffmanIOHelper::writeHuffman(huff_Next, lzssNextPath);
            
            printf("\nCompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            long filesize = IOHelper::filesize(path);
            cout << "\nOriginal File Size = " << filesize << " bytes" << endl;
            long compressedSize = IOHelper::filesize(lzssIdentifierPath) +
            IOHelper::filesize(lzssDeltaPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lzssDeltaPath + FilePaths::HUFFMAN_ENCODING_EXTENSION) +
            IOHelper::filesize(lzssLengthPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lzssLengthPath + FilePaths::HUFFMAN_ENCODING_EXTENSION) +
            IOHelper::filesize(lzssNextPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lzssNextPath + FilePaths::HUFFMAN_ENCODING_EXTENSION);
            cout << "Compressed File Size = " << compressedSize << " bytes" << endl;
            printf("Compression Ratio = %.2f\n", 1.00 * data.size() / compressedSize);
        }
    }
    
    static void lzss_expand() {
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            cout << "\n**********************" << endl;
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            cout << "\nReading file for verification: " << path << endl;
            vector<char> data = IOHelper::readFile(path);
            cout << "File loaded." << endl;
            
            string lzssIdentifierPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_IDENTIFIER_EXTENSION;
            string lzssDeltaPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_DELTA_EXTENSION;
            string lzssLengthPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_LENGTH_EXTENSION;
            string lzssNextPath = FilePaths::LZSS_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZSS_NEXT_EXTENSION;
            
            clock_t startTime = clock();
            
            cout << "Reading compressed files..." << endl;
            vector<char> compressedIdentifiersFromFile = IOHelper::readBytes(lzssIdentifierPath);
            string identifiersFromFile = BitPacker::unpack(compressedIdentifiersFromFile);
            HuffmanElement huffFromFile_Delta = HuffmanIOHelper::readHuffman(lzssDeltaPath);
            HuffmanElement huffFromFile_Length = HuffmanIOHelper::readHuffman(lzssLengthPath);
            HuffmanElement huffFromFile_Next = HuffmanIOHelper::readHuffman(lzssNextPath);
            
            cout << "Huffman -> LZSS Phase..." << endl;
            vector<int> decoded_Delta = Huffman::decode(huffFromFile_Delta);
            vector<int> decoded_Length = Huffman::decode(huffFromFile_Length);
            vector<int> decoded_nextAsInts = Huffman::decode(huffFromFile_Next);
            vector<char> decoded_Next = HelperFunctions::intsToChars(decoded_nextAsInts);
            
            cout << "LZSS -> Decoded Data Phase..." << endl;
            LZSSElement decodedTriplet = LZSSElement(identifiersFromFile, decoded_Delta, decoded_Length, decoded_Next);
            vector<char> decodedData = LZSS::decode(decodedTriplet);
            
            printf("\nDecompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            
            HelperFunctions::verifyEquality(data, decodedData);
        }
    }
    
    static void bwt_compress() {
        
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            clock_t startTime = clock();
            
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            string huffmanPath = FilePaths::BWT_COMPRESSED_DIRECTORY + FilePaths::DATA[i];
            string alphaPath = FilePaths::BWT_COMPRESSED_DIRECTORY + FilePaths::DATA[i] + FilePaths::ALPHABET_EXTENSION;
            
            cout << "\n**********************" << endl;
            cout << "\nReading file: " << path << endl;
            
            vector<char> data = IOHelper::readFile(path);
            cout << "File loaded." << endl;
            
            cout << "Data -> BWT Phase..." << endl;
            vector<char> bwt = BWT::encode(data);
            
            cout << "BWT -> MTF Phase..." << endl;
            MTFElement mtf = MTF::encode(bwt);
            
            cout << "MTF -> Huffman Phase..." << endl;
            HuffmanElement huff = Huffman::encode(mtf.mtf);
            
            cout << "Writing compressed files..." << endl;
            HuffmanIOHelper::writeHuffman(huff, huffmanPath);
            IOHelper::writeAlphabet(mtf.alphabet, alphaPath);
            
            printf("\nCompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            long filesize = IOHelper::filesize(path);
            cout << "\nOriginal File Size = " << filesize << " bytes" << endl;
            long compressedSize = IOHelper::filesize(huffmanPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(huffmanPath + FilePaths::HUFFMAN_ENCODING_EXTENSION) +
            IOHelper::filesize(huffmanPath + FilePaths::ALPHABET_EXTENSION);
            cout << "Compressed File Size = " << compressedSize << " bytes" << endl;
            printf("Compression Ratio = %.2f\n", 1.00 * data.size() / compressedSize);
        }
    }
    
    static void bwt_expand() {
        
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            cout << "\n**********************" << endl;
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            cout << "\nReading file for verification: " << path << endl;
            vector<char> data = IOHelper::readFile(path);
            cout << "File loaded." << endl;
            
            string huffmanPath = FilePaths::BWT_COMPRESSED_DIRECTORY + FilePaths::DATA[i];
            string alphaPath = FilePaths::BWT_COMPRESSED_DIRECTORY + FilePaths::DATA[i] + FilePaths::ALPHABET_EXTENSION;
            
            clock_t startTime = clock();
            
            cout << "Reading compressed files..." << endl;
            HuffmanElement huffFromFile = HuffmanIOHelper::readHuffman(huffmanPath);
            
            cout << "Huffman -> MTF Phase..." << endl;
            vector<int> decodedMTF = Huffman::decode(huffFromFile);
            
            cout << "MTF -> BWT Phase..." << endl;
            vector<char> alphabet = IOHelper::readAlphabet(alphaPath);
            MTFElement mtf_ele(alphabet, decodedMTF);
            vector<char> decodedBWT = MTF::decode(mtf_ele);
            
            cout << "BWT -> Decoded Data Phase..." << endl;
            vector<char> decodedData = BWT::decode(decodedBWT);
            
            printf("\nDecompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            
            HelperFunctions::verifyEquality(data, decodedData);
        }
    }
    
    static void lz78_compress() {
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            clock_t startTime = clock();
            
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            string lz78NodesPath = FilePaths::LZ78_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ78_NODE_ENCODING_EXTENSION;
            string lz78CharsPath = FilePaths::LZ78_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ78_CHARS_EXTENSION;
            
            
            cout << "\n**********************" << endl;
            cout << "\nReading file: " << path << endl;
            
            vector<char> data = IOHelper::readFile(path);
            
            cout << "File loaded." << endl;
            
            cout << "Data -> LZ78 Phase..." << endl;
            LZ78Element pair = LZ78::encode(data);
            
            cout << "LZ78 -> Huffman Phase..." << endl;
            vector<int> lz78CharsAsInts = HelperFunctions::charsToInts(pair.chars);
            HuffmanElement huff_Chars = Huffman::encode(lz78CharsAsInts);
            
            cout << "Writing compressed files..." << endl;
            HuffmanIOHelper::writeHuffman(huff_Chars, lz78CharsPath);
            vector<char> packedNodes = BitPacker::pack(pair.nodeIDBits);
            IOHelper::writeBytes(packedNodes, lz78NodesPath);
            
            printf("\nCompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            long filesize = IOHelper::filesize(path);
            cout << "\nOriginal File Size = " << filesize << " bytes" << endl;
            long compressedSize = IOHelper::filesize(lz78NodesPath) +
            IOHelper::filesize(lz78CharsPath + FilePaths::HUFFMAN_MAP_EXTENSION) +
            IOHelper::filesize(lz78CharsPath + FilePaths::HUFFMAN_ENCODING_EXTENSION);
            cout << "Compressed File Size = " << compressedSize << " bytes" << endl;
            printf("Compression Ratio = %.2f\n", 1.00 * data.size() / compressedSize);
        }
    }
    
    static void lz78_expand() {
        for (int i = 0; i < FilePaths::NUM_DATA; i++) {
            
            cout << "\n**********************" << endl;
            string path = FilePaths::DATA_DIRECTORY + FilePaths::DATA[i];
            cout << "\nReading file for verification: " << path << endl;
            vector<char> data = IOHelper::readFile(path);
            cout << "File loaded." << endl;
            
            string lz78NodesPath = FilePaths::LZ78_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ78_NODE_ENCODING_EXTENSION;
            string lz78CharsPath = FilePaths::LZ78_COMPRESSED_DIRECTORY + FilePaths::DATA[i]
            + FilePaths::LZ78_CHARS_EXTENSION;
            
            clock_t startTime = clock();
            
            cout << "Reading compressed files..." << endl;
            HuffmanElement huffFromFile_Chars = HuffmanIOHelper::readHuffman(lz78CharsPath);
            vector<char> compressedNodesFromFile = IOHelper::readBytes(lz78NodesPath);
            string nodeIDsFromFile = BitPacker::unpack(compressedNodesFromFile);
            
            cout << "Huffman -> LZ78 Phase..." << endl;
            vector<int> decoded_Chars = Huffman::decode(huffFromFile_Chars);
            
            cout << "LZ78 -> Decoded Data Phase..." << endl;
            vector<char> intsAsChars = HelperFunctions::intsToChars(decoded_Chars);
            LZ78Element decodedPair = LZ78Element(nodeIDsFromFile, intsAsChars);
            vector<char> decodedData = LZ78::decode(decodedPair);
            
            printf("\nDecompression took %.2f seconds\n", 1.00 * (clock() - startTime) / CLOCKS_PER_SEC);
            
            HelperFunctions::verifyEquality(data, decodedData);
        }
    }
};

#endif /* MASTER_H_ */
