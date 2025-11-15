//
// Created by samjb on 08/08/2024.
//

#pragma once

namespace util
{
    template <typename T_>
    struct remove_ref
    { using type = T_; };

    template <typename T_>
    struct remove_ref<T_&>
    { using type = T_; };

    template <typename T_>
    struct remove_ref<T_&&>
    { using type = T_; };

    template <typename T> constexpr bool is_lvalue(T&)  { return true; }
    template <typename T> constexpr bool is_lvalue(T&&) { return false; }

    using byte = unsigned char;
}

namespace util
{
    template <typename T>
    constexpr remove_ref<T>::type&& move(T& move_val) noexcept
    {
        return static_cast<remove_ref<T>&&>(move_val);
    }

    template <typename T>
    constexpr remove_ref<T>::type&& move(T&& move_val) noexcept
    {
        return static_cast<remove_ref<T>&&>(move_val);
    }

    // TODO: Add const versions
    template <typename T>
    T&& forward(typename remove_ref<T>::type& forward_val) noexcept
    {
        return static_cast<T&&>(forward_val);
    }

    template <typename T>
    T&& forward(typename remove_ref<T>::type&& forward_val) noexcept
    {
        static_assert(
            !is_lvalue<T>(),
            "util::forward must not be used to convert an rvalue to an lvalue"
            );
        return static_cast<T&&>(forward_val);
    }
}
