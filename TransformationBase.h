#pragma once
#include <sstream>

class RasterImageBase;
/**
 *  The TransformationBase class. This is the base class for the transformations:
 *  grayscale, monochrome, negative, rotate.
 */
class TransformationBase {
protected:
	std::string name_;
public:
	const std::string& getName() {return name_;};/**< @return the name of the transformation. */
	virtual void execute (RasterImageBase*) = 0;
};

