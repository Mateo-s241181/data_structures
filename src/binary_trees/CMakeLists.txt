add_executable(avl_tests avl_tests.cpp avl.cpp avl.h)
target_link_libraries(avl_tests Catch2::Catch2WithMain)
catch_discover_tests(avl_tests)