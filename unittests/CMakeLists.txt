add_executable(test_1 test_1.cpp)
target_link_libraries(test_1 ArgParse)
add_executable(test_2 test_2.cpp)
target_link_libraries(test_2 ArgParse)

install(TARGETS test_1 test_2 DESTINATION bin)
