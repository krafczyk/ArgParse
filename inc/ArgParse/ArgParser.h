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

#ifndef ARGPARSE_ArgParser_HDR
#define ARGPARSE_ArgParser_HDR

#include <vector>
#include <string>

#include "ArgParse/Option.h"

namespace ArgParse {
	class ArgParser {
		public:
			ArgParser(const std::string& help_intro);
			~ArgParser();

			void AddOption(const std::string& call_name, const std::string& help_text, bool* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<bool>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::string* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<std::string>* options, const Option::Req_t requred = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, char* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<char>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, unsigned char* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, short* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<short>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, unsigned short* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, int* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<int>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, unsigned int* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, double* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<double>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, long double* option, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddOption(const std::string& call_name, const std::string& help_text, std::vector<long double>* options, const Option::Req_t required = Option::Optional, bool* was_defined = ARGPARSE_NULLPTR);

			void AddOption(Option* option);

			void PrintHelp();

			bool HelpPrinted() const {
				return help_printed;
			}

			int ParseArgs(int argc, char** argv) __attribute__((warn_unused_result));

		private:
			std::string help_intro;
			std::vector<Option*> options;
			std::vector<Option*> responsible_options;
			bool help_printed;
	};
}

#endif
