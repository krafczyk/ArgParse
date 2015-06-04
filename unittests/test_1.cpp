/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2015  Matthew Scott Krafczyk

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

#include <cstdio>
#include <string>
#include <vector>

#include "ArgParse/ArgParse.h"

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
}