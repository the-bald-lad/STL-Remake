//
// Created by samjb on 23/06/2024.
//

#pragma once

#include "trees.h"

namespace Sorting
{
    template <typename T>
    void sort(T first, T last, bool ascending = true)
    {
        auto tree = dataStructures::BinaryTree<typename T::ValueType>();
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

