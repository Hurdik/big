#ifndef _BIG_CONSTS_H_
#define _BIG_CONSTS_H_

// big magic number
const char MAGIC[] = { 0x42, 0x49, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00 };

// length of chunk
const unsigned CHUNK_LENGTH = 8;

// chunk ids
const unsigned NUMBER_OF_IMAGES = 1;
const unsigned NUMBER_OF_TILES = 2;
const unsigned IMAGE_WIDTH = 3;
const unsigned IMAGE_HEIGHT = 4;
const unsigned NUMBER_OF_IMAGE_PLANES = 5;
const unsigned DATA_ORDER = 6;
const unsigned DATA_TYPE = 7;
const unsigned DATA = 8;
const unsigned COLOR_SPACE = 9;
const unsigned ILLUMINANT = 10;
const unsigned PPMM = 11;
const unsigned NAME = 12;
const unsigned TEXT = 13;
const unsigned XML = 14;
const unsigned COORDINATES_OF_TILES = 15;
const unsigned LIST_OF_DIRECTIONS = 16;

// data type ids
const unsigned HALF = 1;
const unsigned FLOAT = 2;
const unsigned DOUBLE = 3;
const unsigned CHAR = 4;
const unsigned UNSIGNED_CHAR = 5;
const unsigned SHORT = 6;
const unsigned UNSIGNED_SHORT = 7;
const unsigned INT = 8;
const unsigned UNSIGNED_INT = 9;
const unsigned LONG_LONG = 10;
const unsigned UNSIGNED_LONG_LONG = 11;
const unsigned BOOL = 12;

#endif // _BIG_CONSTS_H_

