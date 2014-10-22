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
#include <cstring>

#include "ArgParse/ArgParse.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	const Option::Type_t Option::Bool = 0;
	const Option::Type_t Option::Str = 1;
	const Option::Type_t Option::Int = 2;
	const Option::Type_t Option::Float = 3;

	const Option::Mode_t Option::Single = 0;
	const Option::Mode_t Option::Multiple = 1;

	const Option::Req_t Option::Required = true;
	const Option::Req_t Option::Optional = false;

	Option::Option(const std::string& call_name, const Type_t& Type, const Mode_t& Mode, const std::string& help_text, const Req_t required, void* options) {
		this->call_names = GetCallNames(call_name);
		this->type = Type;
		this->mode = Mode;
		this->help_text = help_text;
		this->value = options;
		this->required = required;
		this->defined = false;
	}

	Option::Option(const std::string& call_name, const std::string& help_text, bool* option, const Req_t required) : Option(call_name, Bool, Single, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<bool>* option, const Req_t required) : Option(call_name, Bool, Multiple, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::string* option, const Req_t required) : Option(call_name, Str, Single, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<std::string>* option, const Req_t required) : Option(call_name, Str, Multiple, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, int* option, const Req_t required) : Option(call_name, Int, Single, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<int>* option, const Req_t required) : Option(call_name, Int, Multiple, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, double* option, const Req_t required) : Option(call_name, Float, Single, help_text, required, (void*) option) {
	}

	Option::Option(const std::string& call_name, const std::string& help_text, std::vector<double>* option, const Req_t required) : Option(call_name, Float, Multiple, help_text, required, (void*) option) {
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
			answer.push_back(std::string(token));
			token = strtok(NULL, "/");
		} while (true);
		return answer;
	}

	bool Option::IsOption(const char* opt) {
		bool result = false;
		std::stringstream ss;
		for(size_t i=0; i<call_names.size();++i) {
			if(call_names[i].size() == 1) {
				ss.str("");
				ss << "-" << call_names[i];
				if(ss.str() == opt) {
					result = true;
					break;
				}
			}
			if(call_names[i].size() > 1) {
				ss.str("");
				ss << "--" << call_names[i];
				if(ss.str() == opt) {
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

	bool Option::IsArgumentInt(const char* optarg) {
		if( (strlen(optarg) == 0) || ((!isdigit(optarg[0])) && (optarg[0] != '-') && (optarg[0] != '+'))) {
			return false;
		}

		char* p;
		strtol(optarg, &p, 10);
		return (*p == 0);
	}

	bool Option::IsArgumentFloat(const char* optarg) {
		if( (strlen(optarg) == 0) || ((!isdigit(optarg[0])) && (optarg[0] != '-') && (optarg[0] != '+'))) {
			return false;
		}

		char* p;
		strtod(optarg, &p);
		return (*p == 0);
	}

	int Option::SetValue(const char* optarg) {
		if(type == Bool) {
			ArgParseMessageError("Cannot set a Value to a Bool option!\n");
			SetMessage("Cannot set a Value to a Bool option!\n");
			return -1;
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
			if(IsArgumentInt(optarg))  {
				if(mode == Single) {
					int* val = (int*) value;
					char* p;
					*val = strtol(optarg, &p, 10);
					defined = true;
					return 0;
				} else if (mode == Multiple) {
					std::vector<int>* vec_val = (std::vector<int>*) value;
					char* p;
					vec_val->push_back(strtol(optarg, &p, 10));
					defined = true;
					return 0;
				}
			} else {
				ArgParseMessageError("The argument passed is not an Integer!\n");
				SetMessage("The argument passed is not an Integer!\n");
				return -3;
			}
		} else if (type == Float) {
			if(IsArgumentFloat(optarg)) {
				if(mode == Single) {
					double* val = (double*) value;
					char* p;
					*val = strtod(optarg, &p);
					defined = true;
					return 0;
				} else if (mode == Multiple) {
					std::vector<double>* vec_val = (std::vector<double>*) value;
					char* p;
					vec_val->push_back(strtod(optarg, &p));
					defined = true;
					return 0;
				}
			} else {
				ArgParseMessageError("The argument passed is not a Float!\n");
				SetMessage("The argument passed is not a Float!\n");
				return -4;
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

	ArgParser::ArgParser(const std::string& help_intro) {
		this->help_intro = help_intro;
	}


	void ArgParser::AddOption(Option* option) {
		for(size_t i=0;i<option->GetNum();++i) {
			if((option->GetName(i) == "-h") || (option->GetName(i) == "-?") || (option->GetName(i) == "--help")) {
				ArgParseMessageWarning("The option %s will be ignored, as this is reserved by the help text.\n", option->GetName(i).c_str());
			}
			for(size_t j=0;j<options.size();++j) {
				for(size_t k=0;k<options[j]->GetNum();++k) {
					if(option->GetName(i) == options[j]->GetName(k)) {
						ArgParseMessageWarning("The option %s has already been passed, and will be ignored for an earlier option.\n", option->GetName(i).c_str());
					}
				}
			}
		}
		options.push_back(option);
	}


	void ArgParser::PrintHelp() {
		ArgParseMessagePrint("%s\n", help_intro.c_str());
		ArgParseMessagePrint("--- Options ---\n");
		ArgParseMessagePrint("-h / -? / --help : Takes no arguments : Print this help text.\n");
		for(size_t i=0;i<options.size();++i) {
			ArgParseMessagePrint("%s\n", options[i]->GetHelpText().c_str());
		}
	}

	int ArgParser::ParseArgs(int argc, char** argv) {
		int arg_i=1;
		while(arg_i<argc) {
			int I = -1;
			if(std::string(argv[arg_i]) == std::string("-h")) {
				PrintHelp();
				return 0;
			}
			if(std::string(argv[arg_i]) == std::string("--help")) {
				PrintHelp();
				return 0;
			}
			if(std::string(argv[arg_i]) == std::string("-?")) {
				PrintHelp();
				return 0;
			}
			for(size_t i=0;i<options.size();++i) {
				if(options[i]->IsOption(argv[arg_i])) {
					I = i;
					if(options[i]->NeedsArgument()) {
						++arg_i;
						int status;
						if((status = options[i]->SetValue(argv[arg_i]))<0) {
							ArgParseMessageError("There was a problem setting (%s) as option to (%s).\n", argv[arg_i], argv[arg_i-1]);
							SetMessage("There was a problem setting (%s) as option to (%s).\n", argv[arg_i], argv[arg_i-1]);
							return -1;
						}
					}
				}
			}
			if(I < 0) {
				ArgParseMessageError("The option (%s) does not exist.\n", argv[arg_i]);
				SetMessage("The option (%s) does not exist.\n", argv[arg_i]);
				return -2;
			}
			++arg_i;
		}
		for(size_t i=0;i<options.size();++i) {
			if(options[i]->IsRequired()) {
				if(!options[i]->WasDefined()) {
					ArgParseMessageError("The option (%s) needs to be defined.\n", options[i]->GetName().c_str());
					SetMessage("The option (%s) needs to be defined.\n", options[i]->GetName().c_str());
					return -3;
				}
			}
		}
		return 0;
	}
}
