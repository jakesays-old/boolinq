#include <list>
#include <deque>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "ToContainer.h"

using namespace boolinq;

TEST(ToContainer, List2List)
{
    std::list<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toContainer<std::list>(rng);

    EXPECT_EQ(dst,src);
}

TEST(ToContainer, Deque2Deque)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toContainer<std::deque>(rng);

    EXPECT_EQ(dst,src);
}

TEST(ToContainer, Vector2Vector)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toContainer<std::vector>(rng);

    EXPECT_EQ(dst,src);
}