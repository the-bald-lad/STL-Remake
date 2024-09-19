#include <iostream>

// TODO: map
// TODO: unordered_map
// TODO: shared/weak pointers

#include "array.h"

#include "algorithms.h"

#include "queue.h"
#include "trees.h"

#include "hash.h"

int main()
{
    dataStructures::Array<String, 5> strings;
    strings[0] = "Test";
    strings[1] = "Test1";
    strings[2] = "Beans";
    strings[3] = "Cheese";
    strings[4] = "a";

    for (const auto& i : strings)
        std::cout << hash(i) << " : " << i << std::endl;
}

