//
// Created by samjb on 08/08/2024.
//

// Not unordered, not currently using hashing

#pragma once

#include "util.h"

namespace dataStructures
{
    template<typename T_key, typename T_item>
    class Map
    {
    public:
        Map() noexcept
        {
            reAlloc(5);
        }

        T_item& operator[](const T_key& index) { return getItem(index); }
        const T_item& operator[](const T_key& index) const { return getItem(index); }
    private:
        T_item& getItem(const T_key& index)
        {
            // Change to O(log(N))
            for (size_t i = 0; i < m_size; i++)
                if (m_keys[i] == index)
                    return m_items[i];

            return nullptr;
        }

        // ReSharper disable once CppDFAUnreachableFunctionCall
        void checkCap(const size_t& size_divider = 2)
        {
            if (m_size >= m_capacity)
                reAlloc(m_capacity + m_capacity / size_divider);
        }

        void reAlloc(const size_t& new_cap)
        {
            reAlloc_keys(new_cap);
            reAlloc_items(new_cap);
        }

        void reAlloc_keys(const size_t& new_capacity)
        {
            // 1. allocate new block of memory
            auto* new_block = static_cast<T_key*>(::operator new(new_capacity * sizeof(T_key)));

            if (new_capacity < m_size)
                m_size = new_capacity;

            // 2. move to new location
            for (size_t i = 0; i < m_size; i++)
                new_block[i] = move(m_keys[i]);

            // 3. free old block
            for (size_t i = 0; i < m_size; i++)
                m_keys[i].~T();

            ::operator delete(m_keys, m_capacity * sizeof(T_key));

            m_keys = new_block;
            m_capacity = new_capacity;
        }

        void reAlloc_items(const size_t& new_capacity)
        {
            // 1. allocate new block of memory
            auto* new_block = static_cast<T_item*>(::operator new(new_capacity * sizeof(T_item)));

            if (new_capacity < m_size)
                m_size = new_capacity;

            // 2. move to new location
            for (size_t i = 0; i < m_size; i++)
                new_block[i] = move(m_items[i]);

            // 3. free old block
            for (size_t i = 0; i < m_size; i++)
                m_items[i].~T();

            ::operator delete(m_items, m_capacity * sizeof(T_item));

            m_items = new_block;
            m_capacity = new_capacity;
        }

        T_key* m_keys = nullptr;
        T_item* m_items = nullptr;

        size_t m_capacity = 0;
        size_t m_size = 0;
    };
}
