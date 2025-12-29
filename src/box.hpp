/// @file  box.hpp
/// @brief Описание набора прямоугольников.
#ifndef MX2D_BOX_HPP
#define MX2D_BOX_HPP

#include <concepts>
#include <vector>
#include <span>

namespace mx2d
{

    template <std::floating_point Float = float>
    class BoxData
    {
    public:
        [[nodiscard]] constexpr auto getHalfWidth(this auto&& self) noexcept  { return std::span{ self._halfWidth  }; }
        [[nodiscard]] constexpr auto getHalfHeight(this auto&& self) noexcept { return std::span{ self._halfHeight }; }

    private:
        using FloatData = std::vector<Float>;
        FloatData _halfWidth;
        FloatData _halfHeight;
    };

}

#endif//MX2D_BOX_HPP
