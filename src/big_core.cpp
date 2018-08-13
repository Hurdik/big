#include <iterator>
#include <iostream>
#include <fstream>

#include "big_core.h"
#include "big_consts.h"

BigCore::BigCore()
	:
_numberOfImages(0),
_numberOfTiles(0),
_imageHeight(0),
_imageWidth(0),
_numberOfImagePlanes(0),
_dataType(0),
_data(0),
_dataLength(0)
{
}

#ifdef DEBUG
BigCore::BigCore(uint64_t numberOfImages, uint64_t numberOfTiles, uint64_t imageHeight, uint64_t imageWidth, 
	             uint64_t numberOfPlanes, uint64_t dataOrder[5], uint64_t dataType, size_t dataLength, char * data)
:
_numberOfImages(numberOfImages),
_numberOfTiles(numberOfTiles),
_imageHeight(imageHeight),
_imageWidth(imageWidth),
_numberOfImagePlanes(numberOfPlanes),
_dataType(dataType),
_dataLength(dataLength)
{
	std::copy(dataOrder, dataOrder + 5, this->_dataOrder);

	this->_data = new char[this->_dataLength];
	// std::copy(data, data + int(dataLength), this->_data); // not sure why, but MVS doesn't support this on arrays
	for (size_t i = 0; i < dataLength; ++i)
		this->_data[i] = data[i];
}
#endif // DEBUG

uint64_t BigCore::alignToMultipleOf8(uint64_t length)
{
	return length % 8 == 0 ? length : length + 8 - length % 8;
}

void BigCore::writeChunk(std::ofstream &file, uint64_t id, uint64_t length, const char* data)
{
	file.write((char*)&id, CHUNK_LENGTH);

	uint64_t alignedLength = this->alignToMultipleOf8(length);
	file.write((char*)&alignedLength, CHUNK_LENGTH);
	file.write(data, length);

	// pad with zeros to align length to multiple of 8
	const char zero[] = { 0 };
	for (uint64_t i = 0; i < length % 8; ++i)
		file.write(zero, 1);
}

uint64_t BigCore::dataSize()
{
	uint64_t size = this->_imageWidth * this->_imageHeight * this->_numberOfImagePlanes * this->_numberOfImages * this->_numberOfTiles;

	if (this->_dataType == CHAR || this->_dataType == UNSIGNED_CHAR || this->_dataType == BOOL)
		return size;

	if (this->_dataType == SHORT || this->_dataType == UNSIGNED_SHORT)
		return size * 2;

	if (this->_dataType == FLOAT || this->_dataType == INT || this->_dataType == UNSIGNED_INT)
		return size * 4;

	if (this->_dataType == DOUBLE || this->_dataType == LONG_LONG || this->_dataType == UNSIGNED_LONG_LONG)
		return size * 8;

	// if neither, do not write data
	return 0;
}

void BigCore::writeFile(std::string fname)
{
	// this is for easier writing of lengths into file
	uint64_t length;

	std::ofstream file(fname, std::ios_base::binary);
	if (!file)
	{
		throw "Couldn't open file for writing";
	}

	// write header into file
	file.write(MAGIC, 8);

	// write number of images
	this->writeChunk(file, NUMBER_OF_IMAGES, CHUNK_LENGTH, (char*)&this->_numberOfImages);

	// write number of tiles
	this->writeChunk(file, NUMBER_OF_TILES, CHUNK_LENGTH, (char*)&this->_numberOfTiles);

	// write image width
	this->writeChunk(file, IMAGE_WIDTH, CHUNK_LENGTH, (char*)&this->_imageWidth);

	// write image height
	this->writeChunk(file, IMAGE_HEIGHT, CHUNK_LENGTH, (char*)&this->_imageHeight);

	// write number of image planes
	this->writeChunk(file, NUMBER_OF_IMAGE_PLANES, CHUNK_LENGTH, (char*)&this->_numberOfImagePlanes);

	// write data order -- arrays must be handled differently
	length = CHUNK_LENGTH * 5;

	file.write((char*)&DATA_ORDER, CHUNK_LENGTH);
	file.write((char*)&length, CHUNK_LENGTH);
	for (int i = 0; i < 5; ++i)
		file.write((char*)&this->_dataOrder[i], CHUNK_LENGTH);
	
	// write data types
	this->writeChunk(file, DATA_TYPE, CHUNK_LENGTH, (char*)&this->_dataType);

	// write data -- length must be multiplied by data type -- half float is 2 bytes, double is 8 bytes etc...
	this->writeChunk(file, DATA, this->dataSize(), this->_data);

	file.close();
}

bool BigCore::checkHeader(char buffer[8])
{
	for (uint64_t i = 0; i < CHUNK_LENGTH; ++i)
		if (buffer[i] != MAGIC[i])
			return false;
	return true;
}

uint64_t BigCore::getFileLength(std::ifstream &file)
{
	file.seekg(0, file.end);
	uint64_t length = file.tellg();

	// return to the beginning of the file!
	file.seekg(0, file.beg);
	return length;
}

void BigCore::readChunk(std::ifstream &file, uint64_t &id, uint64_t &length)
{
	file.read((char*)&id, CHUNK_LENGTH);
	file.read((char*)&length, CHUNK_LENGTH);
}

void BigCore::readData(std::ifstream &file, const uint64_t id, const uint64_t length)
{
	if (id == NUMBER_OF_IMAGES)
		file.read((char*)&this->_numberOfImages, length);
	else if (id == NUMBER_OF_TILES)
		file.read((char*)&this->_numberOfTiles, length);
	else if (id == IMAGE_WIDTH)
		file.read((char*)&this->_imageWidth, length);
	else if (id == IMAGE_HEIGHT)
		file.read((char*)&this->_imageHeight, length);
	else if (id == NUMBER_OF_IMAGE_PLANES)
		file.read((char*)&this->_numberOfImagePlanes, length);
	else if (id == DATA_ORDER)
	{
		for (int i = 0; i < 5; ++i)
			file.read((char*)&this->_dataOrder[i], CHUNK_LENGTH);
	}
	else if (id == DATA_TYPE)
		file.read((char*)&this->_dataType, length);
	else if (id == DATA)
	{
		if (this->_data)
		{
			delete[] this->_data;
		}
		this->_data = new char[length];
		file.read(this->_data, length);
		this->_dataLength = length;
	}
}

void BigCore::readFile(std::string fname)
{
	std::ifstream file(fname, std::ios_base::binary);

	if (!file)
	{
		throw "Couldn't open file for reading!";
	}

	char buffer[CHUNK_LENGTH];

	uint64_t fileLength = this->getFileLength(file);
	if (fileLength > CHUNK_LENGTH)
		file.read(buffer, CHUNK_LENGTH);
	else
		return;

	if (!checkHeader(buffer))
	{
		throw "Given file format is not a BIG format!";
	}

	// we have read CHUNK_LENGTH
	uint64_t loadedData = 8;

	uint64_t id = 0, length = 0;
	while (loadedData < fileLength)
	{
		if (loadedData + 16 <= fileLength)
		{
			loadedData += 16;
			this->readChunk(file, id, length);
#ifdef DEBUG
                        std::cout << "DEBUG: id: " << id << std::endl;
                        std::cout << "DEBUG: length: " << length << std::endl;
                        std::cout << "DEBUG: loaded data: " << loadedData << std::endl;
#endif

			if (loadedData + length <= fileLength)
			{
				loadedData += length;
				this->readData(file, id, length);
			}
		}
		else
			return;
	}
        // this->_dataLength = this->dataSize();

	file.close();

}

void BigCore::print()
{
	std::cout << "images: " << this->_numberOfImages << std::endl;
	std::cout << "tiles: " << this->_numberOfTiles << std::endl;
	std::cout << "height: " << this->_imageHeight << std::endl;
	std::cout << "width: " << this->_imageWidth << std::endl;
	std::cout << "planes: " << this->_numberOfImagePlanes << std::endl;
	std::cout << "data order ";
	for (int i = 0; i < 5; ++i)
		std::cout << this->_dataOrder[i] << std::endl;

	std::cout << "data type: " << this->_dataType << std::endl;
	std::cout << "data ";
	for (uint64_t i = 0; i < this->_dataLength; ++i)
		std::cout << int(this->_data[i]) << std::endl;
}

BigCore::~BigCore()
{
	if (this->_data)
		delete[] this->_data;
}
