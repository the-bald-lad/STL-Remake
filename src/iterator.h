//
// Created by samjb on 11/06/2024.
//

#pragma once

namespace Iterating
{

    template<typename T>
    /*
     * Used to add to data structures to allow for nicer for loops
     */
    class Iterator
    {
    public:
        // Get type from data structure, type needs to be defined in structure
        using ValueType = typename T::ValueType;
        using PointerType = ValueType*;
        using ReferenceType = ValueType&;

        // ReSharper disable once CppParameterMayBeConst
        explicit Iterator(PointerType ptr) noexcept
            : m_ptr(ptr)
        {
        }

        Iterator& operator=(const Iterator& other)
        {
            *m_ptr = *other.m_ptr;
            return *this;
        }


        // Pointer offsetting
        PointerType operator+(int offset)
        {
            return m_ptr + offset;
        }

        PointerType operator-(int offset)
        {
            return m_ptr - offset;
        }

        // Post increment returns actual thing
        Iterator& operator++()
        {
            ++m_ptr;
            return *this;
        }

        // Pre increment returns a copy
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++(*this);
            return iterator;
        }

        // Decrement same as increment for pre and post
        Iterator& operator--()
        {
            --m_ptr;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator iterator = *this;
            --(*this);
            return iterator;
        }

        // Get the index
        ReferenceType operator[](size_t index)
        {
            return *(m_ptr + index);
        }

        // Return the raw pointer
        PointerType operator->()
        {
            return m_ptr;
        }

        // Return dereferenced ptr
        ReferenceType operator*()
        {
            return *m_ptr;
        }

        // Equality operators
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
