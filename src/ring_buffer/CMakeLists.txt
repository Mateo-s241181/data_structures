add_executable(ring_buf_tests ring_buf_tests.cpp ring_buf.cpp ring_buf.h)
target_link_libraries(ring_buf_tests Catch2::Catch2WithMain)
catch_discover_tests(ring_buf_tests)