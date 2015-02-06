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
#include <cstring>

namespace ArgParse {
	int _vscprintf (const char * format, va_list pargs); 

	const std::string& GetMessage();

	extern int DebugLevel;
	extern bool Color;

	void SetMessage(const std::string& message);
	void SetMessage(const char* format, ...);

	void SetSTDOUTChannel(FILE* stdout_channel);
	void SetSTDERRChannel(FILE* stderr_channel);

	void MessageStandardPrint(const char* format, ...);
	void MessageErrorPrint(const char* format, ...);
}

#define ARGPARSE_TNRM  "\x1B[0m"
#define ARGPARSE_TRED  "\x1B[31m"
#define ARGPARSE_TGRN  "\x1B[32m"
#define ARGPARSE_TYEL  "\x1B[33m"
#define ARGPARSE_TBLU  "\x1B[34m"
#define ARGPARSE_TMAG  "\x1B[35m"
#define ARGPARSE_TCYN  "\x1B[36m"
#define ARGPARSE_TWHT  "\x1B[37m"

#define ARGPARSE_TMSG ARGPARSE_TGRN
#define ARGPARSE_TERR ARGPARSE_TRED
#define ARGPARSE_TWRN ARGPARSE_TYEL
#define ARGPARSE_TDBG ARGPARSE_TBLU

#define ArgParseMessagePrint(format, ...) ArgParse::MessageStandardPrint(format, ##__VA_ARGS__)
#define ArgParseMessageWarning(format, ...) if(ArgParse::Color) { ArgParse::MessageStandardPrint("%s%s-W (%s:%i):%s " format, ARGPARSE_TWRN, __PRETTY_FUNCTION__, basename(__FILE__), __LINE__, ARGPARSE_TNRM, ##__VA_ARGS__); } else { ArgParse::MessageStandardPrint("%s-W (%s:%i): " format, __PRETTY_FUNCTION__, basename(__FILE__), __LINE__, ##__VA_ARGS__); }
#define ArgParseMessageError(format, ...) if(ArgParse::Color) { ArgParse::MessageErrorPrint("%s%s-E (%s:%i):%s " format, ARGPARSE_TERR, __PRETTY_FUNCTION__, basename(__FILE__), __LINE__, ARGPARSE_TNRM, ##__VA_ARGS__); } else { ArgParse::MessageErrorPrint("%s-E (%s:%i): " format, __PRETTY_FUNCTION__, basename(__FILE__), __LINE__, ##__VA_ARGS__); }

#endif
