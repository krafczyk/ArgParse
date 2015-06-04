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

#include "ArgParse/Argument.h"

namespace ArgParse {
	class ArgParser {
		public:
			ArgParser(const std::string& help_intro);
			~ArgParser();

			void AddArgument(const std::string& call_name, const std::string& help_text, bool* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<bool>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::string* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<std::string>* arguments, const Argument::Req_t requred = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, char* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<char>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned char* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned char>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, short* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<short>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned short* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned short>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, int* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<int>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned int* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned int>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, unsigned long long* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<unsigned long long>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, float* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<float>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, double* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<double>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, long double* argument, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);
			void AddArgument(const std::string& call_name, const std::string& help_text, std::vector<long double>* arguments, const Argument::Req_t required = Argument::Optional, bool* was_defined = ARGPARSE_NULLPTR);

			void AddArgument(Argument* argument);

			void PrintHelp();

			bool HelpPrinted() const {
				return help_printed;
			}

			int ParseArgs(int& argc, char**& argv) __attribute__((warn_unused_result));

		private:
			std::string help_intro;
			std::vector<Argument*> arguments;
			std::vector<Argument*> responsible_arguments;
			bool help_printed;
	};
}

#endif
