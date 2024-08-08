//
// Created by samjb on 27/06/2024.
//

#pragma once

#include <queue>

namespace dataStructures
{
    template<typename T>
    class Queue
    {
    public:
        Queue()
        {
            reAlloc(5);
        }

        void push(const T& value)
        {
            checkCap();

            m_queue[m_size] = std::move(value);
            m_size++;
        }
        void push(T&& value)
        {
            checkCap();

            m_queue[m_size] = std::move(value);
            m_size++;
        }

        T pop()
        {
            T val = m_queue[0];

            for (size_t i = 0; i < m_size-1; i++)
                m_queue[i] = m_queue[i+1];

            m_size--;

            return val;
        }

        T front()
        {
            return m_queue[0];
        }
    private:
        void checkCap()
        {
            if (m_size >= m_capacity)
                reAlloc(m_capacity + m_capacity % 4);
        }

        void reAlloc(const size_t new_capacity) noexcept
        {
            // 1. allocate new block of memory
            T* new_block = static_cast<T*>(::operator new(new_capacity * sizeof(T)));

            if (new_capacity < m_size)
                m_size = new_capacity;

            // 2. move to new location
            for (size_t i = 0; i < m_size; i++)
                new_block[i] = std::move(m_queue[i]);

            // 3. free old block
            for (size_t i = 0; i < m_size; i++)
                m_queue[i].~T();

            ::operator delete(m_queue, m_capacity * sizeof(T));

            m_queue = new_block;
            m_capacity = new_capacity;
        }

        T* m_queue = nullptr;

        size_t m_size = 0;
        size_t m_capacity = 0;
    };
}