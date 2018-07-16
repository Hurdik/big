#include <fstream>

#include "big_core.h"
#include "big_consts.h"

void BigCore::writeChunk(std::ofstream &file, unsigned int id, unsigned int length, const char* data)
{
	file.write((char*)&id, CHUNK_LENGTH);
	file.write((char*)&length, CHUNK_LENGTH);

	// this is for fixating length to be multiple of 8
	if (length % 8 > 0)
		length = length + 8 - (length % 8);

	file.write(data, length);
}

unsigned int BigCore::dataSize()
{
	unsigned int size = this->_imageWidth * this->_imageHeight * this->_numberOfImagePlanes * this->_numberOfImages;

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
	int length;

	std::ofstream file(fname, std::ios_base::binary);
	if (!file)
	{
		// do something when file couldn't be opened
		return;
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
	// length = this->_dataType.size();
	this->writeChunk(file, DATA_ORDER, CHUNK_LENGTH, (char*)&this->_dataType);

	// write data -- length must be multiplied by data type -- half float is 2 bytes, double is 8 bytes etc...
	this->writeChunk(file, DATA, this->dataSize, (char*)&this->_data);

	file.close();
}

bool BigCore::checkHeader(char buffer[8])
{
	for (int i = 0; i < CHUNK_LENGTH; ++i)
		if (buffer[i] != MAGIC[i])
			return false;
	return true;
}

unsigned int BigCore::getFileLength(std::ifstream &file)
{
	file.seekg(0, file.end);
	unsigned int length = file.tellg();

	// return to the beginning of the file!
	file.seekg(0, file.beg);
	return length;
}

void BigCore::readChunk(std::ifstream &file, unsigned int &id, unsigned int &length)
{
	file.read((char*)&id, CHUNK_LENGTH);
	file.read((char*)&length, CHUNK_LENGTH);
}

void BigCore::readData(std::ifstream &file, const unsigned int id, const unsigned int length)
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
		file.read((char*)&this->_data, length);
}

void BigCore::readFile(std::string fname)
{
	std::ifstream file(fname, std::ios_base::binary);

	if (!file)
	{
		// do something when file couldn't beopened
		return;
	}

	char buffer[CHUNK_LENGTH];

	unsigned int fileLength = this->getFileLength(file);
	if (fileLength > CHUNK_LENGTH)
		file.read(buffer, CHUNK_LENGTH);
	else
		return;

	if (!checkHeader(buffer))
	{
		// in case of wrong header do something -- what?
		return;
	}

	// we have read CHUNK_LENGTH
	unsigned int loadedData = 8;

	unsigned int fileLength = this->getFileLength(file);
	unsigned int id, length;
	while (loadedData < fileLength)
	{
		if (loadedData + 16 <= fileLength)
		{
			loadedData += 16;
			this->readChunk(file, id, length);
			if (loadedData + length <= fileLength)
			{
				loadedData += length;
				this->readData(file, id, length);
			}
		}
		else
			return;
	}
}
