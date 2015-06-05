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
	ArgParser::ArgParser(const std::string& help_intro) : ArgObjContainer() {
		this->help_printed = false;
		this->help_intro = help_intro;
	}

	ArgParser::~ArgParser() {
	}

	void ArgParser::PrintHelp() {
		ArgParseMessagePrint("%s\n", help_intro.c_str());
		ArgParseMessagePrint("--- Arguments ---\n");
		ArgParseMessagePrint("-h / -? / --help : Takes no arguments : Print this help text.\n");
		for(size_t i=0;i<objects.size();++i) {
			ArgParseMessagePrint("%s\n", objects[i]->GetHelpText().c_str());
		}
		help_printed = true;
	}

	int ArgParser::ParseArgs(int& argc, char**& argv) {
		//Check that the options are configured.
		for(size_t i=0; i<objects.size();++i) {
			if(!objects[i]->IsConfigured()) {
				return -1;
			}
		}
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
			for(size_t i=0;i<objects.size();++i) {
				ArgObject::Accept_t accepted = objects[i]->AcceptsArgument(arg);
				if (accepted != ArgObject::No) {
					I = i;
					if(accepted == ArgObject::WithArg) {
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
						ArgObject::Pass_t passed = objects[i]->PassArgument(arg, opt, true);
						if(passed == ArgObject::Error) {
							return -2;
						}
						if(passed == ArgObject::NotAccepted) {
							ArgParseMessageError("The argument did not accept what we passed it! this shouldn't happen!\n");
							SetMessage("The argument did not accept what we passed it! this shouldn't happen!\n");
							return -3;
						}
						if(DebugLevel > 1) {
							MessageStandardPrint("Finished Setting Value\n");
						}
					} else if (accepted == ArgObject::WithoutArg) {
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
						ArgObject::Pass_t passed = objects[i]->PassArgument(arg, opt, false);
						if(passed == ArgObject::Error) {
							return -4;
						}
						if(passed == ArgObject::NotAccepted) {
							ArgParseMessageError("The argument did not accept what we passed it! this shouldn't happen!\n");
							SetMessage("The argument did not accept what we passed it! this shouldn't happen!\n");
							return -5;
						}
						if(DebugLevel > 1) {
							MessageStandardPrint("Finished Setting Value\n");
						}
					} else {
						ArgParseMessageError("Something strange was returned from AcceptsArgument!\n");
						SetMessage("Something strange was returned from AcceptsArgument!\n");
						return -6;
					}
				}
			}
			if(I < 0) {
				ArgParseMessageError("The argument (%s) does not exist.\n", arg.c_str());
				SetMessage("The argument (%s) does not exist.\n", arg.c_str());
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
		for(size_t i=0;i<objects.size();++i) {
			if(!objects[i]->IsReady()) {
				return -3;
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
