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

    /// @brief  Хранилище данных на основе непрерывного массива.
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

        [[nodiscard]] decltype(auto) operator[](this auto&& self, BodyId id) noexcept
        {
            return self.Base::operator[](id.index());
        }
        
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

    
    /// @brief Добавляем к DataStorage тип Tag для автоматической выборки из набора.
    template <typename Tag, std::semiregular Item>
    class Data
        : public DataStorage<Item>
    {
    public:
        using Base = DataStorage<Item>;
        using Base::Base;
    };


    namespace impl
    {

        template <typename>
        struct IsTaggedData
            : std::bool_constant<false> {};

        template <typename Tag, typename Item>
        struct IsTaggedData<Data<Tag, Item>>
            : std::bool_constant<true> {};

        template <typename...>
        struct SelectByTag 
        {
            // Пусто.
        };

        template <typename Tag, typename Head, typename... Tail>
        struct SelectByTag<Tag, Head, Tail...>
        {
            using type = typename SelectByTag<Tag, Tail...>::type;
        };

        template <typename Tag, typename Item, typename... Tail>
        struct SelectByTag<Tag, Data<Tag, Item>, Tail...>
        {
            using type = Data<Tag, Item>;
        };

        template <typename Head, typename...>
        struct First
        {
            using type = Head;
        };

    }

    template <typename T>
    concept TaggedData =
        impl::IsTaggedData<T>::value;

    template <typename Tag, TaggedData... Fields>
    using SelectByTag =
        typename impl::SelectByTag<Tag, Fields...>::type;

    template <typename... Types>
    using First =
        typename impl::First<Types...>::type;


    template <TaggedData... Fields>
    class DataSet
        : private Fields...
    {
        static_assert(sizeof...(Fields) != 0);

    public:
        constexpr explicit DataSet(Index size)
            : Fields(static_cast<std::size_t>(size))...
        {
            // Пусто.
        }

        [[nodiscard]] constexpr bool empty() const noexcept
        {
            return asFirst().empty();
        }

        [[nodiscard]] constexpr auto size() const noexcept
            -> Index
        {
            return static_cast<Index>(asFirst().size());
        }

        [[nodiscard]] constexpr auto capacity() const noexcept
            -> Index
        {
            return static_cast<Index>(asFirst().capacity());
        }

        void reserve(Index capacity)
        {
            auto const cap { static_cast<std::size_t>(capacity) };
            Fields::reserve(cap)...;
        }

        void pop_back()
        {
            Fields::pop_back()...;
        }

        void erase(Index index)
        {
            Fields::erase(index)...;
        }

        template <typename Tag>
        [[nodiscard]] constexpr decltype(auto) select() && noexcept
        {
            return static_cast<SelectByTag<Tag, Fields...>&&>(*this);
        }

        template <typename Tag>
        [[nodiscard]] constexpr decltype(auto) select() & noexcept
        {
            return static_cast<SelectByTag<Tag, Fields...>&>(*this);
        }

        template <typename Tag>
        [[nodiscard]] constexpr decltype(auto) select() const& noexcept
        {
            return static_cast<SelectByTag<Tag, Fields...> const&>(*this);
        }

        template <typename Tag, typename Self>
        [[nodiscard]] constexpr auto view(this Self&& self) noexcept
        {
            return std::forward<Self>(self).select().view();
        }

    private:
        [[nodiscard]] constexpr decltype(auto) asFirst() const noexcept
        {
            return static_cast<First<Fields> const&>(*this);
        }
    };


}

#endif//MX2D_DATA_STORAGE_HPP
