#include <iostream>
#include "Huffman.h"
#include "HelperFunctions.h"
#include "IOHelper.h"
#include "HuffmanIOHelper.h"
#include "SuffixArray.h"
#include "BWT.h"
#include "MTF.h"
#include "LZ78.h"
#include "LZ77.h"
#include "LZSS.h"
#include "Master.h"
using namespace std;

template<typename F>
void printVector(vector<F> &vect) {
	if (vect.size() == 0)
		cout << "[]" << endl;
	else {
		cout << "[" << vect[0];
		for (int i = 1; i < vect.size(); i++)
			cout << ", " << vect[i];
		cout << "]" << endl;
	}
}

template<typename S, typename T>
void printMap(unordered_map<S, T> &map) {
	typename unordered_map<S, T>::iterator it = map.begin();
	if (it == map.end()) {
		cout << "{}" << endl;
		return;
	}
	cout << "Mapping:  {" << it->first << ":" << it->second << "}";
	it++;
	while (it != map.end()) {
		cout << ", ";
		cout << "{" << it->first << ":" << it->second << "}";
		it++;
	}
	cout << endl;
}

void testHuffman(string str) {
	cout << "Original string: " << str << endl;
	vector<char> stringAsVector = HelperFunctions::stringToVector(str);
    vector<int> charAsInts = HelperFunctions::charsToInts(stringAsVector);
	HuffmanElement huff = Huffman::encode(charAsInts);

	unordered_map<int, string> map = huff.mappingTable;
	printMap(map);
	string &encoding = huff.encoding;
	cout << "Encoding: " << encoding << endl;

	vector<int> originalMessage = Huffman::decode(huff);
	cout << "Decoded string:  "
			<< HelperFunctions::vectorToString(originalMessage) << endl
			<< endl;
}

void testManberMyers(string str) {
	vector<char> stringAsVector = HelperFunctions::stringToVector(str);
	cout << "Suffix Array for " << str + ": ";
	vector<int> sa = SuffixArray::manberMyers(stringAsVector);
	printVector(sa);
}

void testBruteForceSA(string str) {
    vector<char> stringAsVector = HelperFunctions::stringToVector(str);
    cout << "Suffix Array for " << str + ": ";
    vector<int> sa = SuffixArray::bruteforce(stringAsVector);
    printVector(sa);
}

void testBWT(string str) {
    cout << "String:  " << str << endl;
    vector<char> strAsVector = HelperFunctions::stringToVector(str);
    strAsVector.push_back('\0');
    vector<char> bwt = BWT::encode(strAsVector);
    cout << "BWT:     ";
    printVector(bwt);
    vector<char> decode = BWT::decode(bwt);
    cout << "Decoded: " << HelperFunctions::vectorToString(decode);
    cout << endl << endl;
}

void testMTF(string str) {
    cout << "Original: " << str << endl;
    vector<char> strAsVector = HelperFunctions::stringToVector(str);
    MTFElement mtf = MTF::encode(strAsVector);
    cout << "MTF: ";
    printVector(mtf.mtf);
    vector<char> decodedStr = MTF::decode(mtf);
    cout << "Decoded:  " << HelperFunctions::vectorToString(decodedStr)
    << endl;
}

void testBitPacker(string str) {
	cout << "Binary String: " << str << endl;
	vector<char> chars = BitPacker::pack(str);
    vector<int> charsAsInts = HelperFunctions::charsToInts(chars);
	cout << "Packed Bytes:  ";
	printVector(charsAsInts);
	string bytesToBits = BitPacker::unpack(chars);
	cout << "Unpacked Bits: " << bytesToBits << endl << endl;
}

static void testHuffmanIO(string str) {
	cout << "String:         " << str << endl;
	vector<char> strAsVector = HelperFunctions::stringToVector(str);
    vector<int> charAsInts = HelperFunctions::charsToInts(strAsVector);
	HuffmanElement huffObj = Huffman::encode(charAsInts);
	HuffmanIOHelper::writeHuffman(huffObj, FilePaths::HUFFMAN_IO_TEST);
	HuffmanElement huffObjFromFile = HuffmanIOHelper::readHuffman(FilePaths::HUFFMAN_IO_TEST);
	vector<int> decodedHuffmanVector = Huffman::decode(
			huffObjFromFile);
	string decodedStr = HelperFunctions::vectorToString(decodedHuffmanVector);
	cout << "Decoded String: " << decodedStr << endl << endl;
}

static void testLZ78(string str) {
	cout << "Original String:  " << str << endl;
	vector<char> strAsVector = HelperFunctions::stringToVector(str);
    strAsVector.push_back('\0');
	LZ78Element pair = LZ78::encode(strAsVector);
	cout << "Encoded Node Ids: " << pair.nodeIDBits << endl;
	cout << "Next character:   ";
	printVector(pair.chars);
	vector<char> output = LZ78::decode(pair);
	string decodedStr = HelperFunctions::vectorToString(output);
	cout << "Decoded String:   " << decodedStr << endl;
}

static void testLZ77(string str) {
    cout << "Original String:  " << str << endl;
    vector<char> strAsVector = HelperFunctions::stringToVector(str);
    strAsVector.push_back('\0');
    LZ77Element lz77 = LZ77::encode(strAsVector);
    cout << "Encoding: " << lz77.toString() << endl;
    vector<char> output = LZ77::decode(lz77);
    string decodedStr = HelperFunctions::vectorToString(output);
    cout << "Decoded String:   " << decodedStr << endl;
}

static void testLZSS(string str) {
    cout << "Original String:  " << str << endl;
    vector<char> strAsVector = HelperFunctions::stringToVector(str);
    strAsVector.push_back('\0');
    LZSSElement lzss = LZSS::encode(strAsVector);
    cout << "Encoding: " << lzss.toString() << endl;
    vector<char> output = LZSS::decode(lzss);
    string decodedStr = HelperFunctions::vectorToString(output);
    cout << "Decoded String:   " << decodedStr << endl;
}

void testCorrectness() {
    
    cout << "*** Huffman Test ***" << endl;
    testHuffman("Y2XEYX2XYX2CEXEX2Y2ZYX2ZYZE2Y2ZEYXEX2YZYCY2ZEX");
    
    cout << "*** Test Huffman IO ***" << endl;
    testHuffmanIO("Y2XEYX2XYX2CEXEX2Y2ZYX2ZYZE2Y2ZEYXEX2YZYCY2ZEX");
    
    cout << "*** Manber Myers Test ***" << endl;
    testManberMyers("banana");
    testManberMyers("mississippi");
    testManberMyers("mississippilesslyormississippily");
    cout << endl;
    
    cout << "*** Brute-Force Suffix Array Test ***" << endl;
    testBruteForceSA("banana");
    testBruteForceSA("mississippi");
    testBruteForceSA("mississippilesslyormississippily");
    cout << endl;
    
//    cout << "*** Packing/Unpacking Test ***" << endl;
//    testBitPacker("0111001100001001111101110100");
//    testBitPacker("01110011000010011111001001");
//    testBitPacker("10110011011010011101011101001101");
//
//    cout << "*** Test LZ77 ***" << endl;
//    testLZ77("mississippimissississispsisp");
//    cout << endl;
//
//    cout << "*** Test LZSS ***" << endl;
//    testLZSS("mississippimissississispsisp");
//    cout << endl;
//
//    cout << "*** BWT Test ***" << endl;
//
//    testBWT("banana");
//    testBWT("mississippi");
//    testBWT("mississippilesslyormississippily");
//    testBWT("TAT");
//
//    cout << "*** MTF Test ***" << endl;
//
//    testMTF("spsssmmipissssiiii");
//    cout << endl;
//
//    cout << "*** Test LZ78 ***" << endl;
//    testLZ78("mississippimissississispsisp");
//    cout << endl;
}

static void loadTest() {
//    Master::lz77();
//    cout << "**********************" << endl;
//    Master::lzss();
//    cout << "**********************" << endl;
//    Master::bwt();
//    cout << "**********************" << endl;
//    Master::lz78();
//    cout << "**********************" << endl;
}

int main(int argc, const char * argv[]) {
    testCorrectness();
    loadTest();
    return 0;
}
