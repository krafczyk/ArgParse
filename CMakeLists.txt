project(ArgParse)

cmake_minimum_required(VERSION 2.8)

set(ArgParse_VERSION_MAJOR 0)
set(ArgParse_VERSION_MINOR 0)
set(ArgParse_VERSION_PATCH 0)
set(ArgParse_VERSION_STRING ${ArgParse_VERSION_MAJOR}.${ArgParse_VERSION_MINOR}.${ArgParse_VERSION_PATCH})

add_definitions("-std=c++11 -Wall -Wextra -Werror")
include_directories(inc)

add_library(ArgParse SHARED src/ArgParse.cxx)
add_library(ArgParseStatic STATIC src/ArgParse.cxx)

set_target_properties(ArgParse PROPERTIES VERSION ${ArgParse_VERSION_STRING})
set_target_properties(ArgParse PROPERTIES SOVERSION ${ArgParse_VERSION_MAJOR})
set_target_properties(ArgParseStatic PROPERTIES VERSION ${ArgParse_VERSION_STRING})
set_target_properties(ArgParseStatic PROPERTIES SOVERSION ${ArgParse_VERSION_MAJOR})
set_target_properties(ArgParseStatic PROPERTIES OUTPUT_NAME ArgParse)

install(TARGETS ArgParse DESTINATION lib)
install(DIRECTORY inc/ArgParse DESTINATION include FILES_MATCHING PATTERN "*.h")
