#include <cstdarg>

#include "ArgParse/Message.h"

namespace ArgParse {
	std::string currentMessage = "";

	const std::string& GetMessage() {
		return currentMessage;
	}

	void SetMessage(const std::string& message) {
		currentMessage = message;
	}

	int _vscprintf (const char* format, va_list pargs) { 
		int retval; 
		va_list argcopy; 
		va_copy(argcopy, pargs); 
		retval = vsnprintf(NULL, 0, format, argcopy); 
		va_end(argcopy); 
		return retval; 
	}

	void SetMessage(const char* format,...) {
		va_list argptr;
		va_start(argptr, format);
		int the_length = _vscprintf(format, argptr)+1;
		char buffer[the_length];
		vsprintf(buffer, format, argptr);
		va_end(argptr);
		currentMessage = buffer;
	}
}
