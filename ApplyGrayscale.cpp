#include "ApplyGrayscale.h"

ApplyGrayscale::ApplyGrayscale() {
    this->name_ += "grayscale";
}
void ApplyGrayscale::execute(RasterImageBase *image) {
    uint32_t temp_color;
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t gray;
    //Only apply to image with color
    if (image->getType()==FileType::P3) {
        for (size_t i = 0; i < image->getHeight(); i++) {
            for (size_t j = 0; j < image->getWidth(); j++) {
                temp_color = image->getPixel(i, j);
                red = (temp_color & RED_BITMASK) >> 24;
                blue = (temp_color & BLUE_BITMASK) >> 16;
                green = (temp_color & GREEN_BITMASK) >> 8;

                gray = red / 3 + blue / 3 + green / 3;

                temp_color = gray << 24 | gray << 16 | gray << 8 | 0xFF;
                image->setPixel(i, j, temp_color);
            }
        }
    }
}
