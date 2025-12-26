/// @file test_body_id.cpp
#include <doctest.h>
#include <body_id.hpp>

using namespace mx2d;

TEST_SUITE("BodyId")
{

    TEST_CASE("default")
    {
        auto def { BodyId{} };
        
        CHECK(def.index() == 0);
        CHECK(def.type()  == BodyType::ConvexPolygon);

        auto copy { def };
        
        CHECK(def == copy);

        auto other { BodyId(127001, BodyType::Lozenge) };

        CHECK(other.index() == 127001);
        CHECK(other.type()  == BodyType::Lozenge);
        CHECK(other != def);
        CHECK(other > def);
        CHECK(copy < other);
    }

}
