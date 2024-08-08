//
// Created by samjb on 08/08/2024.
//

#pragma once

template<typename T>
T&& move(const T& move_val) noexcept
{
    return static_cast<T&&>(move_val);
}

template<typename T>
const T&& move(const T& move_val) noexcept
{
    return const_cast<T&&>(move_val);
}