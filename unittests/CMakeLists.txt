#ArgParser - C++ Argument Parser reflecting the python module ArgParse.
#Copyright (C) 2015  Matthew Scott Krafczyk
#
#This program is free software: you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 2 of the License, or
#(at your option) any later version.
#
#This program is distributed in the hope that it will be useful,
#WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with this program.  If not, see <http://www.gnu.org/licenses/>.

add_executable(test_1 test_1.cpp)
target_link_libraries(test_1 ArgParse)
add_executable(test_2 test_2.cpp)
target_link_libraries(test_2 ArgParse)

install(TARGETS test_1 test_2 DESTINATION bin)
