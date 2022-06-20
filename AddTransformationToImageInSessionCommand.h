#pragma once
#include "SessionCommandBase.h"
#include "Session.h"
#include "ApplicationController.h"
/**
 * The AddTransformationToImageInSessionCommand class.
 * It is used to add a given transformation to the images in the active session.
 * */
class AddTransformationToImageInSessionCommand : public SessionCommandBase {
private:
	TransformationBase* transformation_;
public:
	AddTransformationToImageInSessionCommand(Session* ses , TransformationBase* t);/**< Parameter constructor */
	void execute() override;/**< Adds the transformation in the pending transformations for the images in the session. */
	void revert() override;/**< Removes the last pending transformation for the images. */
};

