/// @file test_world.cpp
#include <doctest.h>
#include <world.hpp>

using namespace mx2d;

TEST_SUITE("World")
{

    TEST_CASE("")
    {
        auto world { World{} };
        CHECK(world.getPosX().empty());
        CHECK(world.getPosY().empty());
        CHECK(world.getVelX().empty());
        CHECK(world.getVelY().empty());
        CHECK(world.getAngle().empty());
        CHECK(world.getAngularVel().empty());
        CHECK(world.getInvM().empty());
        CHECK(world.getInvI().empty());
        CHECK(world.getIds().empty());
    }

}
