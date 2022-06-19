#pragma once
#include <sstream>
#include "RasterImageBase.h"

class RasterImageBase;
class TransformationBase {
protected:
	std::string name_;
public:
	const std::string& getName() {return name_;};
	virtual void execute(RasterImageBase*) = 0;
};

