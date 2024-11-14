//
// Created by samjb on 08/08/2024.
//

#pragma once

// Helper Structs
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
}

// Utility Functions
namespace util
{
    template<typename T>
    constexpr typename remove_ref<T>::type&& move(T&& move_val) noexcept
    {
        return static_cast<std::remove_reference_t<T>&&>(move_val);
    }

    template<typename T>
    T&& forward(typename remove_ref<T>::type& forward_val) noexcept
    {
        return static_cast<T&&>(forward_val);
    }

    template<typename T>
    T&& forward(typename remove_ref<T>::type&& forward_val) noexcept
    {
        static_assert(!is_lvalue<T>(),
            "util::forward must not be used to convert an rvalue to an lvalue");
        return const_cast<T&&>(forward_val);
    }
}
