//
// Created by samjb on 11/06/2024.
//

#pragma once

#include "stlint.h"

namespace Iterating
{
    template<typename T>
    class Iterator
    {
    public:
        using ValueType = typename T::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        explicit Iterator(PointerType ptr) noexcept
            : m_ptr(ptr)
        {
        }

        Iterator& operator=(const Iterator& other)
        {
            *m_ptr = *other.m_ptr;
            return *this;
        }

        PointerType operator+(int offset)
        {
            return m_ptr + offset;
        }

        PointerType operator-(int offset)
        {
            return m_ptr - offset;
        }

        Iterator& operator++()
        {
            ++m_ptr;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }

        Iterator& operator--()
        {
            --m_ptr;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator iterator = *this;
            --*this;
            return iterator;
        }

        ReferenceType operator[](sizet index)
        {
            return *(m_ptr + index);
        }

        PointerType operator->()
        {
            return m_ptr;
        }

        ReferenceType operator*()
        {
            return *m_ptr;
        }

        bool operator==(const Iterator& other) const
        {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

        bool operator<(const Iterator& other) const
        {
            return &*this < &other;
        }

        bool operator>(const Iterator& other) const
        {
            return &*this > &other;
        }
    private:
        PointerType m_ptr;
    };

}
