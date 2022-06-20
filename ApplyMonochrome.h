#pragma once
#include "TransformationBase.h"
#include "RasterImageBase.h"
/**
 *  The ApplyMonochrome class. It is used to transform PPM and PGM images to monochrome.
 */
class ApplyMonochrome : public TransformationBase {
public:
	ApplyMonochrome();/**< Default constructor */
	void execute(RasterImageBase* image) override;/**< Executes the transformation. */
};

