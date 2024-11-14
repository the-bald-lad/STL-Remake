//
// Created by samjb on 27/09/2024.
//

#pragma once

#include "string_internal.h"

#include <ostream> // For cout overload

// String aliases
using String = string_internal<char>;


// cout overload
namespace std
{
    inline ostream& operator<<(ostream& out_stream, const String& str) { return out_stream << str.get_raw(); }
}