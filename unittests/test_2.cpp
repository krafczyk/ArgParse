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
	int a;
	std::string output_dir = "";
	long r;
	double s;

	bool t = false;
	bool u = false;
	bool v = false;

	ArgParse::ArgParser Parser("This parser demonstrates how to use ArgParse groups.");
	ArgParse::ArgGroup& NormalGroup = Parser.AddArgGroup("norm", "This is a normal group");
	NormalGroup.AddArgument("-a", "Test argument for a normal group", &a);
	NormalGroup.AddArgument("-o/--output-dir", "Test required argument", &output_dir, ArgParse::Argument::Required);
	ArgParse::ArgGroup& RequiredInclusiveGroup = Parser.AddArgGroup("required-inclusive", "This is a required Inclusive group", ArgParse::ArgObject::None, ArgParse::ArgObject::Required, ArgParse::ArgObject::Inclusive);
	RequiredInclusiveGroup.AddArgument("-r", "Test argument", &r, ArgParse::Argument::Required);
	RequiredInclusiveGroup.AddArgument("-s", "Test argument", &s, ArgParse::Argument::Required);
	ArgParse::ArgGroup& RequiredExclusiveGroup = Parser.AddArgGroup("required-exclusive", "This is a required Exclusive group", ArgParse::ArgObject::None, ArgParse::ArgObject::Required, ArgParse::ArgObject::Exclusive);
	RequiredExclusiveGroup.AddArgument("-t", "Test argument", &t, ArgParse::Argument::Required);
	RequiredExclusiveGroup.AddArgument("-u", "Test argument", &u, ArgParse::Argument::Required);
	RequiredExclusiveGroup.AddArgument("-v", "Test argument", &v, ArgParse::Argument::Required);
	
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

	if(argc > 1) {
		printf("Arguments are left over!\n");
		for(int arg_i = 1; arg_i < argc; ++arg_i) {
			printf("%s ", argv[arg_i]);
		}
		printf("\n");
	}
}
