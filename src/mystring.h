//
// Created by samjb on 27/09/2024.
//

#pragma once

#include "string_internal.h"

#include <ostream> // For cout overload

namespace stl
{
    using String = string_internal<char>;

}

namespace std
{
    inline ostream& operator<<(ostream& out_stream, const stl::String& str) { return out_stream << str.get_raw(); }
}