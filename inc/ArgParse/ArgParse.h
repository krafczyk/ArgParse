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

#ifndef ARGPARSE_HDR
#define ARGPARSE_HDR

#include <vector>
#include <string>

#include "ArgParse/Option.h"

namespace ArgParse {
	class ArgParser {
		public:
			ArgParser(const std::string& help_intro);

			void AddOption(Option* option);

			void PrintHelp();

			int ParseArgs(int argc, char** argv) __attribute__((warn_unused_result));

		private:
			std::string help_intro;
			std::vector<Option*> options;
	};
}

#endif
