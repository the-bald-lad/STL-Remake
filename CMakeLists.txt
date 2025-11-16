cmake_minimum_required(VERSION 3.28)
project(remaking_stdlib)

set(CMAKE_CXX_STANDARD 20)

set(SRC_DIR src)

add_executable(${PROJECT_NAME}
        ${SRC_DIR}/sandbox.cpp

        ${SRC_DIR}/iterator.h
        ${SRC_DIR}/array.h
        ${SRC_DIR}/vector.h

        ${SRC_DIR}/uniqueptr.h
        ${SRC_DIR}/sharedptr.h
        ${SRC_DIR}/weakptr.h

        ${SRC_DIR}/mystring.h
        ${SRC_DIR}/string_internal.h

        ${SRC_DIR}/algorithms.h
        ${SRC_DIR}/hash.h

        ${SRC_DIR}/trees.h

        ${SRC_DIR}/queue.h

        ${SRC_DIR}/map.h

        ${SRC_DIR}/type_traits.h
        ${SRC_DIR}/util.h
        ${SRC_DIR}/stlint.h

        ${SRC_DIR}/function.h
        ${SRC_DIR}/function_internal.h
)
