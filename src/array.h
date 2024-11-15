//
// Created by samjb on 11/06/2024.
//

#pragma once

#include "iterator.h"

#include "stlint.h"

#include "util.h"

namespace stl
{
    template<typename T, sizet S>
    class Array
    {
    public:
        using ValueType = T;
        using Iterator = Iterating::Iterator<Array>;

        Array() = default;
        Array(const Array& copy) noexcept
            : m_data(copy.m_data)
        {
        }
        Array(Array&& move) noexcept
            : m_data(util::move(move.m_data))
        {
        }

        template<typename... Args>
        Array(Args&&... args)
            : m_data(util::forward<Args>(args)...)
        {
        }

        // Iterators
        Iterator begin()
        {
            return Iterator(m_data);
        }

        Iterator end()
        {
            return Iterator(m_data + S);
        }

        // ReSharper disable once CppMemberFunctionMayBeStatic
        [[nodiscard]] constexpr sizet size() const noexcept { return S; }

        // Indexing operator
        T& operator[](sizet index) { return m_data[index]; }
        const T& operator[](sizet index) const { return m_data[index]; }

        // Return array pointer
        T* Data() { return m_data; }
        const T* Data() const { return m_data; }
    private:
        T m_data[S];
    };

}