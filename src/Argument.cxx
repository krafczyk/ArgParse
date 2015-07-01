/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2015  Matthew Scott Krafczyk

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

#include <sstream>
#include <cerrno>
#include <climits>
#include <cmath>

#include "ArgParse/Argument.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	const Argument::ParseStatus_t Argument::Complete = 0;
	const Argument::ParseStatus_t Argument::Incomplete = -1;
	const Argument::ParseStatus_t Argument::OutOfRange = -2;
	const Argument::ParseStatus_t Argument::ParseError = -3;

	Argument::Argument(const std::string& call_name, const Mode_t& Mode, const std::string& help_text, const Req_t required, bool* was_defined) : ArgObject(help_text, Mode, required) {
		this->call_names = GetCallNames(call_name);
		if(was_defined == ARGPARSE_NULLPTR) {
			this->defined = new bool;
			this->responsible_for_defined = true;
			*(this->defined) = false;
		} else {
			this->responsible_for_defined = false;
			this->defined = was_defined;
		}
	}

	Argument::~Argument() {
		if(this->responsible_for_defined) {
			delete this->defined;
		}
	}

	std::vector<std::string> Argument::GetCallNames(const std::string& combined_names) {
		std::vector<std::string> answer;
		const size_t buffer_size = combined_names.size();
		char temp_buffer[buffer_size];
		strcpy(temp_buffer, combined_names.c_str());
		char* token = strtok(temp_buffer, "/");
		do {
			if(token == NULL) {
				break;
			}
			if(DebugLevel > 0) {
				MessageStandardPrint("Found name: (%s)\n", token);
			}
			answer.push_back(std::string(token));
			token = strtok(NULL, "/");
		} while (true);
		return answer;
	}

	std::string Argument::GetName(size_t i) {
		if(call_names.size() > i) {
			return call_names[i];
		} else {
			return "";
		}
	}

	void Argument::PrepareHelpText(std::stringstream& ss) {
		for(size_t i=0;i<call_names.size();++i) {
			ss << GetName(i) << " ";
			if(i < call_names.size()-1) {
				ss << "/ ";
			}
		}
		ss << ": ";
	}
	
	void Argument::AppendType(std::stringstream& ss) {
		ss << " Generic Type : ";
	}

	std::string Argument::GetHelpTextWithMessage(const std::string& message) {
		std::stringstream ss;
		PrepareHelpText(ss);
		ss << message;
		AppendType(ss);
		ss << GetHelp();
		return ss.str();
	}

	std::string Argument::GetHelpText() {
		return GetHelpTextWithMessage("Takes a generic argument : ");
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsChar(char& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		long temp_val = strtol(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as char.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as char.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a char. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a char. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > CHAR_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum char. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				SetMessage("The argument (%s) is greater than the maximum short. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				return Argument::OutOfRange;
			}
			if(temp_val < CHAR_MIN) {
				ArgParseMessageError("The argument (%s) is less than the minimum char. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				SetMessage("The argument (%s) is greater than the maximum char. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				return Argument::OutOfRange;
			}
			val = (char) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsUChar(unsigned char& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned char.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as unsigned char.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned char. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned char. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > UCHAR_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum unsigned char. Unsigned char range is: [ 0 , %lli ]\n", UCHAR_MAX);
				SetMessage("The argument (%s) is greater than the maximum unsigned char. Unsigned char range is: [ 0 , %lli ]\n", UCHAR_MAX);
				return Argument::OutOfRange;
			}
			val = (unsigned char) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsShort(short& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		long temp_val = strtol(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as short.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as short.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an short. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an short. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > SHRT_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				SetMessage("The argument (%s) is greater than the maximum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				return Argument::OutOfRange;
			}
			if(temp_val < SHRT_MIN) {
				ArgParseMessageError("The argument (%s) is less than the minimum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				SetMessage("The argument (%s) is greater than the maximum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				return Argument::OutOfRange;
			}
			val = (short) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsUShort(unsigned short& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned short.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as unsigned short.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned short. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned short. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > USHRT_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum unsigned short. Unsigned short range is: [ 0 , %lli ]\n", USHRT_MAX);
				SetMessage("The argument (%s) is greater than the maximum unsigned short. Unsigned short range is: [ 0 , %lli ]\n", USHRT_MAX);
				return Argument::OutOfRange;
			}
			val = (unsigned short) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsInt(int& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		long temp_val = strtol(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as integer.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as integer.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an integer. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an integer. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > INT_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				SetMessage("The argument (%s) is greater than the maximum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				return Argument::OutOfRange;
			}
			if(temp_val < INT_MIN) {
				ArgParseMessageError("The argument (%s) is less than the minimum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				SetMessage("The argument (%s) is greater than the maximum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				return Argument::OutOfRange;
			}
			val = (int) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsUInt(unsigned int& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned integer.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as unsigned integer.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned integer. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned integer. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > UINT_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum unsigned integer. Unsigned integer range is: [ 0 , %lli ]\n", UINT_MAX);
				SetMessage("The argument (%s) is greater than the maximum unsigned integer. Unsigned integer range is: [ 0 , %lli ]\n", UINT_MAX);
				return Argument::OutOfRange;
			}
			val = (unsigned int) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsLong(long& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		long temp_val = strtol(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as long.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as long.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an long. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an long. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > LONG_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				SetMessage("The argument (%s) is greater than the maximum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				return Argument::OutOfRange;
			}
			if(temp_val < LONG_MIN) {
				ArgParseMessageError("The argument (%s) is less than the minimum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				SetMessage("The argument (%s) is greater than the maximum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				return Argument::OutOfRange;
			}
			val = (long) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsULong(unsigned long& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned long.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as unsigned long.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned long. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned long. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > ULONG_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum unsigned long. Unsigned long range is: [ 0 , %lli ]\n", ULONG_MAX);
				SetMessage("The argument (%s) is greater than the maximum unsigned long. Unsigned long range is: [ 0 , %lli ]\n", ULONG_MAX);
				return Argument::OutOfRange;
			}
			val = (unsigned long) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsLongLong(long long& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		long long temp_val = strtoll(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as long long.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as long long.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an long long. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an long long. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > LLONG_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum long long. Long Long range is: [ %lli , %lli ]\n", LLONG_MIN, LLONG_MAX);
				SetMessage("The argument (%s) is greater than the maximum long long. Long Long range is: [ %lli , %lli ]\n", LLONG_MIN, LLONG_MAX);
				return Argument::OutOfRange;
			}
			if(temp_val < LLONG_MIN) {
				ArgParseMessageError("The argument (%s) is less than the minimum long long. Long Long range is: [ %lli , %lli ]\n", LLONG_MIN, LLONG_MAX);
				SetMessage("The argument (%s) is greater than the maximum long long. Long Long range is: [ %lli , %lli ]\n", LLONG_MIN, LLONG_MAX);
				return Argument::OutOfRange;
			}
			val = (long long) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsULongLong(unsigned long long& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		unsigned long long temp_val = strtoull(optarg_array, &p, 0);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned long long.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as unsigned long long.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned long long. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned long long. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > ULLONG_MAX) {
				ArgParseMessageError("The argument (%s) is greater than the maximum unsigned long long. Unsigned long long range is: [ 0 , %lli ]\n", ULLONG_MAX);
				SetMessage("The argument (%s) is greater than the maximum unsigned long long. Unsigned long long range is: [ 0 , %lli ]\n", ULLONG_MAX);
				return Argument::OutOfRange;
			}
			val = (unsigned long long) temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsFloat(float& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		float temp_val = strtof(optarg_array, &p);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as float.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as float.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a float. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a float. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The argument (%s) is infinite.\n");
			}
			//Check for nan
			if(std::isfinite(temp_val)) {
				ArgParseMessageWarning("The argument (%s) is nan.\n");
			}
			//Parsing completed successfully.
			val = temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsDouble(double& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		double temp_val = strtod(optarg_array, &p);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as double.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as double.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a double. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a double. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The argument (%s) is infinite.\n", optarg_array);
			}
			//Check for nan
			//Don't use -ffast-math which will screw this up.
			if(temp_val != temp_val) {
				ArgParseMessageWarning("The argument (%s) is nan.\n", optarg_array);
			}
			//Parsing completed successfully.
			val = temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsLongDouble(long double& val, const std::string& optarg) {
		const char* optarg_array = optarg.c_str();
		errno = 0;
		char* p;
		long double temp_val = strtold(optarg_array, &p);
		if (p == optarg_array) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as long double.\n", optarg_array);
			SetMessage("The argument (%s) could not be parsed as long double.\n", optarg_array);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a long double. The error was (%s)\n", optarg_array, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a long double. The error was (%s)\n", optarg_array, strerror(errno));
				return Argument::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The argument (%s) is infinite.\n");
			}
			//Check for nan
			if(std::isfinite(temp_val)) {
				ArgParseMessageWarning("The argument (%s) is nan.\n");
			}
			//Parsing completed successfully.
			val = temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg_array);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg_array);
			return Argument::Incomplete;
		}
	}

	bool Argument::DoesAnArgumentMatch(size_t& position, const std::string& arg) {
		size_t i=0;
		for(;i<call_names.size();++i) {
			if(DebugLevel > 1) {
				MessageStandardPrint("checking if call name (%s) matches.\n", call_names[i].c_str());
			}
			if(DebugLevel > 3) {
				MessageStandardPrint("position: %lu arg: (%s)\n", position, arg.c_str());
			}
			if(arg == call_names[i]) {
				break;
			}
		}
		if (i != call_names.size()) {
			position = i;
			return true;
		} else {
			return false;
		}
	}

	bool Argument::IsReady() {
		if (IsRequired()) {
			if(!WasDefined()) {
				ArgParseMessageError("The argument (%s) needs to be defined.\n", GetName().c_str());
				SetMessage("The argument (%s) needs to be defined.\n", GetName().c_str());
				return false;
			}
		}
		return true;
	}
}
