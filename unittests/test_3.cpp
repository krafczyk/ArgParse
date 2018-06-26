#include <cstdio>
#include <string>
#include <vector>

#include "ArgParse/ArgParseStandalone.h"

int main(int argc, char** argv) {
	bool bool_val = false;
	std::string output_path = "";
	std::vector<int> vector_of_ints;

	ArgParse::ArgParser Parser("This parser demonstrates how to use ArgParse.");
	Parser.AddArgument("-o/--output-path", "Pass an output file path", &output_path, ArgParse::Argument::Required);
	Parser.AddArgument("b/bool-val", "Pass this flag to set a boolean value", &bool_val);
	Parser.AddArgument("-i/--int-vector", "Pass this flag multiple times to pass multiple ints", &vector_of_ints);
	
	if(Parser.ParseArgs(argc, argv) < 0) {
		fprintf(stderr, "There was a problem parsing the arguments!\n");
		return -1;
	}

	if(Parser.HelpPrinted()) {
		return 0;
	}

	printf("The output-path was : (%s)\n", output_path.c_str());
	if(bool_val) {
		printf("The bool-val was set.\n");
	} else {
		printf("The bool-val was not set.\n");
	}

	if(vector_of_ints.size() > 0) {
		printf("The passed integers were:\n");
		for(size_t i = 0;i < vector_of_ints.size();++i) {
			printf("%i\n", vector_of_ints[i]);
		}
	} else {
		printf("There were no passed intergers.\n");
	}

	if(argc > 1) {
		printf("Arguments are left over!\n");
		for(int arg_i = 1; arg_i < argc; ++arg_i) {
			printf("%s ", argv[arg_i]);
		}
		printf("\n");
	}
}
