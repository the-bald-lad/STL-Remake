//
// Created by samjb on 08/08/2024.
//

#pragma once

#include "type_traits.h"

namespace util {

    template <typename T>
    constexpr traits::remove_ref<T>::type&& move(T& move_val) noexcept
    {
        return static_cast<T&&>(move_val);
    }

    template <typename T>
    constexpr traits::remove_ref<T>::type&& move(T&& move_val) noexcept
    {
        return move_val;
    }

    template <typename T>
    T&& forward(typename traits::remove_ref<T>::type& forward_val) noexcept
    {
        return static_cast<T&&>(forward_val);
    }

    template <typename T>
    T&& forward(typename traits::remove_ref<T>::type&& forward_val) noexcept
    {
        static_assert(
            !traits::is_lvalue<T>,
            "util::forward must not be used to convert an rvalue to an lvalue"
            );
        return static_cast<T&&>(forward_val);
    }

}
