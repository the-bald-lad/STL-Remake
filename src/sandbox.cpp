#include <iostream>

#include "pointers.h"

#include "array.h"
#include "function.h"
#include "vector.h"

#include "mystring.h"

void exampleOne()
{
    // Create custom vector
    stl::Vector<int> vector_of_ints;

    // Add items
    vector_of_ints.push_back(1);
    vector_of_ints.push_back(2);
    vector_of_ints.push_back(3);

    std::cout << "Output vector contents\n";

    // Loop through items using iterator
    for (const auto& item : vector_of_ints)
        std::cout << item << " ";
    std::cout << std::endl;
}

void exampleTwo()
{
    stl::Array<stl::UniquePointer<int>, 3> array_of_unique_pointers;

    array_of_unique_pointers[0] = make_unique<int>(100);
    array_of_unique_pointers[1] = make_unique<int>(200);
    array_of_unique_pointers[2] = make_unique<int>(300);

    std::cout << "Output array contents\n";

    for (auto & array_of_unique_pointer : array_of_unique_pointers)
        std::cout << *array_of_unique_pointer << " ";
    std::cout << std::endl;

    std::cout << array_of_unique_pointers.Size() << std::endl;
}

void exampleThree()
{
    // Create array of custom strings
    stl::Array<stl::String, 4> names = { "Sam", "John", "Lisa", "Aimee" };

    const stl::String temp = names[0];
    names[0] = names[1];
    names[1] = temp;

    for (const auto& name : names)
        std::cout << "Your name is: " << name << std::endl;
}

void DoStuff(int x, float y)
{
    std::cout << "Called with value: " << x + y << std::endl;
}

int main()
{
    stl::Function otherFunc(DoStuff);

    stl::Function<void, int> func([](int x) {
        std::cout << "called with value: " << x << std::endl;
    });

    otherFunc(1, 5);
}
