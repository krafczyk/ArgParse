/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2016  Matthew Scott Krafczyk

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
		ArgParseMessagePrint("The Argument listing is in columns separated by colons ':'.\n");
		ArgParseMessagePrint("The columns give the following information.\n");
		ArgParseMessagePrint("1 - Names the argument must be refered by.\n");
		ArgParseMessagePrint("2 - What type of argument it takes or if it takes no argument.\n");
		ArgParseMessagePrint("3 - Whether the argument should be specified a single time (Scalar) Or can be specified multiple times (Vector)\n");
		ArgParseMessagePrint("4 - Help text for that argument.\n");
		ArgParseMessagePrint("--- Arguments ---\n");
		ArgParseMessagePrint("-h / -? / --help : Takes no argument : Vector : Print this help text.\n");
		for(size_t i=0;i<objects.size();++i) {
			ArgParseMessagePrint("%s\n", objects[i]->GetHelpText().c_str());
		}
		help_printed = true;
	}

	int ArgParser::ParseArgs(int& argc, char**& argv) {
		std::string command_line = ArgsToString(argc, argv);
		//Check that the options are configured.
		for(size_t i=0; i<objects.size();++i) {
			if(!objects[i]->IsConfigured()) {
				ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
				return -1;
			}
		}
		//We start at 1 because the zeroth argument is the program name.
		int arg_i=1;
		int obj_idx_accepting_multiple_args = -1;
		std::string multiple_args_arg = "";
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
					if(DebugLevel > 2) {
						MessageStandardPrint("Eating an argument.\n");
					}
					if(EatArgument(argc, argv, arg_i) < 0) {
						MessageStandardPrint("There was a problem eating an argument!\n");
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -1;
					}
					if(DebugLevel > 2) {
						MessageStandardPrint("Finished eating an argument.\n");
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
			int accepting_obj_idx = ObjectIdxAcceptingArgument(arg);
			if(accepting_obj_idx < 0) {
				if (obj_idx_accepting_multiple_args > 0) {
					if(DebugLevel > 5) {
						ArgParseMessageDebug("Arg (%s) isn't a known argument, but there is an argument (%s) which is taking multiple arguments. Passing this arg to that argument", argv[arg_i], multiple_args_arg.c_str());
					}

					ArgObject::Pass_t passed = objects[obj_idx_accepting_multiple_args]->PassArgument(multiple_args_arg, argv[arg_i], true);
					if(passed == ArgObject::Error) {
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -2;
					}
					if(passed == ArgObject::NotAccepted) {
						ArgParseMessageError("The argument did not accept what we passed it! this shouldn't happen!\n");
						SetMessage("The argument did not accept what we passed it! this shouldn't happen!\n");
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -3;
					}
				} else {
					ArgParseMessageError("The argument (%s) does not exist.\n", arg.c_str());
					SetMessage("The argument (%s) does not exist.\n", arg.c_str());
					ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
					return -2;
				}
			} else {
				//Reset the multiarg variables
				obj_idx_accepting_multiple_args = -1;
				multiple_args_arg = "";

				ArgObject::Accept_t accepted = objects[accepting_obj_idx]->AcceptsArgument(arg);
				if (accepted == ArgObject::WithoutArg) {
					if(DebugLevel > 5) {
						ArgParseMessageDebug("object %lu accepts the argument without an option\n", accepting_obj_idx);
					}
					if(DebugLevel > 0) {
						MessageStandardPrint("Doesn't need a value\n");
					}
					if (split_arg) {
						ArgParseMessageError("The argument (%s) doesn't take a value!\n", arg.c_str());
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -3;
					}
					if(DebugLevel > 1) {
						MessageStandardPrint("Setting Value\n");
					}
					ArgObject::Pass_t passed = objects[accepting_obj_idx]->PassArgument(arg, opt, false);
					if(passed == ArgObject::Error) {
						ArgParseMessageError("There was a problem passing the argument (%s) to (%s)\n", opt.c_str(), arg.c_str());
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -4;
					}
					if(passed == ArgObject::NotAccepted) {
						ArgParseMessageError("The argument did not accept what we passed it! this shouldn't happen!\n");
						SetMessage("The argument did not accept what we passed it! this shouldn't happen!\n");
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -5;
					}
					if(DebugLevel > 1) {
						MessageStandardPrint("Finished Setting Value\n");
					}
				} else if ((accepted == ArgObject::WithSingleArg)||(accepted == ArgObject::WithMultipleArg)) {
					if(DebugLevel > 5) {
						ArgParseMessageDebug("object %lu accepts the argument with an option\n", accepting_obj_idx);
					}
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
							ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
							return -1;
						}
						if(DebugLevel > 2) {
							MessageStandardPrint("Finished eating an argument.\n");
						}
						opt = std::string(argv[arg_i]);
					}
					if(DebugLevel > 1) {
						MessageStandardPrint("Setting Value (%s)\n", opt.c_str());
					}
					ArgObject::Pass_t passed = objects[accepting_obj_idx]->PassArgument(arg, opt, true);
					if(passed == ArgObject::Error) {
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -2;
					}
					if(passed == ArgObject::NotAccepted) {
						ArgParseMessageError("The argument did not accept what we passed it! this shouldn't happen!\n");
						SetMessage("The argument did not accept what we passed it! this shouldn't happen!\n");
						ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
						return -3;
					}
					if (accepted == ArgObject::WithMultipleArg) {
						obj_idx_accepting_multiple_args = accepting_obj_idx;
						multiple_args_arg = arg;
					}
					if(DebugLevel > 1) {
						MessageStandardPrint("Finished Setting Value\n");
					}
				} else {
					ArgParseMessageError("Something strange was returned from AcceptsArgument!\n");
					SetMessage("Something strange was returned from AcceptsArgument!\n");
					ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
					return -6;
				}
	
				if(DebugLevel > 2) {
					MessageStandardPrint("Eating an argument.\n");
				}
				if(EatArgument(argc, argv, arg_i) < 0) {
					ArgParseMessageError("There was a problem eating an argument!\n");
					SetMessage("There was a problem eating an argument!\n");
					ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
					return -2;
				}
				if(DebugLevel > 2) {
					MessageStandardPrint("Finished eating an argument.\n");
				}
			}
		}
		for(size_t i=0;i<objects.size();++i) {
			if(objects[i]->State() == ArgObject::NotReady) {
				ArgParseMessageError("One of the arguments wasn't ready!\n");
				SetMessage("One of the arguments wasn't ready!\n");
				ArgParseMessageError("There was a problem parsing the arguments. The command line was (%s)\n", command_line.c_str());
				return -3;
			}
		}
		return 0;
	}

	std::string ArgParser::ArgsToString(int& argc, char**& argv) {
		std::stringstream ss;
		for(int i=0; i<argc; ++i) {
			ss << argv[i];
			if(i < argc-1) {
				ss << " ";
			}
		}
		return ss.str();
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
			if(opt.size() == 0) {
				ArgParseMessageWarning("You passed an empty value to the argument (%s)! This could screw up the parsing of later arguments.\n", arg.c_str());
			}
			return true;
		}
	}


	int ArgParser::ObjectIdxAcceptingArgument(const std::string& arg __attribute__((unused))) const {
		for(size_t i=0;i<objects.size();++i) {
			if(objects[i]->AcceptsArgument(arg) != ArgObject::No) {
				return (int) i;
			}
		}
		return -1;
	}
}
