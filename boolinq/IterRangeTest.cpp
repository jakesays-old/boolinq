#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"

using namespace boolinq;

TEST(IterRange, PopFront)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    
    for (int i = 1; i <= 4; i++)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.front());
        EXPECT_EQ(i, rng.popFront());
    }

    EXPECT_TRUE(rng.empty());
}

TEST(IterRange, PopBack)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);

    auto rng = range(src);
    
    for (int i = 4; i >= 1; i--)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.back());
        EXPECT_EQ(i, rng.popBack());
    }

    EXPECT_TRUE(rng.empty());
}