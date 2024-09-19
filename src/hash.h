//
// Created by samjb on 14/08/2024.
//

#pragma once

#include "strings.h"

#include "stlint.h"

namespace Hexing
{
    inline String intToHex(uint64t hash)
    {
        String hexStr(16, '0');

        for (int i = 15; i >= 0; --i)
        {
            auto* hexChars = "0123456789ABCDEF";
            hexStr[i] = hexChars[hash & 0xF];
            hash >>= 4;
        }

        return hexStr;
    }

    inline uint64t scrambleAndObscure(const uint64t& hash)
    {
        return (hash << 7 | hash >> 64 - 7) ^ 0xCAFEBABEDEADBEEF;
    }
}

inline String hash(const String& str) noexcept
{
    uint64t hash = 5381;

    for (const auto c : str)
        hash = (hash << 5) + hash + c;

    hash = Hexing::scrambleAndObscure(hash);

    return Hexing::intToHex(hash + hash * 512);
}