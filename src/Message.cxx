/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014  Matthew Scott Krafczyk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cstdarg>

#include "ArgParse/config.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	std::string currentMessage = "";
	FILE* STDOUT_Channel = stdout;
	FILE* STDERR_Channel = stderr;
	int DebugLevel = -1;

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
