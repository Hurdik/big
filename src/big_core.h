#ifndef _BIG_CORE_H_
#define _BIG_CORE_H_

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>

//using namespace std;

class BigCore
{
public:
	// allow only empty constructor
	// BigCore();

	void addTile(float *img);
	void addTile(int *img);
	// void addTile(Big *img);

	// void *getTile(/*number, etc.*/, uint8_t &dataType);

	// file de/serialization
	void writeFile(std::string fname);
	void readFile(std::string fname);

	static bool checkHeader(char buffer[8]);

	// setters
	void setNumberOfImages(unsigned numberOfImages);
	void setNumberOfTiles(unsigned numberOfTiles);
	void setImageHeight(unsigned imageHeight);
	void setImageWidth(unsigned imageWidth);
	void setNumberOfImagePlanes(unsigned numberOfImagePlanes);

	void setDataOrder(uint64_t dataOrder[5]);
	//void setDataType(unsigned dataType);
	//void setData(void *data);

	// getters
	unsigned getNumberOfImages();
	unsigned getNumberOfTiles();
	unsigned getImageHeight();
	unsigned getImageWidth();
	unsigned getNumberOfImagePlanes();
	std::vector<unsigned> getDataOrder();
	unsigned getDataType();
	//Array<T> getData();

	// destructor
	~BigCore();

protected:
	void writeChunk(std::ofstream &file, unsigned int id, unsigned int length, const char* data);

	void readChunk(std::ifstream &file, unsigned int &id, unsigned int &length);
	void readData(std::ifstream &file, const unsigned int id, const unsigned int length);

	unsigned int dataSize();
	unsigned int getFileLength(std::ifstream &file);

	uint64_t _numberOfImages;
	uint64_t _numberOfTiles;
	uint64_t _imageHeight;
	uint64_t _imageWidth;
	uint64_t _numberOfImagePlanes;
	uint64_t _dataOrder[5];
	// std::vector<uint8_t> _dataType;
	uint64_t _dataType;
	void *_data;

	std::vector<void *> _entity;

};

#endif // BIG_CORE_H
