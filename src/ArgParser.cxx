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

#include "ArgParse/ArgParser.h"
#include "ArgParse/Message.h"

namespace ArgParse {
	ArgParser::ArgParser(const std::string& help_intro) {
		this->help_printed = false;
		this->help_intro = help_intro;
	}

	ArgParser::~ArgParser() {
		for(size_t i=0;i<responsible_options.size();++i) {
			delete responsible_options[i];
		}
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, bool* option, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, option, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::vector<bool>* options, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, options, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::string* option, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, option, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::vector<std::string>* options, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, options, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, int* option, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, option, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::vector<int>* options, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, options, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, unsigned int* option, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, option, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* options, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, options, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, double* option, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, option, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::vector<double>* options, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, options, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}
	
	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, long double* option, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, option, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
	}

	void ArgParser::AddOption(const std::string& call_name, const std::string& help_text, std::vector<long double>* options, const Option::Req_t required, bool* was_defined) {
		Option* the_option = new Option(call_name, help_text, options, required, was_defined);
		this->responsible_options.push_back(the_option);
		AddOption(the_option);
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
		help_printed = true;
	}

	int ArgParser::ParseArgs(int argc, char** argv) {
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
					} else {
						int status;
						if((status = options[i]->SetValue(0)) < 0) {
							ArgParseMessageError("There was a problem with toggling the option (%s)!\n", argv[arg_i]);
							return -2;
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
