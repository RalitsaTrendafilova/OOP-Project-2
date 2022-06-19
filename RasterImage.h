#pragma once
#include "RasterImageBase.h"
class RasterImage : public RasterImageBase {
public:
	RasterImage(std::string name, int w, int h);
	~RasterImage();

	virtual void setPixel(size_t row, size_t col, unsigned int c) override;
	unsigned int getPixel(size_t r, size_t c) const override;
};

