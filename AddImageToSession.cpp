#include "AddImageToSession.h"
#include "ApplicationController.h"
AddImageToSession::AddImageToSession(Session* ses,std::string filename) : SessionCommandBase(ses),filename_(filename) {
	this->success_message_ += "Image \"" + std::string(filename_) + "\" added \n";
}

void AddImageToSession::execute() {
    auto foundImageWithName = std::find_if(this->session_->raster_images_.begin(),
                                            this->session_->raster_images_.end(), [=]( RasterImageBase* ri) {return ri->getName()==filename_; });
    if (foundImageWithName == this->session_->raster_images_.end()) {
        RasterImageBase* img = reader_.read(filename_);
        this->session_->raster_images_.push_back(img);
    } else {
        throw std::invalid_argument("The image is already added to the session!\n");
    }
}

void AddImageToSession::revert() {
	 auto foundImageWithName = std::find_if(this->session_->raster_images_.begin(),
		 this->session_->raster_images_.end(), [=]( RasterImageBase* ri) {return ri->getName()==filename_; });
	 if (foundImageWithName != this->session_->raster_images_.end()) {
		 delete* foundImageWithName;
		 this->session_->raster_images_.erase(foundImageWithName);
	 }
}
