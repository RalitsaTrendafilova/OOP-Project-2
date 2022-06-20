#pragma once
#include "TransformationBase.h"
#include "RasterImageBase.h"
/**
 *  The ApplyGrayscale class. It is used to transform PPM images to grayscale.
 */
class ApplyGrayscale : public TransformationBase {
public:
	ApplyGrayscale();/**< Default constructor */
	void execute(RasterImageBase* image) override;/**< Executes the transformation. */
};

