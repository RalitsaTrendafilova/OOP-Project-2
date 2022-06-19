#pragma once
#include "TransformationBase.h"
#include "RasterImageBase.h"

class ApplyNegative : public TransformationBase
{
public:
	ApplyNegative()
	{
		this->name_ += "negative";
	}
	void execute(RasterImageBase* image) override
	{
		uint32_t temp_color;
		uint8_t red;
		uint8_t blue;
		uint8_t green;
		
		for (size_t i = 0; i < image->getHeight(); i++) {
			for (size_t j = 0; j < image->getWidth(); j++) {
				temp_color = image->getPixel(i, j);
				red = (temp_color & RED_BITMASK) >> 24;
				blue = (temp_color & BLUE_BITMASK) >> 16;
				green = (temp_color & GREEN_BITMASK) >> 8;
				temp_color = (255 - red) << 24 | (255 - green) << 16 | (255 - blue) << 8 | 0xFF;
				image->setPixel(i, j, temp_color);
			}
		}
	}
};
