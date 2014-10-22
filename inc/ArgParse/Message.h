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

#ifndef ARGPARSE_Message_HDR
#define ARGPARSE_Message_HDR

#include <string>

namespace ArgParse {
	int _vscprintf (const char * format, va_list pargs); 

	const std::string& GetMessage();

	void SetMessage(const std::string& message);
	void SetMessage(const char* format, ...);

	void SetSTDOUTChannel(FILE* stdout_channel);
	void SetSTDERRChannel(FILE* stderr_channel);

	void MessageStandardPrint(const char* format, ...);
	void MessageErrorPrint(const char* format, ...);
}

#define ArgParseMessagePrint(format, ...) ArgParse::MessageStandardPrint(format, ##__VA_ARGS__)
#define ArgParseMessageWarning(format, ...) ArgParse::MessageStandardPrint("%s-W (%s:%i): " format, __PRETTY_FUNCTION__, basename(__FILE__), __LINE__, ##__VA_ARGS__)
#define ArgParseMessageError(format, ...) ArgParse::MessageErrorPrint("%s-W (%s:%i): " format, __PRETTY_FUNCTION__, basename(__FILE__), __LINE__, ##__VA_ARGS__)

#endif
