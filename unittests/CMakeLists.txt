add_executable(test_1 test_1.cpp)
target_link_libraries(test_1 ArgParse)
add_executable(test_2 test_2.cpp)
target_link_libraries(test_2 ArgParse)
add_executable(test_3 test_3.cpp)
add_dependencies(test_3 standalone-wrapper)

install(TARGETS test_1 test_2 test_3 DESTINATION bin)
