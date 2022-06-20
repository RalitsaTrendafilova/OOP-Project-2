#pragma once
#include <sstream>
#include <utility>
#include <vector>
#include "TransformationBase.h"
#define RED_BITMASK 0xFF000000
#define BLUE_BITMASK 0x00FF0000
#define GREEN_BITMASK 0x0000FF00
/**
 * The FileType class. This is an enum class which shows the different types of files.
 * P1 and P4 are Portable BitMap type,
 * P2 and P5 are Portable GrayMap type,
 * P3 and P6 are Portable PixMap type.
 * P1, P2 and P3 are in ASCII format.
 * P4, P5 and P6 are in binary format.
 * */
enum class FileType {
	P1, P2, P3, P4, P5, P6
};
/**
 *  The RasterImageBase class. This is the base class for the images. It contains data for the image
 *  and vector in which are saved the pending transformations for the image.
 */
class RasterImageBase {
protected:
	std::string name_;
	size_t width_;
	size_t height_;
	FileType filetype_;
	unsigned int max_value_;/**< Maximum value of the colors in the image. */
	unsigned int* pixels_;/**< Array of all pixels in the image. */
	size_t get_index(size_t r, size_t c) const;/**< @return index of pixel in r-th row and in c-th column. */

public:
    RasterImageBase(std::string name, int w, int h);/**< Parameter constructor */
    RasterImageBase& operator=(const RasterImageBase& other);/**< Copy assignment operator. */
    ~RasterImageBase();
	size_t getWidth() const;/**< @return width of the image. */
	size_t getHeight() const;/**< @return height of the image. */

	FileType getType() const;/**< @return type of the image. */
	void setType(FileType t);/**< @set type of the image. */

	unsigned int getMaxValue() const;/**< @return maximum value of colors in the image. */
	void setMaxValue(unsigned int mv);/**< @set maximum value of colors in the image. */

	std::vector<TransformationBase*> pending_transformations_;/**< Contains the pending transformations for the image. */

	
	std::string getName() const;/**< @return name of the image. */
	void setName(std::string s);/**< @set name of the image. */
	virtual void setPixel(size_t, size_t, unsigned int) = 0;/**< @set value of given pixel in the image. */
	virtual unsigned int getPixel(size_t, size_t) const = 0;/**< @return value of pixel in the image. */

	void applyAndPopTransformations();/**< Executes all pending transformations for the image. */
};

