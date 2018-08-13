#ifndef _BIG_CORE_H_
#define _BIG_CORE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>

#ifndef DEBUG
#define DEBUG 1
#endif


class BigCore
{
public:
	// allow only empty constructor
	BigCore();

#ifdef DEBUG 
	BigCore(uint64_t numberOfImages, uint64_t numberOfTiles, uint64_t imageHeight, uint64_t imageWidth,
		    uint64_t numberOfPlanes, uint64_t dataOrder[5], uint64_t dataType, size_t dataLength, char* data);
#ifdef DEBUG

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
	void writeChunk(std::ofstream &file, uint64_t id, uint64_t length, const char* data);

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
	size_t _dataLength;

	// std::vector<void *> _entity;

};

#endif // BIG_CORE_H
