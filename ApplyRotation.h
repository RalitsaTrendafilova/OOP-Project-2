#pragma once
#include "TransformationBase.h"
#include "RasterImage.h"
/**
 *  The ApplyRotation class. It is used to rotate images.
 */
class ApplyRotation : public TransformationBase {
private:
	bool is_clowckwise_;/**< If the rotation is right or left. */
public:
	ApplyRotation(bool is_clockwise = true);/**< Default constructor */
	void execute(RasterImageBase* image) override;/**< Executes the transformation. */
};

