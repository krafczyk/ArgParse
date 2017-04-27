#ArgParser - C++ Argument Parser reflecting the python module ArgParse.
#Copyright (C) 2014-2017  Matthew Scott Krafczyk
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

cmake_minimum_required(VERSION 2.8)

set(CC "$ENV{CC}")
if(CC)
	set(CMAKE_C_COMPILER CACHE STRING ${CC})
endif()

set(CXX "$ENV{CXX}")
if(CXX)
	set(CMAKE_CXX_COMPILER CACHE STRING ${CXX})
endif()

if((CMAKE_VERSION VERSION_GREATER 3.1) OR (CMAKE_VERSION VERSION_EQUAL 3.1))
cmake_policy(SET CMP0054 NEW)
endif()

project(ArgParse)

option(UNITTESTS "Compile the unittests" OFF)
option(TUTORIAL "Compile the tutorial" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)

#Check for C++11 support
check_cxx_compiler_flag("-std=c++11" CPP11)
check_cxx_compiler_flag("-std=c++0x" CPP0X)

if(CPP11)
message(STATUS "Compiler uses -std=c++11")
set(CPPSTANDARD "-std=c++11")
else()
if(CPP0X)
message(STATUS "Compiler uses -std=c++0x")
set(CPPSTANDARD "-std=c++0x")
else()
message(FATAL "Compiler does not support C++11!")
endif()
endif()

set(CMAKE_REQUIRED_FLAGS "${CPPSTANDARD}")

#Check if we have nullptr
file(READ ${CMAKE_CURRENT_SOURCE_DIR}/platform_tests/nullptr_test.cpp NULLPTR_CODE)
check_cxx_source_compiles("${NULLPTR_CODE}" ARGPARSE_HAVE_NULLPTR)

if(ARGPARSE_HAVE_NULLPTR)
message(STATUS "Compiler has nullptr")
else()
message(STATUS "Compiler doesn't have nullptr")
endif()

#configure config.h
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/inc/ArgParse/config.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/inc/ArgParse/config.h")
	
set(VERSION_MAJOR 0)
set(VERSION_MINOR 6)
set(VERSION_PATCH 3)
set(VERSION_STRING ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

add_definitions("${CPPSTANDARD} -Wall -Wextra -Werror")
include_directories(inc ${CMAKE_CURRENT_BINARY_DIR}/inc)

if(UNITTESTS)
add_subdirectory(unittests)
endif()

if(TUTORIAL)
add_subdirectory(tutorial)
endif()

add_library(ArgParse SHARED src/Message.cxx src/ArgObject.cxx src/ArgObjContainer.cxx src/Argument.cxx src/ArgScalar.cxx src/ArgVector.cxx src/ArgGroup.cxx src/ArgExclusiveGroup.cxx src/ArgInclusiveGroup.cxx src/ArgExclusiveGroup.cxx src/ArgParser.cxx)
add_library(ArgParseStatic STATIC src/Message.cxx src/ArgObject.cxx src/ArgObjContainer.cxx src/Argument.cxx src/ArgScalar.cxx src/ArgVector.cxx src/ArgGroup.cxx src/ArgExclusiveGroup.cxx src/ArgInclusiveGroup.cxx src/ArgExclusiveGroup.cxx src/ArgParser.cxx)

set_target_properties(ArgParse PROPERTIES VERSION ${VERSION_STRING})
set_target_properties(ArgParse PROPERTIES SOVERSION ${VERSION_MAJOR})
set_target_properties(ArgParseStatic PROPERTIES VERSION ${VERSION_STRING})
set_target_properties(ArgParseStatic PROPERTIES SOVERSION ${VERSION_MAJOR})
set_target_properties(ArgParseStatic PROPERTIES OUTPUT_NAME ArgParse)

install(TARGETS ArgParse ArgParseStatic DESTINATION lib)
install(DIRECTORY inc/ArgParse DESTINATION include FILES_MATCHING PATTERN "*.h")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/inc/ArgParse/config.h DESTINATION include/ArgParse)

set(INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
if(FINAL_INSTALL_PREFIX)
	set(INSTALL_PREFIX "${FINAL_INSTALL_PREFIX}")
endif()

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
