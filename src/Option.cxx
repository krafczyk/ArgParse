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
	const Option::Type_t Option::Int = 2;
	const Option::Type_t Option::Float = 3;
	const Option::Type_t Option::Double = 4;

	const Option::Mode_t Option::Single = 0;
	const Option::Mode_t Option::Multiple = 1;

	const Option::Req_t Option::Required = true;
	const Option::Req_t Option::Optional = false;

	const Option::ParseStatus_t Option::Complete = 0;
	const Option::ParseStatus_t Option::Incomplete = -1;
	const Option::ParseStatus_t Option::OutOfRange = -2;
	const Option::ParseStatus_t Option::ParseError = -3;

	Option::Option(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options) {
		InitializeOption(call_name, Type, Mode, help_text, required, options);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, bool* option, const Req_t required) {
		InitializeOption(call_name, Bool, Single, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<bool>* option, const Req_t required) {
		InitializeOption(call_name, Bool, Multiple, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::string* option, const Req_t required) {
		InitializeOption(call_name, Str, Single, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<std::string>* option, const Req_t required) {
		InitializeOption(call_name, Str, Multiple, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, int* option, const Req_t required) {
		InitializeOption(call_name, Int, Single, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<int>* option, const Req_t required) {
		InitializeOption(call_name, Int, Multiple, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, double* option, const Req_t required) {
		InitializeOption(call_name, Float, Single, help_text, required, (void*) option);
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<double>* option, const Req_t required) {
		InitializeOption(call_name, Float, Multiple, help_text, required, (void*) option);
	}

	void Option::InitializeOption(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options) {
		this->call_names = GetCallNames(call_name);
		this->type = Type;
		this->mode = Mode;
		this->help_text = help_text;
		this->value = options;
		this->required = required;
		this->defined = false;
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
		} else if (type == Int) {
			ss << "Takes an integer : ";
		} else if (type == Float) {
			ss << "Takes a float : ";
		}
		ss << help_text;
		return ss.str();
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
				ArgParseMessageError("There was a problem parsing the argument (%s). The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s). The error was (%s)\n", optarg, strerror(errno));
				return Option::ParseError;
			}
			//Parsing completed successfully.
			//Now check range.
			if(temp_val > INT_MAX) {
				ArgParseMessageError("The option (%s) is greater than the maximum integer. Integer range is: [ %lli, %lli ]\n", INT_MIN, INT_MAX);
				SetMessage("The option (%s) is greater than the maximum integer. Integer range is: [ %lli, %lli ]\n", INT_MIN, INT_MAX);
				return Option::OutOfRange;
			}
			if(temp_val < INT_MIN) {
				ArgParseMessageError("The option (%s) is less than the minimum integer. Integer range is: [ %lli, %lli ]\n", INT_MIN, INT_MAX);
				SetMessage("The option (%s) is greater than the maximum integer. Integer range is: [ %lli, %lli ]\n", INT_MIN, INT_MAX);
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
				ArgParseMessageError("There was a problem parsing the argument (%s). The error was (%s)\n", optarg, strerror(errno));
				SetMessage("There was a problem parsing the argument (%s). The error was (%s)\n", optarg, strerror(errno));
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
				defined = true;
			}
			return 0;
		} else if (type == Str) {
			if(mode == Single) {
				std::string* string = (std::string*) value;
				*string = std::string(optarg);
				defined = true;
				return 0;
			} else if (mode == Multiple) {
				std::vector<std::string>* vec_string = (std::vector<std::string>*) value;
				vec_string->push_back(std::string(optarg));
				defined = true;
				return 0;
			}
		} else if (type == Int) {
			int temp_val = 0;
			Option::ParseStatus_t status;
			if((status = ParseArgumentAsInt(temp_val, optarg)) < 0)  {
				return -3;
			} else {
				if(mode == Single) {
					*((int*) value) = temp_val;
					defined = true;
					return 0;
				} else if (mode == Multiple) {
					std::vector<int>* vec_val = (std::vector<int>*) value;
					vec_val->push_back(temp_val);
					defined = true;
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
					defined = true;
					return 0;
				} else if (mode == Multiple) {
					std::vector<float>* vec_val = (std::vector<float>*) value;
					vec_val->push_back(temp_val);
					defined = true;
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
