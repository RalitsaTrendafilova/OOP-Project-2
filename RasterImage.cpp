#include "RasterImage.h"

RasterImage::RasterImage(std::string name, int w, int h): RasterImageBase(name,w,h) {}

RasterImage::~RasterImage() {
    delete[] pixels_;
}

void RasterImage::setPixel(size_t row, size_t col, unsigned int c) {
    this->pixels_[this->get_index(row, col)] = c;
}

unsigned int RasterImage::getPixel(size_t r, size_t c) const {
    return pixels_[this->get_index(r, c)];
}
