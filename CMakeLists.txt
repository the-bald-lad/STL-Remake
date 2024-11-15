cmake_minimum_required(VERSION 3.28)
project(remaking_stdlib)

set(CMAKE_CXX_STANDARD 20)

add_executable(remaking_stdlib
        src/sandbox.cpp
        src/array.h
        src/iterator.h
        src/vector.h
        src/pointers.h
        src/strings.h
        src/algorithms.h
        src/trees.h
        src/queue.h
        src/map.h
        src/util.h
        src/hash.h
        src/stlint.h
        src/string_internal.h
        src/iterator.h
        src/mystring.h
        src/uniqueptr.h
        src/sharedptr.h
        src/weakptr.h
)
