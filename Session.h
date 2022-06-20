#pragma once
#include <vector>
#include <stack>
#include "RasterImageBase.h"
#include <algorithm>
class SessionCommandBase;
/**
 * The Session class. It contains the images in the session
 * and stack with commands that will be eventually executed.
 * */
class Session {
private:
	int id_;

public:
	std::vector<RasterImageBase*> raster_images_;/**< Added images in session. */
	std::stack<SessionCommandBase*> command_stack_;/**< Stack with pending commands. */

	Session(RasterImageBase* img);/**< Parameter constructor */
	~Session();/**<  Destructor */
	void setId(size_t i);/**< @set ID of the session. */
	int getId() const;/**< @return ID of the session. */
	
	void applyAndPopTransformations();/**<  Executes all pending transformations. */
	RasterImageBase* getImage(const std::string& name);/**< @return the image with the given name if it's int the session. */
	void popImageFirst();/**< Removes the first image in the session */
	std::string getInformation();/**< Prints information about the session. */
};

