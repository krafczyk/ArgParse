/*
ArgParser - C++ Argument Parser reflecting the python module ArgParse.
Copyright (C) 2014-2017  Matthew Scott Krafczyk

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
	int a = 0;
	std::string output_dir = "";
	long r = 0;
	double s = 0;

	bool t = false;
	bool u = false;
	bool v = false;

	std::vector<std::string> strings;
	std::vector<int> ints;

	//ArgParse::DebugLevel = 10;

	ArgParse::ArgParser Parser("This parser demonstrates how to use ArgParse groups.");
	ArgParse::ArgGroup* NormalGroup = Parser.AddArgGroup("norm", "This is a normal group");
	NormalGroup->AddArgument("-a", "Test argument for a normal group", &a);
	NormalGroup->AddArgument("-o/--output-dir", "Test required argument", &output_dir, ArgParse::ArgObject::Required);
	ArgParse::ArgGroup* RequiredInclusiveGroup = Parser.AddInclusiveArgGroup("required-inclusive", "This is a required Inclusive group", ArgParse::ArgObject::None, ArgParse::ArgObject::Required);
	RequiredInclusiveGroup->AddArgument("-r", "Test argument", &r, ArgParse::ArgObject::Required);
	RequiredInclusiveGroup->AddArgument("-s", "Test argument", &s, ArgParse::ArgObject::Required);
	ArgParse::ArgGroup* RequiredExclusiveGroup = Parser.AddExclusiveArgGroup("required-exclusive", "This is a required Exclusive group", ArgParse::ArgObject::None, ArgParse::ArgObject::Required);
	RequiredExclusiveGroup->AddArgument("-t", "Test argument", &t, ArgParse::ArgObject::Required);
	RequiredExclusiveGroup->AddArgument("-u", "Test argument", &u, ArgParse::ArgObject::Required);
	RequiredExclusiveGroup->AddArgument("-v", "Test argument", &v, ArgParse::ArgObject::Required);
	ArgParse::ArgGroup* InclusiveMultipleGroup = Parser.AddInclusiveArgGroup("multiple-inclusive", "This is a multiple inclusive group", ArgParse::ArgObject::Multiple);
	InclusiveMultipleGroup->AddArgument("-i", "Test argument", &ints);
	InclusiveMultipleGroup->AddArgument("-str", "Test argument", &strings);
	
	if(Parser.ParseArgs(argc, argv) < 0) {
		fprintf(stderr, "There was a problem parsing the arguments!\n");
		return -1;
	}

	if(Parser.HelpPrinted()) {
		return 0;
	}

	printf("output-dir: %s\n", output_dir.c_str());
	printf("r: %li\n", r);
	printf("s: %f\n", s);

	if(t) {
		printf("t was defined!\n");
	}

	if(u) {
		printf("u was defined!\n");
	}

	if(v) {
		printf("v was defined!\n");
	}

	if(ints.size() != 0) {
		printf("ints:\n");
		for(size_t i=0; i<ints.size(); ++i) {
			printf("%i\n", ints[i]);
		}
	}

	if(strings.size() != 0) {
		printf("strings:\n");
		for(size_t i=0; i<strings.size(); ++i) {
			printf("%s\n", strings[i].c_str());
		}
	}

	if(argc > 1) {
		printf("Arguments are left over!\n");
		for(int arg_i = 1; arg_i < argc; ++arg_i) {
			printf("%s ", argv[arg_i]);
		}
		printf("\n");
	}
}
