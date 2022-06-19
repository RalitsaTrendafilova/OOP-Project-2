#include <climits>
#include "Session.h"
#include "SessionCommandBase.h"
#include "TransformationBase.h"
 Session::Session(RasterImageBase* img):id_(UINT_MAX)
{
	 this->raster_images_.push_back(img);
}
 void Session::printPendingTransformations() {}

  void Session::applyAndPopTransformations()
 {
	
		  for (size_t j = 0; j < raster_images_.size(); j++)
		  {
			  this->raster_images_[j]->applyAndPopTransformations();

		  }
	
	  
 }

   std::string Session::getInformation()
  {
	  std::string information;
	  information += "Name of images in the session: ";
	  for (auto raster_image : this->raster_images_)
	  {
		  information += raster_image->getName();
		  information += " ";
	  }
	  information += "\nPending transformations: ";


	  std::vector<TransformationBase*> unique_transformations;
	  for (size_t i = 0; i < this->raster_images_.size(); i++)
	  {
		  for (size_t j = 0; j < this->raster_images_[i]->pending_transformations_.size(); j++)
		  {
			  auto found = std::find(
				  unique_transformations.begin()
				  , unique_transformations.end(),
				  this->raster_images_[i]->pending_transformations_[j]);


			  if (found == unique_transformations.end())
			  {
				  information += this->raster_images_[i]->pending_transformations_[j]->getName() + " ";
				  unique_transformations.push_back(this->raster_images_[i]->pending_transformations_[j]);
			  }
		  }
	  }
	  information += "\n";
	  return information;
  }
