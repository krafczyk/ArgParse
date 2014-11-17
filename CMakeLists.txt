#ArgParser - C++ Argument Parser reflecting the python module ArgParse.
#Copyright (C) 2014  Matthew Scott Krafczyk
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
#*/

project(ArgParse)

cmake_minimum_required(VERSION 2.8)

set(ArgParse_VERSION_MAJOR 0)
set(ArgParse_VERSION_MINOR 2)
set(ArgParse_VERSION_PATCH 0)
set(ArgParse_VERSION_STRING ${ArgParse_VERSION_MAJOR}.${ArgParse_VERSION_MINOR}.${ArgParse_VERSION_PATCH})

add_definitions("-std=c++11 -Wall -Wextra -Werror")
include_directories(inc)

add_library(ArgParse SHARED src/ArgParser.cxx src/Message.cxx src/Option.cxx)
add_library(ArgParseStatic STATIC src/ArgParser.cxx src/Message.cxx src/Option.cxx)

set_target_properties(ArgParse PROPERTIES VERSION ${ArgParse_VERSION_STRING})
set_target_properties(ArgParse PROPERTIES SOVERSION ${ArgParse_VERSION_MAJOR})
set_target_properties(ArgParseStatic PROPERTIES VERSION ${ArgParse_VERSION_STRING})
set_target_properties(ArgParseStatic PROPERTIES SOVERSION ${ArgParse_VERSION_MAJOR})
set_target_properties(ArgParseStatic PROPERTIES OUTPUT_NAME ArgParse)

install(TARGETS ArgParse ArgParseStatic DESTINATION lib)
install(DIRECTORY inc/ArgParse DESTINATION include FILES_MATCHING PATTERN "*.h")

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/ArgParse.pc.in"
	"${CMAKE_CURRENT_BINARY_DIR}/ArgParse.pc"
	IMMEDIATE @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ArgParse.pc DESTINATION lib/pkgconfig)

# uninstall target
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)

add_custom_target(uninstall
	COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
