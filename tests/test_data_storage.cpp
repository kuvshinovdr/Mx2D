/// @file test_data_storage.cpp
#include <doctest.h>
#include <data_storage.hpp>

#include <algorithm>
#include <initializer_list>

using namespace mx2d;

TEST_SUITE("DataStorage")
{

    TEST_CASE("")
    {
        auto stor { DataStorage<float>{} };
        stor.push_back(1.f);
        stor.push_back(0.5f);
        stor.push_back(char(10));

        CHECK(stor.size() == 3);
        CHECK(stor[1] == 0.5f);
        CHECK(stor.data() == stor.view().data());
        CHECK(std::ranges::equal(stor.view(), std::initializer_list{1.f, 0.5f, 10.f}));
        stor.pop_back();

        CHECK(stor.size() == 2);
        CHECK(std::ranges::equal(std::as_const(stor).view(), std::initializer_list{1.f, 0.5f}));

        stor.erase(0);
        CHECK(stor.size() == 1);
        CHECK(!stor.empty());
        CHECK(std::ranges::equal(stor.view(), std::initializer_list{0.5f}));

        stor.erase(0);
        CHECK(stor.size() == 0);
        CHECK(stor.empty());
        CHECK(std::ranges::equal(stor.view(), std::initializer_list<float>{}));
    }

}
