#pragma once
#ifndef _BIG_CORE_INPUT_H_
#define _BIG_CORE_INPUT_H_

#include "big_core_base.h"

#include <string>

class BigCoreInput : public BigCoreBase
{
public:
    // Empty constructor. Constructs an empty container, with no elements.
    BigCoreInput();

    // Input constructor. Opens file, reads parameters of the container, but does not read data.
    BigCoreInput(const std::string& fileName);

    // Copy constructor forbidden.
    BigCoreInput(const BigCoreInput &) = delete;

    // destructor
    ~BigCoreInput();

    // Opens file, reads parameters of the container, but does not read data.
	// which parameters?
    void openFile(const std::string& fileName);

    // Sets maximum possible size of memory that can be used and opens file, reads parameters and data to memory, if possible.
	static bool checkHeader(const char* buffer);
	bool readChunk(std::ifstream& file, uint64_t& id, uint64_t& length);
	void checkDataIntegrity(uint64_t& thisData, const uint64_t loadedData);
	bool readData(std::ifstream& file, const uint64_t id, const uint64_t length);
    void readFile(const std::string& fileName, const size_t bytes = DEFAULT_MEMORY_SIZE);

    // If possible, loads all data to memory. Does nothing if data are bigger than memory size. 
	// should it really do nothing if data are bigger?
    void loadToMemory(std::ifstream& file, size_t length);

	// All the four methods below are much more complicated -- not checking bounds doesn't seem right
	// also even though operator() may call operator [] as [imageNum * row * col * plane * tileNum]
	// BUT index of data cannot be simply index in char* data, it must be adjusted over each image data type
	// for example let's suppose i want to get some data in second image, where image data type of first image is float,
	// and image type of second image is double therefore to compute index of row * column * plane * tile * image, we need
	// to compute it like this:
	//
	// index = imageWidth * imageHeight * numberOfPlanes * numberOfTiles * sizeof(float) + row * column * plane * tile * sizeof(double)
	//
	// and this index then has to be compared against this->dataLength
	//
    // Access element in given image at given row, column, (color) plane and in given tile. Does not check bounds.
    template<typename T>
    const T & operator() (uint64_t imageNum, uint64_t row, uint64_t col, uint64_t plane = 0, uint64_t tileNum = 0) const;

    // Access the outermost entity of the container. If uniformDataType() is true, does not check bounds.
    template<typename T>
    const T & operator[] (size_t index) const;

    // Access element in given image at given row, column, (color) plane and in given tile. Checks bounds.
    template<typename T>
    const T & at(uint64_t imageNum, uint64_t row, uint64_t col, uint64_t plane = 0, uint64_t tileNum = 0) const;

    // Access the outermost entity of the container. Checks bounds.
    template<typename T>
    const T & at(uint64_t index) const;

    // Returns a direct pointer to the memory array used internally by the container to store its owned elements.
	// this doesn't make sense -- data might have different data type on each image
	// rather add method const T* getImage
    //template<typename T>
    //const T * data() const;

    // Returns tile specified by the number of image and the number of tile.
    // Data must be of size at least height x width x #planes x sizeof(T).
    template<typename T>
    T* getTile(uint64_t imageNum, uint64_t tileNum = 0);

    // Returns tile specified by the number of image and the number of tile.
    template<typename T>
    std::vector<T> getTile(uint64_t imageNum, uint64_t tileNum = 0);

    // todo: introduce constant iterators to iterate through tiles from first tile of the first image to last tile of the last image.

protected:
	bool lock;
};

#endif // _BIG_CORE_INPUT_H_
