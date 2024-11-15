#include <iostream>

// TODO: Hash does not work

// TODO: map
// TODO: unordered_map
// TODO: shared/weak pointers

#include "pointers.h"

int main()
{
    stl::SharedPointer<int> other {};

    {
        stl::SharedPointer<int> ptr = make_shared<int>(5);

        other = ptr;

        std::cout << *ptr << std::endl;
    }

    std::cout << *other << std::endl;

    std::cout << "beans\n";
}
