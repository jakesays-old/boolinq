#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(DotCall, BitsRangeHL)
{
    int src[] = {0xAABBCCDD};
    int ansFL[] = 
    {
        1,1,0,1,1,1,0,1,
        1,1,0,0,1,1,0,0,
        1,0,1,1,1,0,1,1,
        1,0,1,0,1,0,1,0,
    };
    int ansLF[] = 
    {
        1,0,1,0,1,0,1,0,
        1,0,1,1,1,0,1,1,
        1,1,0,0,1,1,0,0,
        1,1,0,1,1,1,0,1,
    };

    auto dstFL1 = from(src).bits();
    auto dstFL2 = from(src).bits<HighToLow>();
    auto dstFL3 = from(src).bits<HighToLow,FirstToLast>();
    auto dstLF1 = from(src).bits<HighToLow,LastToFirst>();

    CheckRangeEqArray(dstFL1, ansFL);
    CheckRangeEqArray(dstFL2, ansFL);
    CheckRangeEqArray(dstFL3, ansFL);
    CheckRangeEqArray(dstLF1, ansLF);
}

TEST(DotCall, BitsRangeLH)
{
    int src[] = {0xAABBCCDD};
    int ansFL[] = 
    {
        1,0,1,1,1,0,1,1,
        0,0,1,1,0,0,1,1,
        1,1,0,1,1,1,0,1,
        0,1,0,1,0,1,0,1,
    };
    int ansLF[] = 
    {
        0,1,0,1,0,1,0,1,
        1,1,0,1,1,1,0,1,
        0,0,1,1,0,0,1,1,
        1,0,1,1,1,0,1,1,
    };

    auto dstFL1 = from(src).bits<LowToHigh>();
    auto dstFL2 = from(src).bits<LowToHigh,FirstToLast>();
    auto dstLF1 = from(src).bits<LowToHigh,LastToFirst>();

    CheckRangeEqArray(dstFL1, ansFL);
    CheckRangeEqArray(dstFL2, ansFL);
    CheckRangeEqArray(dstLF1, ansLF);
}
