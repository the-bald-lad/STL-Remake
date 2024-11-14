#include <iostream>

// TODO: Hash does not work

// TODO: map
// TODO: unordered_map
// TODO: shared/weak pointers
// TODO: Create std::forward


#include "pointers.h"

int main()
{
    dataStructures::UniquePointer<int> ptr = make_unique<int>(5);

    std::cout << *ptr << std::endl;
}
