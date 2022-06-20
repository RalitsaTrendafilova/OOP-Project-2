#include "RasterImageBase.h"

RasterImageBase::RasterImageBase(std::string name, int w, int h): name_(name), width_(w), height_(h), filetype_(FileType::P3), max_value_(UINT8_MAX) {
    pixels_ = new unsigned int[width_*height_];
}
RasterImageBase &RasterImageBase::operator= (const RasterImageBase &other) {
    this->filetype_ = other.filetype_;
    this->width_ = other.width_;
    this->height_ = other.height_;
    this->pixels_ = other.pixels_;
    this->max_value_ = other.max_value_;
    this->name_ = other.name_;
    return *this;
}
RasterImageBase::~RasterImageBase() {
    delete[] pixels_;
}
size_t RasterImageBase::get_index(size_t r, size_t c) const {
    return r * width_ + c;
}
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
std::string RasterImageBase::getName() const {
    return name_;
}
void RasterImageBase::setName(std::string s) {
    this->name_ = std::move(s);
}
void RasterImageBase::applyAndPopTransformations() {
    for (int i = this->pending_transformations_.size() - 1; i >= 0; --i) {
        this->pending_transformations_[i]->execute(this);
    }
    pending_transformations_.clear();
}




