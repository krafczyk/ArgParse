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

#include <sstream>
#include <cerrno>
#include <climits>
#include <cmath>

#include "ArgParse/Argument.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	const Argument::Type_t Argument::Bool = 0;
	const Argument::Type_t Argument::Str = 1;
	const Argument::Type_t Argument::Char = 2;
	const Argument::Type_t Argument::UChar = 3;
	const Argument::Type_t Argument::Short = 4;
	const Argument::Type_t Argument::UShort = 5;
	const Argument::Type_t Argument::Int = 6;
	const Argument::Type_t Argument::UInt = 7;
	const Argument::Type_t Argument::Long = 8;
	const Argument::Type_t Argument::ULong = 9;
	const Argument::Type_t Argument::LongLong = 10;
	const Argument::Type_t Argument::ULongLong = 11;
	const Argument::Type_t Argument::Float = 12;
	const Argument::Type_t Argument::Double = 14;
	const Argument::Type_t Argument::LongDouble = 15;

	const Argument::Mode_t Argument::Single = 0;
	const Argument::Mode_t Argument::Multiple = 1;

	const Argument::Req_t Argument::Required = true;
	const Argument::Req_t Argument::Optional = false;

	const Argument::ParseStatus_t Argument::Complete = 0;
	const Argument::ParseStatus_t Argument::Incomplete = -1;
	const Argument::ParseStatus_t Argument::OutOfRange = -2;
	const Argument::ParseStatus_t Argument::ParseError = -3;

	Argument::Argument(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* arguments, bool* was_defined) {
		InitializeArgument(call_name, Type, Mode, help_text, required, arguments, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, bool* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Bool, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<bool>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Bool, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::string* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Str, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Str, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, char* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Char, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<char>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Char, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, UChar, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, UChar, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, short* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Short, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<short>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Short, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, UShort, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, UShort, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, int* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Int, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<int>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Int, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, UInt, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, UInt, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, long* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Long, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<long>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Long, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, ULong, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, ULong, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, long long* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, LongLong, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<long long>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, LongLong, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, ULongLong, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, ULongLong, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, float* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Float, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<float>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Float, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, double* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Double, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<double>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, Double, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, long double* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, LongDouble, Single, help_text, required, (void*) argument, was_defined);
	}

	Argument::Argument(const std::string& call_name, const std::string& help_text, std::vector<long double>* argument, const Req_t required, bool* was_defined) {
		InitializeArgument(call_name, LongDouble, Multiple, help_text, required, (void*) argument, was_defined);
	}

	Argument::~Argument() {
		if(this->responsible_for_defined) {
			delete this->defined;
		}
	}

	void Argument::InitializeArgument(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* arguments, bool* was_defined) {
		this->call_names = GetCallNames(call_name);
		this->type = Type;
		this->mode = Mode;
		this->help_text = help_text;
		this->value = arguments;
		this->required = required;
		if(was_defined == ARGPARSE_NULLPTR) {
			this->defined = new bool;
			this->responsible_for_defined = true;
			*(this->defined) = false;
		} else {
			this->responsible_for_defined = false;
			this->defined = was_defined;
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

	bool Argument::IsArgument(const char* opt) {
		if(DebugLevel > 1) {
			MessageStandardPrint("Testing the argument (%s)\n", opt);
		}
		bool result = false;
		std::stringstream ss;
		for(size_t i=0; i<call_names.size();++i) {
			if(DebugLevel > 1) {
				MessageStandardPrint("against call name (%s)\n", call_names[i].c_str());
			}
			if(call_names[i].size() == 1) {
				ss.str("");
				ss << "-" << call_names[i];
				if(DebugLevel > 2) {
					MessageStandardPrint("really against: (%s)\n", ss.str().c_str());
				}
				if(ss.str() == std::string(opt)) {
					result = true;
					break;
				}
			}
			if(call_names[i].size() > 1) {
				ss.str("");
				ss << "--" << call_names[i];
				if(DebugLevel > 2) {
					MessageStandardPrint("really against: (%s)\n", ss.str().c_str());
				}
				if(ss.str() == std::string(opt)) {
					result = true;
					break;
				}
			}
		}
		return result;
	}

	std::string Argument::GetName(size_t i) {
		std::stringstream ss;
		if(call_names.size() > i) {
			if(call_names[i].size() == 1) {
				ss << "-" << call_names[i];
				return ss.str();
			} else {
				ss << "--" << call_names[i];
				return ss.str();
			}
		} else {
			return "";
		}
	}

	std::string Argument::GetHelpText() {
		std::stringstream ss;
		for(size_t i=0;i<call_names.size();++i) {
			ss << GetName(i) << " ";
			if(i < call_names.size()-1) {
				ss << "/ ";
			}
		}
		ss << ": ";
		if(type == Bool) {
			ss << "Takes no argument : ";
		} else if (type == Str) {
			ss << "Takes a string : ";
		} else if (type == Char) {
			ss << "Takes a character : ";
		} else if (type == UChar) {
			ss << "Takes an unsigned character : ";
		} else if (type == Short) {
			ss << "Takes a short : ";
		} else if (type == UShort) {
			ss << "Takes an unsigned short : ";
		} else if (type == Int) {
			ss << "Takes an integer : ";
		} else if (type == UInt) {
			ss << "Takes an unsigned integer : ";
		} else if (type == Long) {
			ss << "Takes an long : ";
		} else if (type == ULong) {
			ss << "Takes an unsigned long : ";
		} else if (type == LongLong) {
			ss << "Takes an long long : ";
		} else if (type == ULongLong) {
			ss << "Takes an unsigned long long : ";
		} else if (type == Float) {
			ss << "Takes a float : ";
		} else if (type == Double) {
			ss << "Takes a double : ";
		} else if (type == LongDouble) {
			ss << "Takes a long double : ";
		}
		ss << help_text;
		return ss.str();
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsChar(char& val, const char* optarg) {
		errno = 0;
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as char.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as char.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a char. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a char. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsUChar(unsigned char& val, const char* optarg) {
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned char.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as unsigned char.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned char. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned char. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsShort(short& val, const char* optarg) {
		errno = 0;
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as short.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as short.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an short. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an short. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsUShort(unsigned short& val, const char* optarg) {
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned short.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as unsigned short.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned short. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned short. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsInt(int& val, const char* optarg) {
		errno = 0;
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as integer.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as integer.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an integer. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an integer. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsUInt(unsigned int& val, const char* optarg) {
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned integer.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as unsigned integer.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned integer. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned integer. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsLong(long& val, const char* optarg) {
		errno = 0;
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as long.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as long.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an long. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an long. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsULong(unsigned long& val, const char* optarg) {
		errno = 0;
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned long.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as unsigned long.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned long. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned long. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsLongLong(long long& val, const char* optarg) {
		errno = 0;
		char* p;
		long long temp_val = strtoll(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as long long.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as long long.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an long long. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an long long. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsULongLong(unsigned long long& val, const char* optarg) {
		errno = 0;
		char* p;
		unsigned long long temp_val = strtoull(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as unsigned long long.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as unsigned long long.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned long long. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned long long. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsFloat(float& val, const char* optarg) {
		errno = 0;
		char* p;
		float temp_val = strtof(optarg, &p);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as float.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as float.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a float. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a float. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsDouble(double& val, const char* optarg) {
		errno = 0;
		char* p;
		double temp_val = strtod(optarg, &p);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as double.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as double.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a double. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a double. The error was (%s)\n", optarg, strerror(errno));
				return Argument::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The argument (%s) is infinite.\n", optarg);
			}
			//Check for nan
			//Don't use -ffast-math which will screw this up.
			if(temp_val != temp_val) {
				ArgParseMessageWarning("The argument (%s) is nan.\n", optarg);
			}
			//Parsing completed successfully.
			val = temp_val;
			return Argument::Complete;
		} else {
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	Argument::ParseStatus_t Argument::ParseArgumentAsLongDouble(long double& val, const char* optarg) {
		errno = 0;
		char* p;
		long double temp_val = strtold(optarg, &p);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The argument (%s) could not be parsed as long double.\n", optarg);
			SetMessage("The argument (%s) could not be parsed as long double.\n", optarg);
			return Argument::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a long double. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a long double. The error was (%s)\n", optarg, strerror(errno));
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
			ArgParseMessageError("The whole argument (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole argument (%s) wasn't parsed!\n", optarg);
			return Argument::Incomplete;
		}
	}

	int Argument::SetValue(const char* optarg) {
		if(type == Bool) {
			if(optarg != 0) {
				ArgParseMessageWarning("Ignoring the passed argument (%s), since this is a boolean argument.\n");
			}
			if(mode == Single) {
				bool* val = (bool*) value;
				*val = true;
			} else if (mode == Multiple) {
				std::vector<bool>* vec_val = (std::vector<bool>*) value;
				vec_val->push_back(true);
				SetDefined(true);
			}
			return 0;
		} else if (type == Str) {
			if(mode == Single) {
				std::string* string = (std::string*) value;
				*string = std::string(optarg);
				SetDefined(true);
				return 0;
			} else if (mode == Multiple) {
				std::vector<std::string>* vec_string = (std::vector<std::string>*) value;
				vec_string->push_back(std::string(optarg));
				SetDefined(true);
				return 0;
			}
		} else if (type == Char) {
			char temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsChar(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((char*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<char>* vec_val = (std::vector<char>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == UChar) {
			unsigned char temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsUChar(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((unsigned char*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<unsigned char>* vec_val = (std::vector<unsigned char>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == Short) {
			short temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsShort(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((short*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<short>* vec_val = (std::vector<short>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == UShort) {
			unsigned short temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsUShort(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((unsigned short*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<unsigned short>* vec_val = (std::vector<unsigned short>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == Int) {
			int temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsInt(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((int*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<int>* vec_val = (std::vector<int>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == UInt) {
			unsigned int temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsUInt(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((unsigned int*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<unsigned int>* vec_val = (std::vector<unsigned int>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == Long) {
			long temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsLong(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((long*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<long>* vec_val = (std::vector<long>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == ULong) {
			unsigned long temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsULong(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((unsigned long*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<unsigned long>* vec_val = (std::vector<unsigned long>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == LongLong) {
			long long temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsLongLong(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((long long*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<long long>* vec_val = (std::vector<long long>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == ULongLong) {
			unsigned long long temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsULongLong(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((unsigned long long*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<unsigned long long>* vec_val = (std::vector<unsigned long long>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == Float) {
			float temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsFloat(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((float*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<float>* vec_val = (std::vector<float>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == Double) {
			double temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsDouble(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((double*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<double>* vec_val = (std::vector<double>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		} else if (type == LongDouble) {
			long double temp_val = 0;
			Argument::ParseStatus_t status;
			if((status = ParseArgumentAsLongDouble(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((long double*) value) = temp_val;
					SetDefined(true);
					return 0;
				} else if (mode == Multiple) {
					std::vector<long double>* vec_val = (std::vector<long double>*) value;
					vec_val->push_back(temp_val);
					SetDefined(true);
					return 0;
				}
			}
		}
		ArgParseMessageError("The argument is of unknown type!\n");
		SetMessage("The argument is of unknown type!\n");
		return -2;
	}

	bool Argument::NeedsArgument() {
		if(type != Bool) {
			return true;
		} else {
			return false;
		}
	}
}
