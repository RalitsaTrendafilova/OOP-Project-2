#pragma once
#include "SessionCommandBase.h"
#include "Session.h"
#include "RasterImageRW.h"
/**
 * The AddImageToSession  class. It is used to add image in the active session.
 * It can also remove a given image from the session.
 * */
class AddImageToSession : public SessionCommandBase {
	std::string filename_;/**< Name of the image that will be added. */
	RasterImageReader reader_;/**< The reader_ will read the image from the file and turn it in object of type RasterImageBase. */
public:
	AddImageToSession(Session* target, std::string filename);/**< Parameter constructor */
	void execute() override;/**< Adds the image in the active session. */
	void revert() override;/**< Removes the last image in the session when undo is used and there are no pending transformations. */
};

//commands - addimagetosession, makecollage, sessioncommandbase, addtransformationtoimageinsession
//imagetransformations - apply*
