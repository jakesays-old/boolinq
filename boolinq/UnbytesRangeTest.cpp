#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CommonTests.h"

#include "IterRange.h"
#include "UnbytesRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(UnbytesRange, OneIntDefault)
{
    unsigned char src[] = {0xAA,0xBB,0xCC,0xDD};
    int ans[] = {0xDDCCBBAA};

    auto rng = range(src);
    auto dst = unbytes<int>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbytesRange, OneIntFL)
{
    unsigned char src[] = {0xAA,0xBB,0xCC,0xDD};
    int ans[] = {0xDDCCBBAA};

    auto rng = range(src);
    auto dst = unbytes<int,FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbytesRange, OneIntLF)
{
    unsigned char src[] = {0xAA,0xBB,0xCC,0xDD};
    int ans[] = {0xAABBCCDD};

    auto rng = range(src);
    auto dst = unbytes<int,LastToFirst>(rng);

    CheckRangeEqArray(dst, ans);
}
