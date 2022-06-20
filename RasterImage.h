#pragma once
#include "RasterImageBase.h"
class RasterImage : public RasterImageBase {
public:
	RasterImage(std::string name, int w, int h);/**< Parameter constructor */
    ~RasterImage();/**< Destructor. */
    void setPixel(size_t row, size_t col, unsigned int c) override;/**< @set value of given pixel in the image. */
	unsigned int getPixel(size_t r, size_t c) const override;/**< @return value of pixel in the image. */
};

