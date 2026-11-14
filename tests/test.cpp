#include <catch2/catch_test_macros.hpp>

TEST_CASE("Oak basic math sanity check", "[core]") {
    int a = 2;
    int b = 3;

    SECTION("addition works") { REQUIRE(a + b == 5); }

    SECTION("multiplication works") { CHECK(a * b == 6); }
}