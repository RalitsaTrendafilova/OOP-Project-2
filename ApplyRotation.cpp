#include "ApplyRotation.h"

ApplyRotation::ApplyRotation(bool is_clockwise) : is_clowckwise_(is_clockwise) {
    this->name_ += "rotation";
    if (is_clowckwise_) {
        this->name_ += " right";
    } else {
        this->name_ += " left";
    }
}

void ApplyRotation::execute(RasterImageBase *image)  {
    //Change dimensions
    RasterImage* new_image = new RasterImage(image->getName(),image->getHeight(),image->getWidth());
    new_image->setType(image->getType());
    new_image->setMaxValue(image->getMaxValue());

    size_t new_row;
    size_t new_col;
    if (is_clowckwise_) {
        for (size_t i = 0; i < image->getHeight(); i++) {
            for (size_t j = 0; j < image->getWidth(); j++) {
                new_row = j;
                new_col = new_image->getWidth() - 1 - i;
                new_image->setPixel(new_row,new_col,image->getPixel(i, j));
            }
        }
    } else {
        for (size_t i = 0; i < image->getHeight(); i++) {
            for (size_t j = 0; j < image->getWidth(); j++) {
                new_row = new_image->getHeight() - 1 - j;
                new_col = i;
                new_image->setPixel(new_row, new_col, image->getPixel(i, j));
            }
        }
    }
    (*image) = (*new_image);
}
