#pragma once
#include "RasterImageBase.h"
#include <fstream>
/**
 * The RasterImageReader class. It is used to read the data for the image from a file.
 * It saves the data in object of type RasterImageBase.
 * */
class RasterImageReader {
private:
    static bool is_in_binary (FileType t);/**< @return true if the image is in binary format. */
	static unsigned int get_color_from_asci (std::ifstream& stream, FileType type, int max_value_ = 1);/**< @return colour value of pixel converted from ascii number. */
	static void write_asci_from_pixel (std::ofstream& stream, const RasterImageBase* img_base, unsigned int pixel);/**< @return ascii number of pixel value. */
	static FileType get_filetype_from_name (const std::string& f);/**< @return the file type of the image, read from string. */

public:
	static RasterImageBase* read (const std::string &filename);/**< Reads the data for the image from a file. */
	static void save (RasterImageBase*, const std::string& filename);/**< Writes the data for a given image in a file. */
};

