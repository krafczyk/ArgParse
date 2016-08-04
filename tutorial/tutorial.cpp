#include <cstdio>

#include "ArgParse/ArgParse.h"

int main(int argc, char** argv) {

	// Declare variables which will hold passed arguments
	std::string input_filepath = "default_filepath";
	int test_num = 0;
	unsigned long long test_num_2 = 0;
	bool test_num_2_defined = false;

	// Declare argument parser
	ArgParse::ArgParser Parser("A test program to show how the ArgParse library works");

	// Create arguments
	Parser.AddArgument("-i/--input-file", "An input filepath", &input_filepath);
	Parser.AddArgument("-n", "A required number", &test_num, ArgParse::Argument::Required);
	Parser.AddArgument("--number-two", "Another number", &test_num_2, ArgParse::Argument::Optional, &test_num_2_defined);

	if(Parser.ParseArgs(argc, argv) < 0) {
		// You must check that the arguments were parsed correctly!
		// If they were not, you have the responsibility to
		// end your program accordingly.
		printf("There was a problem parsing the arguments!\n");
		return -1;
	}

	if(Parser.HelpPrinted()) {
		// You must check whether the user asked for the help text
		// You can continue if you want, but this is often a good
		// place to stop if the user only asked for help text.
		return 0;
	}

	//Use passed arguments
	printf("input file was (%s)\n", input_filepath.c_str());
	printf("required number was (%i)\n", test_num);
	if(test_num_2_defined) {
		printf("another number was (%llu)\n", test_num_2);
	}

	return 0;
}
