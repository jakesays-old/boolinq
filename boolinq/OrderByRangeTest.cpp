#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "OrderByRange.h"

using namespace boolinq;

TEST(OrderByRange, RandomIntsWithDuplicatesFront)
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
    auto dst = orderBy(rng);

    EXPECT_FALSE(dst.empty());  EXPECT_EQ(1, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(1, dst.popFront()); // duplicate
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(2, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(3, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popFront()); // duplicate
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popFront()); // duplicate
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(5, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(6, dst.popFront());
    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, RandomIntsWithDuplicatesBack)
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
    auto dst = orderBy(rng);

    EXPECT_FALSE(dst.empty());  EXPECT_EQ(6, dst.popBack());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(5, dst.popBack());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popBack());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popBack()); // duplicate
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popBack()); // duplicate
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(3, dst.popBack());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(2, dst.popBack());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(1, dst.popBack());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(1, dst.popBack()); // duplicate
    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, ReverseInts)
{
    std::vector<int> src;
    src.push_back(4);
    src.push_back(3);
    src.push_back(2);
    src.push_back(1);

    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_FALSE(dst.empty());  EXPECT_EQ(1, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(2, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(3, dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ(4, dst.popFront());
    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, OneElementFront)
{
    std::vector<int> src;
    src.push_back(5);
    
    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(5, dst.popFront());
    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, OneElementBack)
{
    std::vector<int> src;
    src.push_back(5);

    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(5, dst.popBack());
    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, NoElements)
{
    std::vector<int> src;
    
    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, RandomStringByContent)
{
    std::vector<std::string> src;
    src.push_back("microsoft");
    src.push_back("intel");
    src.push_back("nokia");
    src.push_back("apple");
    src.push_back("oracle");
    src.push_back("sun");

    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_FALSE(dst.empty());  EXPECT_EQ("apple",     dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("intel",     dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("microsoft", dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("nokia",     dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("oracle",    dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("sun",       dst.popFront());
    EXPECT_TRUE(dst.empty());
}

TEST(OrderByRange, RandomStringByLength)
{
    std::vector<std::string> src;
    src.push_back("microsoft");
    src.push_back("intel");
    src.push_back("nokia");
    src.push_back("apple");
    src.push_back("oracle");
    src.push_back("sun");

    auto rng = range(src);
    auto dst = orderBy(rng, [](std::string a){return a.size();});

    EXPECT_FALSE(dst.empty());  EXPECT_EQ("sun",       dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("intel",     dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("nokia",     dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("apple",     dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("oracle",    dst.popFront());
    EXPECT_FALSE(dst.empty());  EXPECT_EQ("microsoft", dst.popFront());
    EXPECT_TRUE(dst.empty());
}