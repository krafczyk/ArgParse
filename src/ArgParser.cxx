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
#include <cstring>

#include "ArgParse/ArgParser.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	ArgParser::ArgParser(const std::string& help_intro) {
		this->help_printed = false;
		this->help_intro = help_intro;
	}

	ArgParser::~ArgParser() {
		for(size_t i=0;i<responsible_arguments.size();++i) {
			delete responsible_arguments[i];
		}
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}
	
	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		this->responsible_arguments.push_back(the_argument);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(Argument* argument) {
		for(size_t i=0;i<argument->GetNum();++i) {
			if((argument->GetName(i) == "-h") || (argument->GetName(i) == "-?") || (argument->GetName(i) == "--help")) {
				ArgParseMessageWarning("The argument %s will be ignored, as this is reserved by the help text.\n", argument->GetName(i).c_str());
			}
			for(size_t j=0;j<arguments.size();++j) {
				for(size_t k=0;k<arguments[j]->GetNum();++k) {
					if(argument->GetName(i) == arguments[j]->GetName(k)) {
						ArgParseMessageWarning("The argument %s has already been passed, and will be ignored for an earlier argument.\n", argument->GetName(i).c_str());
					}
				}
			}
		}
		arguments.push_back(argument);
	}


	void ArgParser::PrintHelp() {
		ArgParseMessagePrint("%s\n", help_intro.c_str());
		ArgParseMessagePrint("--- Arguments ---\n");
		ArgParseMessagePrint("-h / -? / --help : Takes no arguments : Print this help text.\n");
		for(size_t i=0;i<arguments.size();++i) {
			ArgParseMessagePrint("%s\n", arguments[i]->GetHelpText().c_str());
		}
		help_printed = true;
	}

	int ArgParser::ParseArgs(int& argc, char**& argv) {
		int arg_i=1;
		while(arg_i<argc) {
			if(DebugLevel > 0) {
				MessageStandardPrint("Argument is: (%s)\n", argv[arg_i]);
			}
			int I = -1;
			if(std::string(argv[arg_i]) == std::string("-h")) {
				if(DebugLevel > 0) {
					MessageStandardPrint("Help discovered!\n", argv[arg_i]);
				}
				PrintHelp();
				return 0;
			}
			if(std::string(argv[arg_i]) == std::string("--help")) {
				if(DebugLevel > 0) {
					MessageStandardPrint("Help discovered!\n", argv[arg_i]);
				}

				PrintHelp();
				return 0;
			}
			if(std::string(argv[arg_i]) == std::string("-?")) {
				if(DebugLevel > 0) {
					MessageStandardPrint("Help discovered!\n", argv[arg_i]);
				}

				PrintHelp();
				return 0;
			}
			for(size_t i=0;i<arguments.size();++i) {
				if(arguments[i]->IsArgument(argv[arg_i])) {
					I = i;
					if(arguments[i]->NeedsArgument()) {
						++arg_i;
						int status;
						if((status = arguments[i]->SetValue(argv[arg_i]))<0) {
							ArgParseMessageError("There was a problem setting (%s) as argument to (%s).\n", argv[arg_i], argv[arg_i-1]);
							SetMessage("There was a problem setting (%s) as argument to (%s).\n", argv[arg_i], argv[arg_i-1]);
							return -1;
						}
					} else {
						int status;
						if((status = arguments[i]->SetValue(0)) < 0) {
							ArgParseMessageError("There was a problem with toggling the argument (%s)!\n", argv[arg_i]);
							return -2;
						}
					}
				}
			}
			if(I < 0) {
				ArgParseMessageError("The argument (%s) does not exist.\n", argv[arg_i]);
				SetMessage("The argument (%s) does not exist.\n", argv[arg_i]);
				return -2;
			}
			++arg_i;
		}
		for(size_t i=0;i<arguments.size();++i) {
			if(arguments[i]->IsRequired()) {
				if(!arguments[i]->WasDefined()) {
					ArgParseMessageError("The argument (%s) needs to be defined.\n", arguments[i]->GetName().c_str());
					SetMessage("The argument (%s) needs to be defined.\n", arguments[i]->GetName().c_str());
					return -3;
				}
			}
		}
		return 0;
	}
}
