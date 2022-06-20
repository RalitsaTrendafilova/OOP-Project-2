#pragma once
#include <vector>
#include <iostream>
#include "Session.h"
#include "RasterImageBase.h"
#include "RasterImageRW.h"
#include "SessionCommandBase.h"
#include <algorithm>
/**
 *  Github: https://github.com/RalitsaTrendafilova/OOP-Project-2.git
 *  The ApplicationController class. It contains the run() method which starts the application,
 *  all started sessions and the current active session, and the main functionalities of the application.
 */
class ApplicationController {
private:
	std::string line;
	std::vector<std::string> tokens;
	RasterImageReader image_RW_;

	void tokenize_string(const std::string& line);/**< Breaks down the command in tokens(words). */
	SessionCommandBase* translate_tokens_to_command(const std::vector<std::string>& tokens) const;/**< Translate the tokens to a command. */

	void saveSessionImages();/**< Saves all images in the session, after executing the pending transformations. */
	void saveImageAs(const std::string& f);/**< Saves a image in file with the given name, after executing all pending transformations for the image. */

public:
	std::vector<Session*> sessions_;/**< All sessions. */
	Session* active_;/**< The current active session. */

    static ApplicationController& getApplicationController();/**< @return instance of type ApplicationController. */
	void run();/**< Runs the application. */
};

