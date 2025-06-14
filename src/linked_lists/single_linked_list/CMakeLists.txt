add_executable(sll_tests sll_tests.cpp sll.cpp sll.h)
target_link_libraries(sll_tests Catch2::Catch2WithMain)
catch_discover_tests(sll_tests)