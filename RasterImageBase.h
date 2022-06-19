#pragma once
#include <sstream>
#include <utility>
#include <vector>
#include "TransformationBase.h"
#define RED_BITMASK 0xFF000000
#define BLUE_BITMASK 0x00FF0000
#define GREEN_BITMASK 0x0000FF00

enum class FileType {
	P1, P2, P3, P4, P5, P6
};
class RasterImageBase {
protected:
	std::string name_;
	size_t width_;
	size_t height_;
	FileType filetype_;
	unsigned int max_value_;
	unsigned int* pixels_;
	size_t get_index(size_t r, size_t c) const {return r * width_ + c;}

public:
	size_t getWidth() const;
	size_t getHeight() const;

	FileType getType() const;
	void setType(FileType t);

	unsigned int getMaxValue() const;
	void setMaxValue(unsigned int mv);

	std::vector<TransformationBase*> pending_transformations_;

	RasterImageBase(std::string name, int w, int h);

	RasterImageBase& operator=(const RasterImageBase& x);
	
	std::string getName() const { return name_; };
	void setName(std::string s) { this->name_ = std::move(s); }
	virtual void setPixel(size_t, size_t, unsigned int) = 0;
	virtual unsigned int getPixel(size_t, size_t) const = 0;

	void applyAndPopTransformations();
};

