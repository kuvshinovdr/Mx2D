/// @file  world.hpp
/// @brief Структура данных, задающая состояние моделируемого "мира".
#ifndef MX2D_WORLD_HPP
#define MX2D_WORLD_HPP

#include <concepts>
#include <vector>
#include <span>

#include "body_id.hpp"

namespace mx2d
{

    template <std::floating_point Float = float>
    class World
    {
    public:
        [[nodiscard]] constexpr auto getPosX(this auto&& self) noexcept  { return std::span{ self._px };    }
        [[nodiscard]] constexpr auto getPosY(this auto&& self) noexcept  { return std::span{ self._py };    }
        [[nodiscard]] constexpr auto getVelX(this auto&& self) noexcept  { return std::span{ self._vx };    }
        [[nodiscard]] constexpr auto getVelY(this auto&& self) noexcept  { return std::span{ self._vy };    }
        [[nodiscard]] constexpr auto getAngle(this auto&& self) noexcept { return std::span{ self._angle }; }
        [[nodiscard]] constexpr auto getInvM(this auto&& self) noexcept  { return std::span{ self._invM };  }
        [[nodiscard]] constexpr auto getInvI(this auto&& self) noexcept  { return std::span{ self._invI };  }
        [[nodiscard]] constexpr auto getIds(this auto&& self) noexcept   { return std::span{ self._ids  };  }
        [[nodiscard]] constexpr auto getAngularVel(this auto&& self) noexcept { return std::span{ self._vAngl }; }

    private:
        using FloatData = std::vector<Float>;
        FloatData _px;      // координаты центра масс
        FloatData _py;
        FloatData _vx;      // скорость центра масс
        FloatData _vy;
        FloatData _invM;    // 1/масса
        FloatData _angle;   // угол поворота вокруг центра масс (рад)
        FloatData _vAngl;   // угловая скорость
        FloatData _invI;    // 1/момент инерции
        
        using BodyIdData = std::vector<BodyId>;
        BodyIdData _ids;    // идентификаторы тел
    };

}

#endif//MX2D_WORLD_HPP
