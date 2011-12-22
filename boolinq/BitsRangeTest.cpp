#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CommonTests.h"

#include "IterRange.h"
#include "BitsRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(BitsRange, OneByteFLHL)
{
    unsigned char src[] = {0xAA};
    int ans[] = {1,0,1,0,1,0,1,0};

    auto rng = range(src);
    auto dst = bits<HighToLow>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(BitsRange, OneByteFLLH)
{
    unsigned char src[] = {0xAA};
    int ans[] = {0,1,0,1,0,1,0,1};

    auto rng = range(src);
    auto dst = bits<LowToHigh>(rng);

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(BitsRange, OneIntFLHL)
{
    unsigned int src[] = {0x12345678};
    int ans[] = 
    {
        0,1,1,1,1,0,0,0,
        0,1,0,1,0,1,1,0,
        0,0,1,1,0,1,0,0,
        0,0,0,1,0,0,1,0,
    };

    auto rng = range(src);
    auto dst = bits<HighToLow,FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(BitsRange, OneIntFLLH)
{
    unsigned int src[] = {0x12345678};
    int ans[] = 
    {
        0,0,0,1,1,1,1,0,
        0,1,1,0,1,0,1,0,
        0,0,1,0,1,1,0,0,
        0,1,0,0,1,0,0,0,
    };

    auto rng = range(src);
    auto dst = bits<LowToHigh,FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}


