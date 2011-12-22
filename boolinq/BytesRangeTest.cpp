#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CommonTests.h"

#include "IterRange.h"
#include "BytesRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(ToBytesRange, OneByteFL)
{
    unsigned char src[] = {0xAA};
    int ans[] = {0xAA};

    auto rng = range(src);
    auto dst = bytes<FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(ToBytesRange, OneByteLF)
{
    unsigned char src[] = {0xAA};
    int ans[] = {0xAA};

    auto rng = range(src);
    auto dst = bytes<LastToFirst>(rng);

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(ToBytesRange, OneIntFL)
{
    int src[] = {0x12345678};
    int ans[] = {0x78,0x56,0x34,0x12};

    auto rng = range(src);
    auto dst = bytes<FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(ToBytesRange, OneIntLF)
{
    int src[] = {0x12345678};
    int ans[] = {0x12,0x34,0x56,0x78};

    auto rng = range(src);
    auto dst = bytes<LastToFirst>(rng);

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(ToBytesRange, IntsFL)
{
    int src[] = {0x12345678, 0xAABBCCDD};
    int ans[] = 
    {
        0x78,0x56,0x34,0x12,
        0xDD,0xCC,0xBB,0xAA,
    };

    auto rng = range(src);
    auto dst = bytes<FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}