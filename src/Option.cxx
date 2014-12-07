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

#include "ArgParse/Option.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	const Option::Type_t Option::Bool = 0;
	const Option::Type_t Option::Str = 1;
	const Option::Type_t Option::Char = 2;
	const Option::Type_t Option::UChar = 3;
	const Option::Type_t Option::Short = 4;
	const Option::Type_t Option::UShort = 5;
	const Option::Type_t Option::Int = 6;
	const Option::Type_t Option::UInt = 7;
	const Option::Type_t Option::Long = 8;
	const Option::Type_t Option::ULong = 9;
	const Option::Type_t Option::Float = 10;
	const Option::Type_t Option::Double = 11;
	const Option::Type_t Option::LongDouble = 12;

	const Option::Mode_t Option::Single = 0;
	const Option::Mode_t Option::Multiple = 1;

	const Option::Req_t Option::Required = true;
	const Option::Req_t Option::Optional = false;

	const Option::ParseStatus_t Option::Complete = 0;
	const Option::ParseStatus_t Option::Incomplete = -1;
	const Option::ParseStatus_t Option::OutOfRange = -2;
	const Option::ParseStatus_t Option::ParseError = -3;

	Option::Option(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options, bool* was_defined) {
		InitializeOption(call_name, Type, Mode, help_text, required, options, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, bool* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Bool, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<bool>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Bool, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::string* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Str, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<std::string>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Str, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, char* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Char, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<char>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Char, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, unsigned char* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, UChar, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, UChar, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, short* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Short, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<short>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Short, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, unsigned short* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, UShort, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, UShort, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, int* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Int, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<int>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Int, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, unsigned int* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, UInt, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, UInt, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, long* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Long, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<long>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Long, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, unsigned long* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, ULong, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, ULong, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, float* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Float, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<float>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Float, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, double* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Double, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<double>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, Double, Multiple, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, long double* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, LongDouble, Single, help_text, required, (void*) option, was_defined);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<long double>* option, const Req_t required, bool* was_defined) {
		InitializeOption(call_name, LongDouble, Multiple, help_text, required, (void*) option, was_defined);
	}

	void Option::InitializeOption(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options, bool* was_defined) {
		this->call_names = GetCallNames(call_name);
		this->type = Type;
		this->mode = Mode;
		this->help_text = help_text;
		this->value = options;
		this->required = required;
		this->defined = was_defined;
	}

	std::vector<std::string> Option::GetCallNames(const std::string& combined_names) {
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

	bool Option::IsOption(const char* opt) {
		if(DebugLevel > 1) {
			MessageStandardPrint("Testing the option (%s)\n", opt);
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

	std::string Option::GetName(size_t i) {
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

	std::string Option::GetHelpText() {
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

	Option::ParseStatus_t Option::ParseArgumentAsChar(char& val, const char* optarg) {
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as char.\n", optarg);
			SetMessage("The option (%s) could not be parsed as char.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a char. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a char. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > CHAR_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum char. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				SetMessage("The option (%s) is greater than the maximum short. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				return Option::OutOfRange;
			}
			if(temp_val < CHAR_MIN) {
				ArgParseMessageError("The option (%s) is less than the minimum char. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				SetMessage("The option (%s) is greater than the maximum char. Char range is: [ %lli , %lli ]\n", CHAR_MIN, CHAR_MAX);
				return Option::OutOfRange;
			}
			val = (char) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsUChar(unsigned char& val, const char* optarg) {
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as unsigned char.\n", optarg);
			SetMessage("The option (%s) could not be parsed as unsigned char.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned char. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned char. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > UCHAR_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum unsigned char. Unsigned char range is: [ 0 , %lli ]\n", UCHAR_MAX);
				SetMessage("The option (%s) is greater than the maximum unsigned char. Unsigned char range is: [ 0 , %lli ]\n", UCHAR_MAX);
				return Option::OutOfRange;
			}
			val = (unsigned char) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsShort(short& val, const char* optarg) {
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as short.\n", optarg);
			SetMessage("The option (%s) could not be parsed as short.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an short. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an short. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > SHRT_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				SetMessage("The option (%s) is greater than the maximum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				return Option::OutOfRange;
			}
			if(temp_val < SHRT_MIN) {
				ArgParseMessageError("The option (%s) is less than the minimum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				SetMessage("The option (%s) is greater than the maximum short. Short range is: [ %lli , %lli ]\n", SHRT_MIN, SHRT_MAX);
				return Option::OutOfRange;
			}
			val = (short) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsUShort(unsigned short& val, const char* optarg) {
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as unsigned short.\n", optarg);
			SetMessage("The option (%s) could not be parsed as unsigned short.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned short. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned short. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > USHRT_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum unsigned short. Unsigned short range is: [ 0 , %lli ]\n", USHRT_MAX);
				SetMessage("The option (%s) is greater than the maximum unsigned short. Unsigned short range is: [ 0 , %lli ]\n", USHRT_MAX);
				return Option::OutOfRange;
			}
			val = (unsigned short) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsInt(int& val, const char* optarg) {
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as integer.\n", optarg);
			SetMessage("The option (%s) could not be parsed as integer.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an integer. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an integer. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > INT_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				SetMessage("The option (%s) is greater than the maximum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				return Option::OutOfRange;
			}
			if(temp_val < INT_MIN) {
				ArgParseMessageError("The option (%s) is less than the minimum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				SetMessage("The option (%s) is greater than the maximum integer. Integer range is: [ %lli , %lli ]\n", INT_MIN, INT_MAX);
				return Option::OutOfRange;
			}
			val = (int) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsUInt(unsigned int& val, const char* optarg) {
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as unsigned integer.\n", optarg);
			SetMessage("The option (%s) could not be parsed as unsigned integer.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned integer. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned integer. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > UINT_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum unsigned integer. Unsigned integer range is: [ 0 , %lli ]\n", UINT_MAX);
				SetMessage("The option (%s) is greater than the maximum unsigned integer. Unsigned integer range is: [ 0 , %lli ]\n", UINT_MAX);
				return Option::OutOfRange;
			}
			val = (unsigned int) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsLong(long& val, const char* optarg) {
		char* p;
		long temp_val = strtol(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as long.\n", optarg);
			SetMessage("The option (%s) could not be parsed as long.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an long. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an long. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > LONG_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				SetMessage("The option (%s) is greater than the maximum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				return Option::OutOfRange;
			}
			if(temp_val < LONG_MIN) {
				ArgParseMessageError("The option (%s) is less than the minimum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				SetMessage("The option (%s) is greater than the maximum long. Long range is: [ %lli , %lli ]\n", LONG_MIN, LONG_MAX);
				return Option::OutOfRange;
			}
			val = (long) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsULong(unsigned long& val, const char* optarg) {
		char* p;
		unsigned long temp_val = strtoul(optarg, &p, 0);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as unsigned long.\n", optarg);
			SetMessage("The option (%s) could not be parsed as unsigned long.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as an unsigned long. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as an unsigned long. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > ULONG_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum unsigned long. Unsigned long range is: [ 0 , %lli ]\n", ULONG_MAX);
				SetMessage("The option (%s) is greater than the maximum unsigned long. Unsigned long range is: [ 0 , %lli ]\n", ULONG_MAX);
				return Option::OutOfRange;
			}
			val = (unsigned long) temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsFloat(float& val, const char* optarg) {
		char* p;
		float temp_val = strtof(optarg, &p);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as float.\n", optarg);
			SetMessage("The option (%s) could not be parsed as float.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a float. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a float. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The option (%s) is infinite.\n");
			}
			//Check for nan
			if(std::isfinite(temp_val)) {
				ArgParseMessageWarning("The option (%s) is nan.\n");
			}
			//Parsing completed successfully.
			val = temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsDouble(double& val, const char* optarg) {
		char* p;
		double temp_val = strtod(optarg, &p);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as double.\n", optarg);
			SetMessage("The option (%s) could not be parsed as double.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a double. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a double. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The option (%s) is infinite.\n");
			}
			//Check for nan
			if(std::isfinite(temp_val)) {
				ArgParseMessageWarning("The option (%s) is nan.\n");
			}
			//Parsing completed successfully.
			val = temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	Option::ParseStatus_t Option::ParseArgumentAsLongDouble(long double& val, const char* optarg) {
		char* p;
		long double temp_val = strtold(optarg, &p);
		if (p == optarg) {
			//No conversion performed
			ArgParseMessageError("The option (%s) could not be parsed as long double.\n", optarg);
			SetMessage("The option (%s) could not be parsed as long double.\n", optarg);
			return Option::ParseError;
		} else if (*p == '\0') {
			//Check whether the value is out of range
			if(errno != 0) {
				ArgParseMessageError("There was a problem parsing the argument (%s) as a long double. The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s) as a long double. The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Check for inf
			if(std::isinf(temp_val)) {
				ArgParseMessageWarning("The option (%s) is infinite.\n");
			}
			//Check for nan
			if(std::isfinite(temp_val)) {
				ArgParseMessageWarning("The option (%s) is nan.\n");
			}
			//Parsing completed successfully.
			val = temp_val;
			return Option::Complete;
		} else {
			ArgParseMessageError("The whole option (%s) wasn't parsed!\n", optarg);
			SetMessage("The whole option (%s) wasn't parsed!\n", optarg);
			return Option::Incomplete;
		}
	}

	int Option::SetValue(const char* optarg) {
		if(type == Bool) {
			if(optarg != 0) {
				ArgParseMessageWarning("Ignoring the passed option (%s), since this is a boolean option.\n");
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
		} else if (type == Float) {
			float temp_val = 0;
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
			Option::ParseStatus_t status;
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
		ArgParseMessageError("The option is of unknown type!\n");
		SetMessage("The option is of unknown type!\n");
		return -2;
	}

	bool Option::NeedsArgument() {
		if(type != Bool) {
			return true;
		} else {
			return false;
		}
	}
}
