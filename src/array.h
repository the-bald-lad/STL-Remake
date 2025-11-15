//
// Created by samjb on 11/06/2024.
//

#pragma once

#include "iterator.h"
#include "stlint.h"
#include "util.h"

namespace stl
{
    template<typename TItem, sizet TSize>
    class Array
    {
    public:
        using ValueType = TItem;
        using Iterator = Iterating::Iterator<Array>;

        Array() = default;
        Array(const Array& copy) noexcept
        {
            for (sizet i = 0; i < TSize; ++i)
            {
                m_data[i] = copy.m_data[i];
            }
        }

        Array(Array&& move) noexcept
            : m_data(util::move(move.m_data))
        { }

        template<typename... Args>
        Array(Args&&... args)
            : m_data(util::forward<Args>(args)...)
        { }

        ~Array()
        {
            for (sizet i = 0; i < TSize; i++)
            {
                m_data[i].~TItem();
            }
        }

        Iterator begin()
        {
            return Iterator(m_data);
        }

        Iterator end()
        {
            return Iterator(m_data + TSize);
        }

        [[nodiscard]] constexpr sizet Size() const noexcept { return TSize; }

        TItem& operator[](sizet index) { return m_data[index]; }
        const TItem& operator[](sizet index) const { return m_data[index]; }

        TItem* Data() { return m_data; }
        const TItem* Data() const { return m_data; }
    private:
        TItem m_data[TSize];
    };

}