/// @file  data_storage.hpp
/// @brief Контейнер данных тел.
#ifndef MX2D_DATA_STORAGE_HPP
#define MX2D_DATA_STORAGE_HPP

#include "body_id.hpp"

#include <concepts>
#include <span>
#include <utility>
#include <vector>

namespace mx2d
{

    namespace config
    {

        template <typename Item>
        struct DataStorageContainer
        {
            using type = std::vector<Item>;
        };

    }

    template <typename Item>
    using DataStorageContainer =
        typename config::DataStorageContainer<Item>::type;

    template <std::semiregular Item>
    class DataStorage
        : private DataStorageContainer<Item>
    {
        using Base = DataStorageContainer<Item>;

    public:
        [[nodiscard]] constexpr auto view() const& noexcept
        {
            return std::span{ static_cast<Base const&>(*this) };
        }

        [[nodiscard]] constexpr auto view()& noexcept
        {
            return std::span{ static_cast<Base&>(*this) };
        }
        
        using Base::Base;
        using Base::operator[];
        using Base::data;
        using Base::size;
        using Base::empty;

        using Base::pop_back;
        using Base::reserve;
        using Base::capacity;
        
        /// @brief  Добавить новый элемент в конец набора. При превышении BodyIndexMax размера UB.
        /// @return индекс добавленного элемента
        template <typename From>
        auto push_back(From&& item)
            -> Index
        {
            // DEBUG: check size
            auto const result { static_cast<Index>(size()) };
            Base::emplace_back(std::forward<From>(item));
            return result;
        }

        /// @brief Удалить элемент по заданному индексу (переставляет последний элемент на место удаляемого).
        /// @param index индекс удаляемого элемента должен быть корректным: от 0 до size()-1, иначе UB
        /// @return (size() - 1) -- индекс элемента, который нужно заменить на index, или отрицательное, если заменять нечего
        auto erase(Index index) noexcept
            -> Index
        {
            // DEBUG: check index
            auto const last   { static_cast<Index>(size()) - 1 };
            auto const result { last == index? -1: last };
            
            if (result > 0) {
                (*this)[index] = std::move((*this)[result]);    
            }
            
            pop_back();
            return result;
        }
    };

}

#endif//MX2D_DATA_STORAGE_HPP
