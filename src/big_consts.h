#ifndef _BIG_CONSTS_H_
#define _BIG_CONSTS_H_

#include <cstdint>

// big magic number
const char MAGIC[] = { 0x42, 0x49, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00 };

// length of chunk
const uint64_t CHUNK_LENGTH = 8;

// chunk ids
uint64_t NUMBER_OF_IMAGES = 1;
uint64_t NUMBER_OF_TILES = 2;
uint64_t IMAGE_WIDTH = 3;
uint64_t IMAGE_HEIGHT = 4;
uint64_t NUMBER_OF_IMAGE_PLANES = 5;
uint64_t DATA_ORDER = 6;
uint64_t DATA_TYPE = 7;
uint64_t DATA = 8;
uint64_t COLOR_SPACE = 9;
uint64_t ILLUMINANT = 10;
uint64_t PPMM = 11;
uint64_t NAME = 12;
uint64_t TEXT = 13;
uint64_t XML = 14;
uint64_t COORDINATES_OF_TILES = 15;
uint64_t LIST_OF_DIRECTIONS = 16;

// data type ids
uint64_t HALF = 1;
uint64_t FLOAT = 2;
uint64_t DOUBLE = 3;
uint64_t CHAR = 4;
uint64_t UNSIGNED_CHAR = 5;
uint64_t SHORT = 6;
uint64_t UNSIGNED_SHORT = 7;
uint64_t INT = 8;
uint64_t UNSIGNED_INT = 9;
uint64_t LONG_LONG = 10;
uint64_t UNSIGNED_LONG_LONG = 11;
uint64_t BOOL = 12;

#endif // _BIG_CONSTS_H_

