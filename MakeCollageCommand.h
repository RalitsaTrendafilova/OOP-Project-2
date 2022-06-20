#pragma once
#include "SessionCommandBase.h"
/**
 *  The MakeCollageCommand class. It is used to make collage from to images.
 *  The collage can be vertical or horizontal.
 */
class MakeCollageCommand : public SessionCommandBase {
private:
	std::string image_name_a;/**< Name of first image. */
	std::string image_name_b;/**< Name of second image. */
	std::string image_name_new;/**< Name of collage. */
	bool is_vertical;/**< If the collage is vertical or horizontal. */
public:
	MakeCollageCommand(Session* ses, std::string img_a, std::string img_b, std::string img_new, bool vertical=true);/**< Parameter constructor */
	void execute();/**< Executes the transformation. */
	void revert();/**< Deletes the collage. */
};

