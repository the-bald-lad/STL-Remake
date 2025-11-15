//
// Created by samjb on 23/06/2024.
//

#pragma once

#include "stlint.h"

#include "trees.h"

namespace sorting
{
    template <typename T>
    void sort(T first, T last, bool ascending = true)
    {
        auto tree = stl::BinaryTree<typename T::ValueType>();
        tree.generate(first, last);

        return;
        // TODO: Change to heap sort for n log n rather than n^2
        if (first == last)
            return;

        while (first != last)
        {
            if (*first > *++first)
            {
                auto temp = *first;
                *first = *(first-1);
                *--first = temp;
            }
        }
    }
}

// TODO: Fix this
namespace Setting
{
    template<typename T>
    void* memset(void *ptr, const int value, sizet size) {
        auto* p = static_cast<T*>(ptr);
        while (size--)
            *p++ = static_cast<T>(value);
        return ptr;
    }
}
