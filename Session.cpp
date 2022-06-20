#include <climits>
#include "Session.h"
#include "SessionCommandBase.h"
Session::Session(RasterImageBase* img):id_(UINT_MAX) {
	 this->raster_images_.push_back(img);
}
Session::~Session() {
    for (size_t i = 0; i < raster_images_.size(); i++) {
        delete raster_images_[i];
    }
    while (!command_stack_.empty()) {
        delete command_stack_.top();
        command_stack_.pop();
    }
}
void Session::applyAndPopTransformations() {
  for (size_t j = 0; j < raster_images_.size(); j++) {
      this->raster_images_[j]->applyAndPopTransformations();
  }
}
std::string Session::getInformation() {
  std::string information;
  information += "Name of images in the session: ";
  for (auto raster_image : this->raster_images_) {
      information += raster_image->getName();
      information += " ";
  }
  information += "\nPending transformations: ";
  std::vector<TransformationBase*> unique_transformations;
  for (size_t i = 0; i < this->raster_images_.size(); i++) {
      for (size_t j = 0; j < this->raster_images_[i]->pending_transformations_.size(); j++) {
          auto found = std::find(unique_transformations.begin(), unique_transformations.end(),
              this->raster_images_[i]->pending_transformations_[j]);
          if (found == unique_transformations.end()) {
              information += this->raster_images_[i]->pending_transformations_[j]->getName() + " ";
              unique_transformations.push_back(this->raster_images_[i]->pending_transformations_[j]);
          }
      }
  }
  information += "\n";
  return information;
}
void Session::setId(size_t i)  {
    this->id_ = i;
}
int Session::getId() const {
    return this->id_;
}
RasterImageBase *Session::getImage(const std::string &name) {
    auto foundImageWithName = std::find_if(this->raster_images_.begin(),
                                           this->raster_images_.end(), [=](RasterImageBase* ri) {return ri->getName() == name; });
    if (foundImageWithName != raster_images_.end()) {
        return *foundImageWithName;
    }
    return nullptr;
}
void Session::popImageFirst() {
    delete raster_images_[0];
    raster_images_.erase(raster_images_.begin());
}

