//
// Created by samjb on 11/06/2024.
//

#pragma once

#include "iterator.h"

namespace dataStructures
{
    template<typename T, size_t S>
    class Array
    {
    public:
        using ValueType = T;
        using Iterator = Iterating::Iterator<Array>;

        Array()
        {
            memset(m_data, 0, S * sizeof(T));
        }
        Array(const Array& copy) noexcept
            : m_data(copy.m_data)
        {
        }
        Array(Array&& move) noexcept
            : m_data(std::move(move.m_data))
        {
        }

        template<typename... Args>
        Array(Args&&... args)
            : m_data(std::forward<Args>(args)...)
        {
        }

        ~Array() = default;

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
        [[nodiscard]] constexpr size_t size() const noexcept { return S; }

        // Indexing operator
        T& operator[](size_t index) { return m_data[index]; }
        const T& operator[](size_t index) const { return m_data[index]; }

        // Return array pointer
        T* Data() { return m_data; }
        const T* Data() const { return m_data; }
    private:
        T m_data[S];
    };

}