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

			std::string ArgsToString(int& argc, char**& argv);

			static int EatArgument(int& argc, char**& argv, const int i = 1) __attribute__((warn_unused_result));
			static bool SplitArg(std::string& arg, std::string& opt, const std::string argument);
			int ObjectIdxAcceptingArgument(const std::string& arg __attribute__((unused))) const __attribute__((warn_unused_result));

		private:
			std::string help_intro;
			bool help_printed;
	};
}

#endif
