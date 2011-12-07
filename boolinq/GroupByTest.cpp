#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "GroupByRange.h"

#include "ToVector.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(GroupByRange, IntsFront)
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9};

    auto rng = range(arr);
    auto dst = groupBy(rng, [](int a){return a % 3;});

    EXPECT_EQ(1, dst.front().key());
    EXPECT_EQ(1, dst.front().popFront());
    EXPECT_EQ(4, dst.front().popFront());
    EXPECT_EQ(7, dst.front().popFront());
    EXPECT_TRUE(dst.front().empty());
    dst.popFront();

    EXPECT_EQ(2, dst.front().key());
    EXPECT_EQ(2, dst.front().popFront());
    EXPECT_EQ(5, dst.front().popFront());
    EXPECT_EQ(8, dst.front().popFront());
    EXPECT_TRUE(dst.front().empty());
    dst.popFront();
    
    EXPECT_EQ(0, dst.front().key());
    EXPECT_EQ(0, dst.front().popFront());
    EXPECT_EQ(3, dst.front().popFront());
    EXPECT_EQ(6, dst.front().popFront());
    EXPECT_EQ(9, dst.front().popFront());
    EXPECT_TRUE(dst.front().empty());
    dst.popFront();

    EXPECT_TRUE(dst.empty());
}

TEST(GroupByRange, CountChildrenByAge)
{
    struct Child
    {
        std::string name;
        int age;
    };

    Child children[] =
    {
        {"Piter", 12},
        {"Bella", 14},
        {"Torry", 15},
        {"Holly", 12},
        {"Zamza", 13},
    };

    auto rng = range(children);
    auto dst = groupBy(rng, [](const Child & a){return a.age < 14;});

    EXPECT_EQ(false, dst.front().key());
    EXPECT_EQ("Bella", dst.front().popFront().name);
    EXPECT_EQ("Torry", dst.front().popFront().name);
    EXPECT_TRUE(dst.front().empty());
    dst.popFront();

    EXPECT_EQ(true, dst.front().key());
    EXPECT_EQ("Piter", dst.front().popFront().name);
    EXPECT_EQ("Holly", dst.front().popFront().name);
    EXPECT_EQ("Zamza", dst.front().popFront().name);
    EXPECT_TRUE(dst.front().empty());
    dst.popFront();

    EXPECT_TRUE(dst.empty());
}