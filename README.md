# STL-Remake
This is a simple re-creation of the C++ Standard Template 
Library. It will be much worse than the STL but is intended 
for me to learn more about how they all work.

## Requirements and Versions

This is a standalone project so no libraries are needed

C++ version used: C++20 

## How to build

It uses CMake, so generating project files and building should 
be simple.
```commandline
cd /STL-Remake
cmake
```
The options I have used for building are:
```commandline
cmake -G "Ninja" -J 20
```

This project was made using CLion and Clang, so while it should
work with other compilers, they have not been tested.