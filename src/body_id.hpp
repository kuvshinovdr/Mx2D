/// @file  body_id.hpp
/// @brief Идентификатор тела (физического объекта).
#ifndef MX2D_BODY_ID_HPP
#define MX2D_BODY_ID_HPP

#include <cstdint>
#include <climits>
#include <bit>
#include <concepts>
#include <type_traits>
#include <utility>

namespace mx2d
{

    /// @brief Тип контура, задающего тело.
    enum class BodyType
        : std::uint_fast32_t
    {
        ConvexPolygon,  ///< выпуклый многоугольник, заданный последовательностью вершин
        Circle,         ///< круг
        Box,            ///< прямоугольник (с произвольно ориентированными сторонами)
        Lozenge,        ///< капсула (алгебраическая сумма отрезка и круга)
        Count
    };

    constexpr auto BodyTypeCount { std::to_underlying(BodyType::Count)     };
    constexpr auto BodyTypeBits  { std::bit_width(BodyTypeCount) - 1       };

    using Index = std::int_fast32_t;
    
    constexpr auto BodyIndexBits { sizeof(Index) * CHAR_BIT - BodyTypeBits };
    constexpr auto BodyIndexMax  { (Index(1) << BodyIndexBits) - 1         };

    [[nodiscard]] constexpr auto toUnsigned(std::signed_integral auto n) noexcept
    {
        return static_cast<std::make_unsigned_t<decltype(n)>>(n);
    }

    /// @brief Идентификатор физического тела: индекс и тип.
    class BodyId
    {
    public:
        constexpr BodyId() noexcept = default;

        constexpr BodyId(Index index, BodyType type)
            : _value(reduceIndex(index) | std::to_underlying(type) << BodyIndexBits)
        {
            // Пусто.
        }

        /// @brief Извлечь индекс тела в массиве атрибутов для тел данного типа. 
        [[nodiscard]] constexpr auto index() const noexcept
            -> Index
        {
            return static_cast<Index>(_value & BodyIndexMax);
        }

        /// @brief Извлечь тип тела. 
        [[nodiscard]] constexpr auto type() const noexcept
            -> BodyType
        {
            return static_cast<BodyType>(_value >> BodyIndexBits);
        }

        [[nodiscard]] constexpr auto operator<=>(BodyId const& other) const noexcept = default;
        [[nodiscard]] constexpr bool operator==(BodyId const& other) const noexcept  = default;

    private:
        using IndexBits = std::make_unsigned_t<Index>;
        
        [[nodiscard]] static constexpr auto reduceIndex(Index index) noexcept
            -> IndexBits
        {
            return static_cast<IndexBits>(index) & BodyIndexMax;
        }

        IndexBits _value {};
    };

}

#endif//MX2D_BODY_ID_HPP
