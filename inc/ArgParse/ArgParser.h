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

#ifndef ARGPARSE_ArgParser_HDR
#define ARGPARSE_ArgParser_HDR

#include <vector>
#include <string>

#include "ArgParse/ArgObjContainer.h"

namespace ArgParse {
	class ArgParser : public ArgObjContainer {
		public:
			ArgParser(const std::string& help_intro);
			~ArgParser();

			void PrintHelp();

			bool HelpPrinted() const {
				return help_printed;
			}

			int ParseArgs(int& argc, char**& argv) __attribute__((warn_unused_result));

			static int EatArgument(int& argc, char**& argv, const int i = 1) __attribute__((warn_unused_result));
			static bool SplitArg(std::string& arg, std::string& opt, const std::string argument);

		private:
			std::string help_intro;
			bool help_printed;
	};
}

#endif
