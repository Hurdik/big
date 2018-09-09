#pragma once
#ifndef _BIG_CORE_OUTPUT_H_
#define _BIG_CORE_OUTPUT_H_

#include "big_core_base.h"

#include <string>

class BigCoreOutput : public BigCoreBase
{
public:
    // Empty constructor. Constructs an empty container, with no elements.
    BigCoreOutput();

    // Reserve constructor. Constructs an empty container and sets its dimensions.
    // Data order and data type are set to default values.
    // Does not allocate any memory. It will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Reserve constructor. Constructs an empty container, sets data order and dimensions of the container.
    // Data type is set to default value.
    // Does not allocate any memory. It will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::vector<uint64_t>& dataOrder, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Reserve constructor. Constructs an empty container, sets data type(s) and dimensions of the container.
    // Data order is set to default value.
    // Does not allocate any memory. It will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::vector<uint8_t>& dataType, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Reserve constructor. Constructs an empty container, sets data order, data type(s) and dimensions of the container.
    // Does not allocate any memory. It will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::vector<uint64_t>& dataOrder, const std::vector<uint8_t>& dataType, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Output and reserve constructor. Opens file, constructs an empty container and sets its dimensions.
    // Data order and data type are set to default values.
    // Does not allocate any memory nor writes to file. Memory will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::string& fileName, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Output and reserve constructor. Opens file, constructs an empty container, sets data order and dimensions of the container.
    // Data type is set to default value.
    // Does not allocate any memory nor writes to file. Memory will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::string& fileName, const std::vector<uint64_t>& dataOrder, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Output and reserve constructor. Opens file, constructs an empty container, sets data type(s) and dimensions of the container.
    // Data order is set to default value.
    // Does not allocate any memory nor writes to file. Memory will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::string& fileName, const std::vector<uint8_t>& dataType, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Output and reserve constructor. Opens file, constructs an empty container, sets data order, data type(s) and dimensions of the container.
    // Does not allocate any memory nor writes to file. Memory will be allocated during first asignment of data or when reserve() method is called. 
    BigCoreOutput(const std::string& fileName, const std::vector<uint64_t>& dataOrder, const std::vector<uint8_t>& dataType, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);

    // Destructor. 
    ~BigCoreOutput();

    // Opens file, but does not write data.
    void openFile(const std::string& fileName);

    // Writes parameters and data to file. Keeps file open for additional writes when new data are provided.
    void writeFile(const std::string& fileName);

    // Writes parameters and data to file specified earlier. Keeps file open for additional writes when new data are provided.
    void writeFile();

    // Closes attached file.
    void closeFile();

    // setters
    // todo: provide comments of individual methods
    void setParameters(uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);
    void setParameters(const std::vector<uint64_t>& dataOrder, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);
    void setParameters(const std::vector<uint8_t>& dataType, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);
    void setParameters(const std::vector<uint64_t>& dataOrder, const std::vector<uint8_t>& dataType, uint64_t numberOfImages, uint64_t imageHeight, uint64_t imageWidth, uint64_t numberOfPlanes = 1, uint64_t numberOfTiles = 1);
    void setNumberOfImages(uint64_t numberOfImages);
    void setNumberOfTiles(uint64_t numberOfTiles);
    void setImageHeight(uint64_t imageHeight);
    void setImageWidth(uint64_t imageWidth);
    void setNumberOfPlanes(uint64_t numberOfPlanes);
    void setDataOrder(const std::vector<uint64_t>& dataOrder);
    void setDataType(const std::vector<uint8_t>& dataType);

    // Reserves required space in memory (and in file, if fileName has been provided). Dimensions, data order or data type(s) of the container cannot be changed any more.
    void reserve();

    // Access element in given image at given row, column, (color) plane and in given tile. Does not check bounds.
    template<typename T>
    T & operator() (uint64_t imageNum, uint64_t row, uint64_t col, uint64_t plane = 0, uint64_t tileNum = 0);

    // Access the outermost entity of the container. If uniformDataType() is true, does not check bounds.
    template<typename T>
    T & operator[] (uint64_t index);

    // Access element in given image at given row, column, (color) plane and in given tile. Checks bounds.
    template<typename T>
    T & at(uint64_t imageNum, uint64_t row, uint64_t col, uint64_t plane = 0, uint64_t tileNum = 0);

    // Access the outermost entity of the container. Checks bounds.
    template<typename T>
    T & at(uint64_t index);

    // Returns a direct pointer to the memory array used internally by the container to store its owned elements.
    template<typename T>
    T * data();


    // Adds data of the tile specified by the number of image and the number of the tile.
    // Data must be of size at least height x width x #planes x sizeof(T).
    template<typename T>
    void addTile(const T *data, uint64_t imageNum, uint64_t tileNum = 0);

    // Adds data of the tile specified by the number of image and the number of the tile.
    // Data must be of size at least height x width x #planes x sizeof(T).
    template<typename T>
    void addTile(const std::vector<T>& data, uint64_t imageNum, uint64_t tileNum = 0);

    // todo: introduce (non-constant) iterators to iterate through tiles from first tile of the first image to last tile of the last image.

protected:

    // protected methods

protected:

    bool changesAllowed = true;

};

#endif // _BIG_CORE_OUTPUT_H_ 