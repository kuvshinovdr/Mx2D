/// @file test_eigen.cpp
#include <doctest.h>
#include <Eigen/Dense>

using namespace Eigen;

// Проверяем, что Eigen доступен и работает.
TEST_SUITE("Eigen")
{

    TEST_CASE("vec2")
    {
        auto v1 { Vector2d(1, -1.5) };
        auto v2 { Vector2d(2,  0.5) };

        auto vs { v1 + 2.0 * v2 };
        
        CHECK(vs[0] ==  5.0);
        CHECK(vs[1] == -0.5);

        CHECK(v1.dot(v2)   == 1.25);
        CHECK(v1.cross(v2) == 3.5);
    }

}