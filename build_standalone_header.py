#!/usr/bin/env python
# This program builds a standalone header for this library.

from shutil import copyfile
import re
import os
import sys

include_re = re.compile(r'#include "ArgParse/(.*\.h)"')

source_path = sys.argv[1]
binary_path = sys.argv[2]
output_file_path = "/".join([binary_path,"inc/ArgParse/ArgParseStandalone.h"])
include_directory = "/".join([source_path,"inc"])
source_directory = "/".join([source_path,"src"])



def get_lines_from_file(path):
    with open(path, "r") as infile:
        return infile.readlines()

def write_lines_to_file(path, lines):
    with open(path, "w") as outfile:
        outfile.writelines(lines)

copyfile('/'.join([binary_path, "inc", "ArgParse", "ArgParse.h"]), output_file_path)

# Append source files after include file.
source_file_list = [f for f in os.listdir(source_directory) if os.path.isfile('/'.join([source_directory,f]))]


for source_file in source_file_list:
    lines = get_lines_from_file(output_file_path)
    new_lines = lines+get_lines_from_file('/'.join([source_directory,source_file]))
    write_lines_to_file(output_file_path, new_lines)

included_directives = []

while True:
    # Reset replacement numbers
    num_replacements = 0
    # Read in lines
    lines = get_lines_from_file(output_file_path)
    i = 0
    while i < len(lines):
        match = include_re.search(lines[i])
        if match:
            header_name = match.group(1)

            # always remove the matched line
            del lines[i]
            if header_name not in included_directives:
                include_file_path = "/".join([include_directory,"ArgParse",header_name])
                include_lines = get_lines_from_file(include_file_path)
                # delete the include line
                j = 0
                while j < len(include_lines):
                    new_line = include_lines[len(include_lines)-1-j]
                    lines.insert(i,new_line)
                    j += 1
                num_replacements += 1
                included_directives.append(header_name)
                write_lines_to_file(output_file_path, lines)
                # break from the loop and start again.
                break
            #No need to advance the index, since we deleted the line we're currently on.

        else:
            # Advance index by one by default
            i += 1

    if num_replacements == 0:
        break

# Prepend license and a message

lines = get_lines_from_file(output_file_path)

lines.insert(0,"\n")
lines.insert(0,"#define ARGPARSE_STANDALONE_HDR\n")
lines.insert(0,"#ifndef ARGPARSE_STANDALONE_HDR\n")
lines.insert(0,"\n")
lines.insert(0,"// This file was created from individual ArgParse source objects\n")
lines.insert(0,"\n")

license_lines = get_lines_from_file("/".join([source_path, "LICENSE"]))
i = 0
while i < len(license_lines):
    lines.insert(0,"// "+license_lines[len(license_lines)-1-i])
    i += 1

lines.insert(len(lines),"#endif\n")

write_lines_to_file(output_file_path, lines)
