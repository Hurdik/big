#ifndef _BIG_CORE_H_
#define _BIG_CORE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>

#ifndef DEBUG
#define DEBUG 1
#endif

// big magic number
const char MAGIC[] = { 0x42, 0x49, 0x47, 0x00, 0x00, 0x00, 0x00, 0x00 };

// length of chunk
const uint64_t CHUNK_LENGTH = 8;

// chunk ids
enum class ChunkIds : uint64_t
{
	NUMBER_OF_IMAGES = 1,
	NUMBER_OF_TILES = 2,
	IMAGE_WIDTH = 3,
	IMAGE_HEIGHT = 4,
	NUMBER_OF_IMAGE_PLANES = 5,
	DATA_ORDER = 6,
	DATA_TYPE = 7,
	DATA = 8,
	COLOR_SPACE = 9,
	ILLUMINANT = 10,
	PPMM = 11,
	NAME = 12,
	TEXT = 13,
	XML = 14,
	COORDINATES_OF_TILES = 15,
	LIST_OF_DIRECTIONS = 16
};

// data type ids
enum class DataTypes : uint64_t
{
	HALF = 1,
	FLOAT = 2,
	DOUBLE = 3,
	CHAR = 4,
	UNSIGNED_CHAR = 5,
	SHORT = 6,
	UNSIGNED_SHORT = 7,
	INT = 8,
	UNSIGNED_INT = 9,
	LONG_LONG = 10,
	UNSIGNED_LONG_LONG = 11,
	BOOL = 12,
};

class BigCore
{
public:
	// allow only empty constructor
	BigCore();
#ifdef DEBUG
	BigCore(uint64_t numberOfImages, uint64_t numberOfTiles, uint64_t imageHeight, uint64_t imageWidth,
		    uint64_t numberOfPlanes, uint64_t dataOrder[5], uint64_t dataType, size_t dataLength, char* data);
#endif

	// file de/serialization
	void writeFile(std::string fname);
	void readFile(std::string fname);

	// static methods for file operations
	static bool checkHeader(char buffer[8]);
	static uint64_t alignToMultipleOf8(uint64_t length);
	static uint64_t getFileLength(std::ifstream &file);

	// destructor
	~BigCore();

	void print();

protected:
	void writeChunk(std::ofstream &file, ChunkIds id, uint64_t length, const char* data);

	void readChunk(std::ifstream &file, uint64_t &id, uint64_t &length);
	void readData(std::ifstream &file, const uint64_t id, const uint64_t length);

	uint64_t dataSize();
	

	uint64_t _numberOfImages;
	uint64_t _numberOfTiles;
	uint64_t _imageHeight;
	uint64_t _imageWidth;
	uint64_t _numberOfImagePlanes;
	uint64_t _dataOrder[5];
	// std::vector<uint8_t> _dataType;
	uint64_t _dataType;
	char *_data;
	uint64_t _dataLength;

	// std::vector<void *> _entity;

};

#endif // BIG_CORE_H
