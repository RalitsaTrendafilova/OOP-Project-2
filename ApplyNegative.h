#pragma once
#include "TransformationBase.h"
#include "RasterImageBase.h"
/**
 *  The ApplyNegative class. It executes negative effect on images.
 */
class ApplyNegative : public TransformationBase {
public:
	ApplyNegative();/**< Default constructor */
	void execute(RasterImageBase* image) override;/**< Executes the transformation. */
};
