#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "DistinctRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(DistinctRange, IntsFront)
{
    std::vector<int> src;
    src.push_back(4);
    src.push_back(5);
    src.push_back(3);
    src.push_back(1);
    src.push_back(4); // duplicate
    src.push_back(2);
    src.push_back(1); // duplicate
    src.push_back(4); // duplicate
    src.push_back(6);

    auto rng = range(src);
    auto dst = distinct(rng);
    
    std::vector<int> ans;
    ans.push_back(4);
    ans.push_back(5);
    ans.push_back(3);
    ans.push_back(1);
    //ans.push_back(4); // duplicate
    ans.push_back(2);
    //ans.push_back(1); // duplicate
    //ans.push_back(4); // duplicate
    ans.push_back(6);

    for(unsigned i = 0; i < ans.size(); i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i], dst.front());
        EXPECT_EQ(6, dst.back());
        EXPECT_EQ(ans[i], dst.popFront());
    }
    
    EXPECT_TRUE(dst.empty());
}

TEST(DistinctRange, IntsBack)
{
    std::vector<int> src;
    src.push_back(4);
    src.push_back(5);
    src.push_back(3);
    src.push_back(1);
    src.push_back(4); // duplicate
    src.push_back(2);
    src.push_back(1); // duplicate
    src.push_back(4); // duplicate
    src.push_back(6);

    auto rng = range(src);
    auto dst = distinct(rng);
    
    std::vector<int> ans;
    ans.push_back(4);
    ans.push_back(5);
    ans.push_back(3);
    //ans.push_back(1); // duplicate
    //ans.push_back(4); // duplicate
    ans.push_back(2);
    ans.push_back(1);
    //ans.push_back(4); // duplicate
    ans.push_back(6);

    for(unsigned i = ans.size(); i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(4, dst.front());
        EXPECT_EQ(ans[i-1], dst.back());
        EXPECT_EQ(ans[i-1], dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(DistinctRange, IntMirrorFront)
{
    std::vector<int> src;
    src.push_back(3);
    src.push_back(2);
    src.push_back(1);
    src.push_back(0);
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    
    auto rng = range(src);
    auto dst = distinct(rng);

    std::vector<int> ans;
    ans.push_back(2);
    ans.push_back(1);
    ans.push_back(0);
    ans.push_back(3);
    
    for(unsigned i = 0; i < ans.size(); i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i], dst.front());
        EXPECT_EQ(3, dst.back());
        EXPECT_EQ(ans[i], dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(DistinctRange, IntMirrorBack)
{
    std::vector<int> src;
    src.push_back(3);
    src.push_back(2);
    src.push_back(1);
    src.push_back(0);
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);
    auto dst = distinct(rng);
    
    std::vector<int> ans;
    ans.push_back(2);
    ans.push_back(0);
    ans.push_back(1);
    ans.push_back(3);

    for(unsigned i = ans.size(); i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(2, dst.front());
        EXPECT_EQ(ans[i-1], dst.back());
        EXPECT_EQ(ans[i-1], dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}