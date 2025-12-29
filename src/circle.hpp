/// @file  circle.hpp
/// @brief Описание набора кругов.
#ifndef MX2D_CIRCLE_HPP
#define MX2D_CIRCLE_HPP

#include "data_storage.hpp"

namespace mx2d
{

    template <std::floating_point Float = float>
    class CircleData
    {
    public:
        [[nodiscard]] constexpr auto getRadius(this auto&& self) noexcept { return std::span{ self._radius }; }

    private:
        using FloatData = std::vector<Float>;
        FloatData _radius;
    };

}

#endif//MX2D_CIRCLE_HPP
