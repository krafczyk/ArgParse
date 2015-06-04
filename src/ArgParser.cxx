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
		for(size_t i=0;i<arguments.size();++i) {
			delete arguments[i];
		}
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
		AddArgument(the_argument);
	}
	
	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, argument, required, was_defined);
		AddArgument(the_argument);
	}

	void ArgParser::AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Argument::Req_t required, bool* was_defined) {
		Argument* the_argument = new Argument(call_name, help_text, arguments, required, was_defined);
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
			std::string arg;
			std::string opt;
			bool split_arg = SplitArg(arg, opt, argv[arg_i]);
			if(arg == std::string("--")) {
				if(!split_arg) {
					//We need to eat this variable and then quit.
					if(EatArgument(argc, argv, arg_i) < 0) {
						MessageStandardPrint("There was a problem eating an argument!\n");
						return -1;
					}
					break;
				}
			}
			if(arg == std::string("-h")) {
				if(DebugLevel > 0) {
					MessageStandardPrint("Help discovered!\n", argv[arg_i]);
				}
				PrintHelp();
				return 0;
			}
			if(arg == std::string("--help")) {
				if(DebugLevel > 0) {
					MessageStandardPrint("Help discovered!\n", argv[arg_i]);
				}

				PrintHelp();
				return 0;
			}
			if(arg == std::string("-?")) {
				if(DebugLevel > 0) {
					MessageStandardPrint("Help discovered!\n", argv[arg_i]);
				}

				PrintHelp();
				return 0;
			}
			int I = -1;
			for(size_t i=0;i<arguments.size();++i) {
				if(arguments[i]->IsArgument(arg)) {
					I = i;
					if(arguments[i]->NeedsArgument()) {
						if(DebugLevel > 0) {
							MessageStandardPrint("Needs a value\n");
						}
						if(!split_arg) {
							if(DebugLevel > 2) {
								MessageStandardPrint("Eating an argument.\n");
							}
							if(EatArgument(argc, argv, arg_i) < 0) {
								ArgParseMessageError("There was a problem eating an argument!\n");
								SetMessage("There was a problem eating an argument!\n");
								return -1;
							}
							if(DebugLevel > 2) {
								MessageStandardPrint("Finished eating an argument.\n");
							}
							opt = std::string(argv[arg_i]);
						}
						if(DebugLevel > 1) {
							MessageStandardPrint("Setting Value\n");
						}
						int status;
						if((status = arguments[i]->SetValue(opt))<0) {
							ArgParseMessageError("There was a problem setting (%s) as argument to (%s).\n", argv[arg_i], argv[arg_i-1]);
							SetMessage("There was a problem setting (%s) as argument to (%s).\n", argv[arg_i], argv[arg_i-1]);
							return -2;
						}
						if(DebugLevel > 1) {
							MessageStandardPrint("Finished Setting Value\n");
						}
					} else {
						if(DebugLevel > 0) {
							MessageStandardPrint("Doesn't need a value\n");
						}
						if (split_arg) {
							ArgParseMessageError("The argument (%s) doesn't take a value!\n", arg.c_str());
							return -3;
						}
						if(DebugLevel > 1) {
							MessageStandardPrint("Setting Value\n");
						}
						int status;
						if((status = arguments[i]->SetValue("")) < 0) {
							ArgParseMessageError("There was a problem with toggling the argument (%s)!\n", argv[arg_i]);
							return -4;
						}
						if(DebugLevel > 1) {
							MessageStandardPrint("Finished Setting Value\n");
						}
					}
				}
			}
			if(I < 0) {
				ArgParseMessageError("The argument (%s) does not exist.\n", argv[arg_i]);
				SetMessage("The argument (%s) does not exist.\n", argv[arg_i]);
				return -2;
			}
			if(DebugLevel > 2) {
				MessageStandardPrint("Eating an argument.\n");
			}
			if(EatArgument(argc, argv, arg_i) < 0) {
				ArgParseMessageError("There was a problem eating an argument!\n");
				SetMessage("There was a problem eating an argument!\n");
				return -2;
			}
			if(DebugLevel > 2) {
				MessageStandardPrint("Finished eating an argument.\n");
			}
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

	int ArgParser::EatArgument(int& argc, char**& argv, const int i) {
		if (i >= argc) {
			return -1;
		}
		//shift arguments
		argc--;
		int j = i;
		while (j < argc) {
			argv[j] = argv[j+1];
			j++;
		}
		return 0;
	}

	bool ArgParser::SplitArg(std::string& arg, std::string& opt, const std::string argument) {
		const int normal = 0;
		const int quoted = 0;
		const int escaped = 0;
		int mode = normal;

		bool found_equals = false;
		size_t equals_position = 0;
		char quote_type;
		size_t i = 0;
		while (i < argument.size()) {
			if (mode == normal) {
				if (argument[i] == '=') {
					found_equals = true;
					equals_position = i;
					break;
				}
				if ((argument[i] == '\'')||(argument[i] == '"')) {
					mode = quoted;
					quote_type = argument[i];
				}
			} else if (mode == quoted) {
				if (argument[i] == quote_type) {
					mode = normal;
				}
				if (argument[i] == '\\') {
					mode = escaped;
				}
			} else if (mode == escaped) {
			}
			++i;
		}

		if (!found_equals) {
			arg = argument;
			return false;
		} else {
			arg = argument.substr(0, equals_position);
			opt = argument.substr(equals_position+1, argument.size()-equals_position-1);
			return true;
		}
	}
}
