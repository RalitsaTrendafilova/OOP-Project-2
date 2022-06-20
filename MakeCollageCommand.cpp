#include "MakeCollageCommand.h"
#include "RasterImage.h"
#include "Session.h"

MakeCollageCommand::MakeCollageCommand(Session *ses, std::string img_a, std::string img_b, std::string img_new,
                                       bool vertical): SessionCommandBase(ses),
                                                       image_name_new(img_new),
                                                       image_name_a(img_a),
                                                       image_name_b(img_b),
                                                       is_vertical(vertical) {
    this->success_message_ + "Collage made from " + image_name_a + "and " + image_name_b + "\n";
    this->success_message_ += "Image \"" + std::string(img_new) + "\" added \n";
}

void MakeCollageCommand::execute() {
	RasterImageBase* img, * img_a, * img_b;
	img_a = this->session_->getImage(image_name_a);
	if (img_a == nullptr) {
		throw std::invalid_argument("First image in collage not found!");
	}
	img_b = this->session_->getImage(image_name_b);
	if (img_b == nullptr) {
		throw std::invalid_argument("Second image in collage not found!");
	}
	if (img_a->getHeight() != img_b->getHeight() || img_a->getWidth() != img_b->getWidth()) {
		throw std::invalid_argument("Images have different dimensions!");
	}
	if (img_a->getType() != img_b->getType()) {
		throw std::invalid_argument("Images have different types!");
	}
	if (is_vertical) {
		img = new RasterImage(image_name_new,img_a->getWidth(), img_a->getHeight()+img_b->getHeight());
		img->setType(img_a->getType());
		img->setMaxValue(img_a->getMaxValue());
		//Copy pixels of first image
		for (size_t i = 0; i < img_a->getHeight(); i++) {
			for (size_t j = 0; j < img_a->getWidth(); j++) {
				img->setPixel(i, j, img_a->getPixel(i, j));
			}
		}
		//Copy pixels of second iamge
		for (size_t i = 0; i < img_b->getHeight(); i++) {
			for (size_t j = 0; j < img_b->getWidth(); j++) {
				img->setPixel(i+img_a->getHeight(), j, img_b->getPixel(i, j));
			}
		}
	} else {
		img = new RasterImage(image_name_new, img_a->getWidth() + img_b->getWidth(), img_a->getHeight());
		img->setType(img_a->getType());
		img->setMaxValue(img_a->getMaxValue());
		//Copy pixels of first image
		for (size_t i = 0; i < img_a->getHeight(); i++) {
			for (size_t j = 0; j < img_a->getWidth(); j++) {
				img->setPixel(i, j, img_a->getPixel(i, j));
			}
		}
		//Copy pixels of second iamge
		for (size_t i = 0; i < img_b->getHeight(); i++) {
			for (size_t j = 0; j < img_b->getWidth(); j++) {
				img->setPixel(i, j+img_a->getWidth(), img_b->getPixel(i, j));
			}
		}
	}
	this->session_->raster_images_.push_back(img);
}

void MakeCollageCommand::revert() {
	 auto foundImageWithName = std::find_if(this->session_->raster_images_.begin(),
		 this->session_->raster_images_.end(), [=](RasterImageBase* ri) {return ri->getName() == image_name_new; });
	 if (foundImageWithName != this->session_->raster_images_.end()) {
		 delete* foundImageWithName;
		 this->session_->raster_images_.erase(foundImageWithName);
	 }
}

