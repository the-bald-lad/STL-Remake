//
// Created by samjb on 14/08/2024.
//

#pragma once

#include "mystring.h"

#include "stlint.h"

namespace Hexing
{
    inline stl::String intToHex(uint64t hash)
    {
        stl::String hexStr(16, '0');

        for (int i = 15; i >= 0; --i)
        {
            const auto* hexChars = "0123456789ABCDEF";
            hexStr[i] = hexChars[hash & 0xF];
            hash >>= 4;
        }

        return hexStr;
    }

    inline uint64t scrambleAndObscure(const uint64t& hash)
    {
        return (hash << 7 | hash >> 64) ^ 0xCAFEBABEDEADBEEF;
    }
}

inline stl::String hash(const stl::String& str) noexcept
{
    uint64t hash = 5381;

    for (const auto c : str)
        hash = (hash << 5) + hash + c;

    hash = Hexing::scrambleAndObscure(hash);

    // TODO: this doesn't work
    return Hexing::intToHex(hash);
}