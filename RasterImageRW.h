#pragma once
#include "RasterImageBase.h"
#include <fstream>

class RasterImageReader {
private:
	static bool is_in_binary (FileType t);
	static unsigned int get_color_from_asci (std::ifstream& stream, FileType type, int max_value_ = 1);
	static void write_asci_from_pixel (std::ofstream& stream, const RasterImageBase* img_base, unsigned int pixel);
	static FileType get_filetype_from_name (const std::string& f);

public:
	static RasterImageBase* read (const char* filename);
	static void save (RasterImageBase*, const char* filename);
};

