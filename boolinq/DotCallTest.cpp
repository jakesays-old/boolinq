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

TEST(DotCall, BytesRange)
{
    int src[] = {0xAABBCCDD};
    int ansFL[] = {0xDD,0xCC,0xBB,0xAA};
    int ansLF[] = {0xAA,0xBB,0xCC,0xDD};

    auto dstFL1 = from(src).bytes();
    auto dstFL2 = from(src).bytes<FirstToLast>();
    auto dstLF1 = from(src).bytes<LastToFirst>();

    CheckRangeEqArray(dstFL1, ansFL);
    CheckRangeEqArray(dstFL2, ansFL);
    CheckRangeEqArray(dstLF1, ansLF);
}            

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

//////////////////////////////////////////////////////////////////////////

TEST(DotCall, UnbytesRange)
{
    unsigned char src[] = 
    {
        0x78,0x56,0x34,0x12,
        0xDD,0xCC,0xBB,0xAA
    };
    int ansFL[] = {0x12345678,0xAABBCCDD};
    int ansLF[] = {0x78563412,0xDDCCBBAA};

    auto dstFL1 = from(src).unbytes<int>();
    auto dstFL2 = from(src).unbytes<int,FirstToLast>();
    auto dstLF1 = from(src).unbytes<int,LastToFirst>();

    CheckRangeEqArray(dstFL1, ansFL);
    CheckRangeEqArray(dstFL2, ansFL);
    CheckRangeEqArray(dstLF1, ansLF);
} 
