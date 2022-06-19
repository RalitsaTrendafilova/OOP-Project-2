#include "RasterImageBase.h"

size_t RasterImageBase::getWidth() const {
    return this->width_;
}

size_t RasterImageBase::getHeight() const {
    return this->height_;
}

FileType RasterImageBase::getType() const {
    return this->filetype_;
}

void RasterImageBase::setType(FileType t) {
    this->filetype_ = t;
}

unsigned int RasterImageBase::getMaxValue() const {
    return this->max_value_;
}

void RasterImageBase::setMaxValue(unsigned int mv) {
    this->max_value_ = mv;
}

RasterImageBase::RasterImageBase(std::string name, int w, int h): name_(name), width_(w), height_(h), filetype_(FileType::P3), max_value_(UINT8_MAX) {
    pixels_ = new unsigned int[width_*height_];
}

RasterImageBase &RasterImageBase::operator= (const RasterImageBase &x) {
    this->filetype_ = x.filetype_;
    this->width_ = x.width_;
    this->height_ = x.height_;
    this->pixels_ = x.pixels_;
    this->max_value_ = x.max_value_;
    this->name_ = x.name_;
    return *this;
}

void RasterImageBase::applyAndPopTransformations() {
    for (size_t i = this->pending_transformations_.size() - 1; i >= 0; --i) {
        this->pending_transformations_[i]->execute(this);
    }
    pending_transformations_.clear();

}
