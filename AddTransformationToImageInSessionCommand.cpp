#include "AddTransformationToImageInSessionCommand.h"

AddTransformationToImageInSessionCommand::AddTransformationToImageInSessionCommand(Session *ses, TransformationBase *t)
    : SessionCommandBase(ses), transformation_(t) {}

void AddTransformationToImageInSessionCommand::execute()  {
    for (auto image : this->session_->raster_images_) {
        image->pending_transformations_.push_back(transformation_);
    }
}

void AddTransformationToImageInSessionCommand::revert() {
    for (auto image : this->session_->raster_images_) {
        image->pending_transformations_.pop_back();
    }
}
