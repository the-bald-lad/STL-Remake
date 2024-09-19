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
        src/move.h
        src/hash.h
        src/stlint.h
)
