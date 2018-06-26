#!/usr/bin/env python
# This program builds a standalone header for this library.

from shutil import copyfile
import re

include_directory = "inc"
source_directory = "src"

copyfile('/'.join([include_directory, "ArgParse", "ArgParse.h"]), "test")

include_re = re.compile(r'#include "ArgParse/(.*\.h)"')

def get_lines_from_file(path):
    with open(path, "r") as infile:
        return infile.readlines()

def write_lines_to_file(path, lines):
    with open(path, "w") as outfile:
        outfile.writelines(lines)

included_directives = []

output_file_path = "test"

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
                for new_line in include_lines:
                    lines.insert(i,new_line)
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


