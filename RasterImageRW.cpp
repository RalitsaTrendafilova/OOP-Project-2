#include "RasterImageRW.h"
#include "RasterImage.h"

bool RasterImageReader::is_in_binary(FileType t) {
    return t == FileType::P4 || t == FileType::P5 || t == FileType::P6;
}
unsigned int RasterImageReader::get_color_from_asci (std::ifstream& stream, FileType type, int max_value_) {
	if (type == FileType::P1) {
		//Monochrome
		char asci_val;
		stream >> asci_val;
		bool val = asci_val - 48;
		if (val) {
			//Black
			return 0x000000ff;
		} else {
			//White
			return 0xffffffff;
		}
	}
	else if (type == FileType::P2) {
		std::string str;
		stream >> str;
		//Grayscale
		int grayscale_val = std::stoi(str);
		if (grayscale_val >= 3) {
			int a = 3;
		}
		float whiteness_percent = (float)grayscale_val / (float)max_value_;
		unsigned short channel_shade = 255 * whiteness_percent;
		unsigned int final_color = channel_shade << 24 | channel_shade << 16 | channel_shade << 8 | 0xFF;
		return final_color;
	} else if (type == FileType::P3) {
		std::string str;
		stream >> str;
		unsigned short red = std::stoi(str);
		stream >> str;
		unsigned short blue = std::stoi(str);
		stream >> str;
		unsigned short green = std::stoi(str);
		unsigned int final_color = red << 24 | blue << 16 | green << 8 | 0xFF;
		return final_color;
	}
}
void RasterImageReader::write_asci_from_pixel(std::ofstream& stream, const RasterImageBase* img_base, unsigned int pixel) {
	if (img_base->getType() == FileType::P1) {
		//Monochrome
		//Only the least significant bits contribute to the alpha channel
		//therefore every number higher than 255 or 0x000000FF will have color
		if (pixel>255) {
			stream << std::to_string(1);
		} else {
			stream << std::to_string(0);
		}
	}
	else if (img_base->getType() == FileType::P2) {
		//Grayscale
		unsigned short shade_val = ( pixel & RED_BITMASK ) >> 24;
		unsigned short val;
		val = shade_val * ((float)img_base->getMaxValue()/255.0f);
		if (val > img_base->getMaxValue()) {
			val = img_base->getMaxValue();
		}
		stream << std::to_string(val);
	}
	else if (img_base->getType() == FileType::P3) {
		unsigned short red  = (pixel & RED_BITMASK) >> 24;
		unsigned short blue  = (pixel & BLUE_BITMASK) >> 16;
		unsigned short green = (pixel & GREEN_BITMASK) >> 8;

		stream << std::to_string(red)   << " ";
		stream << std::to_string(blue)  << " ";
		stream << std::to_string(green);	
	}
}
FileType RasterImageReader::get_filetype_from_name(const std::string &f) {
    std::string::size_type position_of_dot = f.rfind('.');
    std::string filetype_str = f.substr(position_of_dot + 1, 3);
    if (filetype_str=="ppm") {
        return FileType::P3;
    } else if (filetype_str == "pgm") {
        return FileType::P2;
    } else if (filetype_str == "pbm") {
        return FileType::P1;
    }
    return FileType::P3;
}

RasterImageBase* RasterImageReader::read(const char* filename) {
	RasterImageBase* raster_image = nullptr;
	std::ifstream ifstream{ filename };

	FileType file_type;
	size_t width, height;
	int max_value_ = 1;
	if (ifstream) {
		char c;
		ifstream >> c;
		//First char of the file should be the letter P
		if (c == 'P') {
			ifstream >> c;
			short magic_number = c - 48;
			//next character determines the magic number
			//Between 1 and 6
			if (magic_number >= 1 && magic_number <= 6) {
				file_type = (FileType)(magic_number - 1);
				//Read the dimension of the raster image

				ifstream >> width;
				ifstream >> height;


				//Read max value if not monochrome
				if (file_type != FileType::P1) {
					ifstream >> max_value_;
				}

				//Init array
				raster_image = new RasterImage(filename, width, height);
				raster_image->setMaxValue(max_value_);
				raster_image->setType(file_type);

				if (!is_in_binary(file_type)) {
					for (size_t i = 0; i < height; i++) {
						for (size_t j = 0; j < width; j++) {
							raster_image->setPixel(i, j, get_color_from_asci(ifstream, file_type, max_value_));
						}
					}
				}
				return raster_image;
			}
			else {
				throw std::runtime_error("Unrecognized File Type!");
			}
		}


	}
	else {
		throw std::runtime_error("Unable to open file!");
	}
	ifstream.close();
}
void RasterImageReader::save( RasterImageBase* raster_image, const char* filename) {
	std::string used_filename;
	if (filename == "") {
		used_filename = raster_image->getName();
	} else {
		used_filename = filename;
	}

	std::ofstream ofstream(used_filename);
	if (ofstream) {
		//Changed file type to be of desired file
		if (raster_image->getType() != get_filetype_from_name(used_filename)) {
			throw std::invalid_argument("Mismatch in original file type and output file type! \n");
		}

		ofstream << 'P' << std::to_string((int)raster_image->getType() + 1) <<"\n";
		ofstream << std::to_string(raster_image->getWidth())  << " " << 
			std::to_string(raster_image->getHeight()) << "\n";

		//Write max value if not monochrome
		if (raster_image->getType() != FileType::P1) {
			ofstream << std::to_string(raster_image->getMaxValue()) << "\n";
		}
		if (!is_in_binary(raster_image->getType())) {
			for (size_t i = 0; i < raster_image->getHeight(); i++) {
				for (size_t j = 0; j < raster_image->getWidth(); j++) {
					write_asci_from_pixel(ofstream, raster_image, raster_image->getPixel(i,j));
					ofstream << " ";
				}
				ofstream << "\n";
			}
		}
	}
	ofstream.close();
}




