#include <cstdint>

#include "../include/big_core_base.h"

BigCoreBase::BigCoreBase()
	:
	outermostEntitiesOffsets(0)
{}

uint64_t BigCoreBase::getNumberOfImages()
{
	return this->numberOfImages;
}

uint64_t BigCoreBase::getNumberOfTiles()
{
	return this->numberOfTiles;
}

uint64_t BigCoreBase::getImageHeight()
{
	return this->imageHeight;
}

uint64_t BigCoreBase::getImageWidth()
{
	return this->imageWidth;
}

uint64_t BigCoreBase::getNumberOfPlanes()
{
	return this->numberOfPlanes;
}

bool BigCoreBase::isEmpty()
{
	return this->dataLength == 0 ? true : false;
}

void BigCoreBase::clear()
{
	if (this->data)
		delete[] this->data;
}

bool BigCoreBase::isInMemory()
{
	// TODO: implement
	;
}

void BigCoreBase::setMemorySize(const size_t bytes)
{
	this->memorySize = bytes;
}

size_t BigCoreBase::size()
{
	return this->dataLength;
}

size_t BigCoreBase::sizeInMemory()
{
	// TODO: implement
}

size_t BigCoreBase::getImageType(const uint64_t dataType)
{
	DataTypes dType = static_cast<DataTypes>(dataType);

	if (dType == DataTypes::CHAR || dType == DataTypes::UNSIGNED_CHAR || dType == DataTypes::BOOL)
		return 1;

	if (dType == DataTypes::SHORT || dType == DataTypes::UNSIGNED_SHORT || dType == DataTypes::HALF)
		return 2;

	if (dType == DataTypes::FLOAT || dType == DataTypes::INT || dType == DataTypes::UNSIGNED_INT)
		return 4;

	if (dType == DataTypes::DOUBLE || dType == DataTypes::LONG_LONG || dType == DataTypes::UNSIGNED_LONG_LONG)
		return 8;

	return 0;
}

size_t BigCoreBase::imageSizeRaw()
{
	return this->imageWidth * this->imageHeight * this->numberOfPlanes * this->numberOfTiles;
}

size_t BigCoreBase::imageSize(const uint64_t dataType)
{
	return this->getImageType(dataType) * this->imageSizeRaw();	
}

bool BigCoreBase::isUniformDataType()
{
	return this->dataType.size() == 1 ? true : false;
}

BigCoreBase::~BigCoreBase()
{
	if (this->data)
		delete[] this->data;
}
