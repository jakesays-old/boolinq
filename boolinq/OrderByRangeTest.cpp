#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "OrderByRange.h"

using namespace boolinq;

TEST(OrderByRange, RandomInts)
{
    std::vector<int> src;
    src.push_back(5);
    src.push_back(3);
    src.push_back(1);
    src.push_back(4);
    src.push_back(2);
    src.push_back(6);

    auto rng = range(src);
    auto odd = orderBy(rng);

    EXPECT_EQ(1, odd.popFront());
    EXPECT_EQ(2, odd.popFront());
    EXPECT_EQ(3, odd.popFront());
    EXPECT_EQ(4, odd.popFront());
    EXPECT_EQ(5, odd.popFront());
    EXPECT_EQ(6, odd.popFront());
    EXPECT_TRUE(odd.empty());
}

TEST(OrderByRange, ReverseInts)
{
    std::vector<int> src;
    src.push_back(6);
    src.push_back(5);
    src.push_back(4);
    src.push_back(3);
    src.push_back(2);
    src.push_back(1);

    auto rng = range(src);
    auto odd = orderBy(rng);

    EXPECT_EQ(1, odd.popFront());
    EXPECT_EQ(2, odd.popFront());
    EXPECT_EQ(3, odd.popFront());
    EXPECT_EQ(4, odd.popFront());
    EXPECT_EQ(5, odd.popFront());
    EXPECT_EQ(6, odd.popFront());
    EXPECT_TRUE(odd.empty());
}

TEST(OrderByRange, RandomStringContent)
{
    std::vector<std::string> src;
    src.push_back("microsoft");
    src.push_back("intel");
    src.push_back("nokia");
    src.push_back("apple");
    src.push_back("oracle");
    src.push_back("sun");

    auto rng = range(src);
    auto odd = orderBy(rng);

    EXPECT_EQ("apple",     odd.popFront());
    EXPECT_EQ("intel",     odd.popFront());
    EXPECT_EQ("microsoft", odd.popFront());
    EXPECT_EQ("nokia",     odd.popFront());
    EXPECT_EQ("oracle",    odd.popFront());
    EXPECT_EQ("sun",       odd.popFront());
    EXPECT_TRUE(odd.empty());
}

TEST(OrderByRange, RandomStringLength)
{
    std::vector<std::string> src;
    src.push_back("microsoft");
    src.push_back("intel");
    src.push_back("nokia");
    src.push_back("apple");
    src.push_back("oracle");
    src.push_back("sun");

    auto rng = range(src);
    auto odd = orderBy(rng, [](std::string a){return a.size();});

    EXPECT_EQ("sun",       odd.popFront());
    EXPECT_EQ("intel",     odd.popFront());
    EXPECT_EQ("nokia",     odd.popFront());
    EXPECT_EQ("apple",     odd.popFront());
    EXPECT_EQ("oracle",    odd.popFront());
    EXPECT_EQ("microsoft", odd.popFront());
    EXPECT_TRUE(odd.empty());
}