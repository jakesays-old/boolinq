#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "ReverseRange.h"

using namespace boolinq;

TEST(ReverseRange, IntVectorFront)
{
    //
    // [1] [2] [3] [4]
    //  b           f
    //  b       f
    //  b   f
    //  bf
    //
    
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    auto dst = reverse(rng);

    for (int i = 4; i >= 1; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.front());
        EXPECT_EQ(1, dst.back());
        EXPECT_EQ(i, dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(ReverseRange, IntVectorBack)
{
    //
    // [1] [2] [3] [4]
    //  b           f
    //      b       f
    //          b   f
    //             bf
    //

    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    auto dst = reverse(rng);

    for (int i = 1; i <= 4; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(4, dst.front());
        EXPECT_EQ(i, dst.back());
        EXPECT_EQ(i, dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(ReverseRange, IntVectorFrontBack)
{
    //
    // [1] [2] [3] [4]
    //  b           f
    //  b       f
    //      b   f
    //      bf
    //
    
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    auto dst = reverse(rng);

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(4, dst.front());
    EXPECT_EQ(1, dst.back());
    EXPECT_EQ(4, dst.popFront());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(3, dst.front());
    EXPECT_EQ(1, dst.back());
    EXPECT_EQ(1, dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(3, dst.front());
    EXPECT_EQ(2, dst.back());
    EXPECT_EQ(3, dst.popFront());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(2, dst.front());
    EXPECT_EQ(2, dst.back());
    EXPECT_EQ(2, dst.popBack());

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(ReverseRange, DoubleReverseFront)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    auto dst = reverse(reverse(rng));

    for (int i = 1; i <= 4; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.front());
        EXPECT_EQ(i, dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(ReverseRange, DoubleReverseBack)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    auto dst = reverse(reverse(rng));

    for (int i = 4; i >= 1; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.back());
        EXPECT_EQ(i, dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}