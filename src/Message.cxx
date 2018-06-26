#include <cstdarg>

#include "ArgParse/config.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	std::string currentMessage = "";
	FILE* STDOUT_Channel = stdout;
	FILE* STDERR_Channel = stderr;
	int DebugLevel = -1;
	bool Color = true;

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
		retval = vsnprintf(ARGPARSE_NULLPTR, 0, format, argcopy);
		va_end(argcopy);
		return retval;
	}

	void SetMessage(const char* format, ...) {
		va_list argptr;
		va_start(argptr, format);
		int the_length = _vscprintf(format, argptr)+1;
		char buffer[the_length];
		vsprintf(buffer, format, argptr);
		va_end(argptr);
		currentMessage = buffer;
	}

	void SetSTDOUTChannel(FILE* stdout_channel) {
		STDOUT_Channel = stdout_channel;
	}

	void SetSTDERRChannel(FILE* stderr_channel) {
		STDERR_Channel = stderr_channel;
	}

	void MessageStandardPrint(const char* format, ...) {
		if(STDOUT_Channel != ARGPARSE_NULLPTR) {
			va_list argptr;
			va_start(argptr, format);
			vfprintf(STDOUT_Channel, format, argptr);
			va_end(argptr);
		}
	}

	void MessageErrorPrint(const char* format, ...) {
		if(STDERR_Channel != ARGPARSE_NULLPTR) {
			va_list argptr;
			va_start(argptr, format);
			vfprintf(STDERR_Channel, format, argptr);
			va_end(argptr);
		}
	}
}
