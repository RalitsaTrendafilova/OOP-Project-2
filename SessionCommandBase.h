#pragma once
#include <sstream>
class Session;
/**
 *  The SessionCommandBase class. This is the base class for the commands:
 *  add image to session, make collage, add transformation to image in session.
 */
class SessionCommandBase {
protected:
	Session* session_;/**< In which session the command eventually will be executed. */
	std::string success_message_;/**< Information about how the execution of the command went. */
public:
	SessionCommandBase(Session* ses): session_(ses) {}/**< Parameter constructor */
	virtual void execute() = 0;
	virtual void revert() = 0;
	std::string get_success_msg() { return success_message_; } /**< @return the success message. */
};

