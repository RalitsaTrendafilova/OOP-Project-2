#pragma once
#include <sstream>
class Session;
class SessionCommandBase {
protected:
	Session* session_;
	std::string success_message_;
public:
	SessionCommandBase(Session* ses): session_(ses) {}
	virtual void execute() = 0;
	virtual void revert() = 0;
	std::string get_success_msg() { return success_message_; }
};

