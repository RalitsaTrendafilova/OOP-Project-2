#pragma once
#include <vector>
#include <stack>
#include "RasterImageBase.h"
#include <algorithm>
class SessionCommandBase;
typedef uint8_t SessionID;
class Session
{
private:
	int id_;

public:
	std::vector<RasterImageBase*> raster_images_;
	std::stack<SessionCommandBase*> command_stack_;

	Session(RasterImageBase*);
	~Session() 
	{
		for (size_t i = 0; i < raster_images_.size(); i++)
		{
			delete raster_images_[i];
		}


		while (!command_stack_.empty())
		{
			delete command_stack_.top();
			command_stack_.pop();
		}
	}
	void inline setId(int i) { this->id_ = i; }
	int inline getId() { return this->id_; }

	void printPendingTransformations();
	
	void applyAndPopTransformations();
	void popImage() { delete raster_images_.back(); raster_images_.pop_back(); }
	void clearAllImages() { raster_images_.clear(); }
	RasterImageBase* getImage(const std::string& name) 
	{
		auto foundImageWithName = std::find_if(this->raster_images_.begin(),
			this->raster_images_.end(), [=](RasterImageBase* ri) {return ri->getName() == name; });
		if (foundImageWithName!=raster_images_.end())
		{
			return *foundImageWithName;
		}
		return nullptr;
	}

	void popImageFirst() {
		delete raster_images_[0]; 
		raster_images_.erase(raster_images_.begin()); }


	std::string getInformation();
};

