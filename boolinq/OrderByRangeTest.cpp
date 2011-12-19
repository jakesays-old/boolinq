#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "OrderByRange.h"

#include "ReverseRange.h"
#include "ToVector.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N, typename F>
void CheckRangeFront(R dst, T (&ans)[N], F f)
{
    for (int i = 0; i < N; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[i]),   f(dst.front()));
        EXPECT_EQ(f(ans[N-1]), f(dst.back()));
        EXPECT_EQ(f(ans[i]),   f(dst.popFront()));
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeBack(R dst, T (&ans)[N], F f)
{
    for (int i = N; i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[0]),   f(dst.front()));
        EXPECT_EQ(f(ans[i-1]), f(dst.back()));
        EXPECT_EQ(f(ans[i-1]), f(dst.popBack()));
    }

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N>
void CheckRangeFront(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeFront(dst, ans, [](const value_type & a){return a;});
}

template<typename R, typename T, int N>
void CheckRangeBack(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeBack(dst, ans, [](const value_type & a){return a;});
}

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, RandomIntsWithDuplicates)
{
    int src[] = {4,5,3,1,4,2,1,4,6};
    int ans[] = {1,1,2,3,4,4,4,5,6};

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeFront(dst, ans);
    CheckRangeBack(dst, ans);
}

TEST(OrderByRange, ReverseInts)
{
    int src[] = {4,3,2,1};
    int ans[] = {1,2,3,4};

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeFront(dst, ans);
    CheckRangeBack(dst, ans);
}

TEST(OrderByRange, OneElement)
{
    int src[] = {5};
    int ans[] = {5};
    
    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeFront(dst, ans);
    CheckRangeBack(dst, ans);
}

TEST(OrderByRange, NoElements)
{
    std::vector<int> src;
    
    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, RandomStringByContent)
{
    std::string src[] =
    {
        "microsoft",
        "intel",
        "nokia",
        "apple",
        "oracle",
        "sun",
    };

    std::string ans[] =
    {
        "apple",
        "intel",
        "microsoft",
        "nokia",
        "oracle",
        "sun",
    };

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeFront(dst, ans);
    CheckRangeBack(dst, ans);
}

TEST(OrderByRange, RandomStringByLength)
{
    std::string src[] =
    {
        "microsoft",
        "intel",
        "nokia",
        "apple",
        "oracle",
        "sun",
    };

    std::string ans[] =
    {
        "sun",
        "intel",
        "nokia",
        "apple",
        "oracle",
        "microsoft",
    };

    auto rng = range(src);
    auto dst = orderBy(rng, [](std::string a){return a.size();});

    CheckRangeFront(dst, ans, [](const std::string & s){return s.size();});
    CheckRangeBack(dst, ans, [](const std::string & s){return s.size();});
}