//
// Created by samjb on 11/06/2024.
//

#pragma once

#include "iterator.h"

#include <utility>

namespace dataStructures
{

    template<typename T>
    class Vector
    {
    public:
        // Allows for using iterators
        using ValueType = T;
        using Iterator = Iterating::Iterator<Vector>;

        Vector()
        {
            // Allocate space for 2 items on construction
            reAlloc(2);
        }

        ~Vector()
        {
            // Destroy everything contained within structure
            clear();

            // Delete structure itself
            ::operator delete(m_data, m_capacity * sizeof(T));
        }

        // Iterators
        [[nodiscard]] Iterator begin()
        {
            return Iterator(m_data);
        }

        [[nodiscard]] Iterator end()
        {
            return Iterator(m_data + m_size);
        }

        // Access functions
        [[nodiscard]] size_t size() const noexcept { return m_size; }

        // lvalue and implicit rvalue push back
        void push_back(const T& value) noexcept
        {
            checkCap();

            m_data[m_size] = std::move(value);
            m_size++;
        }

        // explicit rvalue push back
        void push_back(T&& value) noexcept
        {
            checkCap();

            m_data[m_size] = std::move(value);
            m_size++;
        }

        // Essentially dequeue
        void pop_back()
        {
            if (m_size <= 0)
            {
                __debugbreak();
                return;
            }

            m_size--;
            m_data[m_size].~T();
        }

        // Remove a specific index
        void remove(size_t index)
        {
            // Bounds checks
            if (index > m_size)
                __debugbreak();
            if (index <= 0)
                __debugbreak();

            // Delete item
            m_data[index].~T();

            // Move others up
            for (size_t i = index; i < m_size; i++)
                m_data[i] = m_data[i+1];

            // Reduce current size
            m_size--;
        }

        // Clear the structure
        void clear()
        {
            for (size_t i = 0; i < m_size; i++)
                m_data[i].~T();

            m_size = 0;
        }

        // Call constructors for items added
        template<typename... Args>
        [[maybe_unused]] T& emplace_back(Args&&... args) noexcept
        {
            checkCap();

            // Calls constructor for item added, inserts in-place
            new(&m_data[m_size]) T(std::forward<Args>(args)...);

            return m_data[m_size++];
        }

        T& operator[](size_t index) noexcept
        {
            return m_data[index];
        }

        const T& operator[](size_t index) const noexcept
        {
            return m_data[index];
        }
    private:
        // ReSharper disable once CppDFAUnreachableFunctionCall
        void checkCap(const size_t& size_divider = 2)
        {
            if (m_size >= m_capacity)
                reAlloc(m_capacity + m_capacity / size_divider);
        }

        // ReSharper disable once CppDFAUnreachableFunctionCall
        void reAlloc(const size_t& new_capacity) noexcept
        {
            // 1. allocate new block of memory
            T* new_block = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

            if (new_capacity < m_size)
                m_size = new_capacity;

            // 2. move to new location
            for (size_t i = 0; i < m_size; i++)
                new_block[i] = std::move(m_data[i]);

            // 3. free old block
            for (size_t i = 0; i < m_size; i++)
                m_data[i].~T();

            ::operator delete(m_data, m_capacity * sizeof(T));

            m_data = new_block;
            m_capacity = new_capacity;
        }

        // Holds pointer to first block of data
        T* m_data = nullptr;

        // Current size
        size_t m_size = 0;

        // Current max size
        size_t m_capacity = 0;
    };

}