#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "boolinq.h"

using namespace boolinq;

// Where Tests

TEST(Linq, WhereOdd)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);

    auto rng = from(src).where([](int a){return a%2 == 1;});

    for (int i = 1; i <= 5; i+=2)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.front());
        EXPECT_EQ(i, rng.popFront());
    }

    EXPECT_TRUE(rng.empty());
}

TEST(Linq, WhereOdd_WhereLess)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto rng = from(src).where([](int a){return a%2 == 1;})
                        .where([](int a){return a < 4;});

    for (int i = 1; i <= 3; i+=2)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.front());
        EXPECT_EQ(i, rng.popFront());
    }

    EXPECT_TRUE(rng.empty());
}

TEST(Linq, WhereLess_WhereOdd)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto rng = from(src).where([](int a){return a<4;})
                        .where([](int a){return a%2 == 1;});

    for (int i = 1; i <= 3; i+=2)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.front());
        EXPECT_EQ(i, rng.popFront());
    }

    EXPECT_TRUE(rng.empty());
}

TEST(Linq, WhereLess_WhereOdd_OrderByDesc)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto rng = from(src).where([](int a){return a<6;})
                        .where([](int a){return a%2 == 1;})
                        .orderBy([](int a){return -a;});

    for (int i = 5; i >= 1; i-=2)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.front());
        EXPECT_EQ(i, rng.popFront());
    }

    EXPECT_TRUE(rng.empty());
}

TEST(Linq, WhereOdd_ToVector)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto dst = from(src).where([](int a){return a%2 == 1;})
                        .toVector();

    std::vector<int> ans;
    ans.push_back(1);
    ans.push_back(3);
    ans.push_back(5);
    ans.push_back(7);
    
    EXPECT_EQ(ans,dst);
}

TEST(Linq, WhereOdd_WhereLess_SelectMul2_ToVector)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto dst = from(src).where([](int a){return a%2 == 1;})
                        .where([](int a){return a < 6;})
                        .select([](int a){return a*2;})
                        .toVector();

    std::vector<int> ans;
    ans.push_back(2);
    ans.push_back(6);
    ans.push_back(10);

    EXPECT_EQ(ans,dst);
}

TEST(Linq, WhereOdd_WhereLess_SelectMul2_Reverse_ToVector)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto dst = from(src).where([](int a){return a%2 == 1;})
        .where([](int a){return a < 6;})
        .select([](int a){return a*2;})
        .reverse()
        .toVector();

    std::vector<int> ans;
    ans.push_back(10);
    ans.push_back(6);
    ans.push_back(2);

    EXPECT_EQ(ans,dst);
}

TEST(Linq, WhereOdd_Reverse_Reverse)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);
    src.push_back(7);
    src.push_back(8);

    auto dst = from(src).where([](int a){return a%2 == 1;})
                        .reverse()
                        .where([](int a){return a < 4;})
                        .reverse()
                        .toVector();

    std::vector<int> ans;
    ans.push_back(1);
    ans.push_back(3);
    
    EXPECT_EQ(ans,dst);
}

//////////////////////////////////////////////////////////////////////////

TEST(Linq, Array_Front)
{
    int src[] = {1,2,3,4,5};

    auto dst = from(src);

    for(int i = 1; i <= 5; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.front());
        EXPECT_EQ(5, dst.back());
        EXPECT_EQ(i, dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(Linq, Array_Back)
{
    int src[] = {1,2,3,4,5};

    auto dst = from(src);

    for(int i = 5; i >= 1; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(1, dst.front());
        EXPECT_EQ(i, dst.back());
        EXPECT_EQ(i, dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}
