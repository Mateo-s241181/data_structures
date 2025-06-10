
add_executable(element_tests element_tests.cpp element.cpp element.h)
target_link_libraries(element_tests Catch2::Catch2WithMain)
catch_discover_tests(element_tests)