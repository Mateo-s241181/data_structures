#include <catch2/catch_test_macros.hpp>

#include "ring_buf.h"

TEST_CASE("Constructor 1", "[ringbuf]")
{
    ringbuf<int> x{2};

    REQUIRE(x.length == 2);
    REQUIRE(x.data.size() == 2);
}