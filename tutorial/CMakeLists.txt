add_executable(tutorial tutorial.cpp)
target_link_libraries(tutorial ArgParse)

install(TARGETS tutorial DESTINATION bin)
