#include "FilePaths.h"

const string FilePaths::DATA_DIRECTORY = "Data/";
const string FilePaths::OUTPUT_DIRECTORY = DATA_DIRECTORY + "OutputC++/";
const string FilePaths::HUFFMAN_IO_TEST = FilePaths::DATA_DIRECTORY + "testHuffmanIO";

const string FilePaths::BWT_COMPRESSED_DIRECTORY = OUTPUT_DIRECTORY + "BWT/";
const string FilePaths::LZ78_COMPRESSED_DIRECTORY = OUTPUT_DIRECTORY + "LZ78/";
const string FilePaths::LZ77_COMPRESSED_DIRECTORY = OUTPUT_DIRECTORY + "LZ77/";
const string FilePaths::LZSS_COMPRESSED_DIRECTORY = OUTPUT_DIRECTORY + "LZSS/";

const string FilePaths::DATA[] = {
    "tiny.txt",
    "medium.txt",
    "aliceinwonderland.txt",
    "H.pylori.fna",
    "L.monocytogenes.fna",
    "bible.txt",
    "E.Coli.fna",
    "S.cerevisiae.fna",
    "N.crassa.fna",
    "C.elegans.fna" };

const int FilePaths::NUM_DATA = 10;

/**
 * Large DNA file. You do not have to run this.
 */
//const string FilePaths::DATA[] = { "T.nigroviridis.fna" };
//const int FilePaths::NUM_DATA = 1;


const string FilePaths::ALPHABET_EXTENSION = ".alpha";

const string FilePaths::HUFFMAN_ENCODING_EXTENSION = ".huffman.encoding";
const string FilePaths::HUFFMAN_MAP_EXTENSION = ".huffman.map";

const string FilePaths::LZ78_NODE_ENCODING_EXTENSION = ".nodes";
const string FilePaths::LZ78_CHARS_EXTENSION = ".chars";

const string FilePaths::LZ77_DELTA_EXTENSION = ".delta";
const string FilePaths::LZ77_LENGTH_EXTENSION = ".length";
const string FilePaths::LZ77_NEXT_EXTENSION = ".next";

const string FilePaths::LZSS_IDENTIFIER_EXTENSION = ".identifier";
const string FilePaths::LZSS_DELTA_EXTENSION = ".delta";
const string FilePaths::LZSS_LENGTH_EXTENSION = ".length";
const string FilePaths::LZSS_NEXT_EXTENSION = ".next";
