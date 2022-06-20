#include "ApplyMonochrome.h"
ApplyMonochrome::ApplyMonochrome(){
    this->name_ += "monochrome";
}

void ApplyMonochrome::execute(RasterImageBase *image) {
    uint32_t temp_color;
    uint8_t red;
    uint8_t blue;
    uint8_t green;
    uint8_t gray;
    //Apply to all images that are not in monochrome format
    if (image->getType() != FileType::P1) {
        for (size_t i = 0; i < image->getHeight(); i++) {
            for (size_t j = 0; j < image->getWidth(); j++) {
                temp_color = image->getPixel(i, j);
                red = (temp_color & RED_BITMASK) >> 24;
                blue = (temp_color & BLUE_BITMASK) >> 16;
                green = (temp_color & GREEN_BITMASK) >> 8;

                gray = red / 3 + blue / 3 + green / 3;

                if (gray <= 128) {
                    //Convert to black
                    temp_color = 0x00000000;
                } else {
                    //Convert to white
                    temp_color = 0xFFFFFFFF;
                }
                image->setPixel(i, j, temp_color);
            }
        }
    }
}