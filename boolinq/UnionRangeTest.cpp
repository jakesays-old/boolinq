#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "UnionAllRange.h"

using namespace boolinq;

TEST(UnionAllRange, TwoArraysFront)
{
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {6,7,8,9};

    auto rng1 = range(arr1);
    auto rng2 = range(arr2);
    auto dst = unionAll(rng1,rng2);

    for (int i = 1; i < 10; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.front());
        EXPECT_EQ(9, dst.back());
        EXPECT_EQ(i, dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(UnionAllRange, TwoArraysBack)
{
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {6,7,8,9};

    auto rng1 = range(arr1);
    auto rng2 = range(arr2);
    auto dst = unionAll(rng1,rng2);

    for (int i = 9; i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(1, dst.front());
        EXPECT_EQ(i, dst.back());
        EXPECT_EQ(i, dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(UnionAllRange, ArrayWithVectorFront)
{
    int arr1[] = {1,2,3,4,5};
    std::vector<int> arr2;
    arr2.push_back(6);
    arr2.push_back(7);
    arr2.push_back(8);
    arr2.push_back(9);

    auto rng1 = range(arr1);
    auto rng2 = range(arr2);
    auto dst = unionAll(rng1,rng2);

    for (int i = 1; i < 10; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.front());
        EXPECT_EQ(9, dst.back());
        EXPECT_EQ(i, dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(UnionAllRange, ArrayWithVectorBack)
{
    int arr1[] = {1,2,3,4,5};
    std::vector<int> arr2;
    arr2.push_back(6);
    arr2.push_back(7);
    arr2.push_back(8);
    arr2.push_back(9);

    auto rng1 = range(arr1);
    auto rng2 = range(arr2);
    auto dst = unionAll(rng1,rng2);

    for (int i = 9; i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(1, dst.front());
        EXPECT_EQ(i, dst.back());
        EXPECT_EQ(i, dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(UnionAllRange, ArrayVectorArrayFront)
{
    int arr1[] = {1,2,3,4,5};
    std::vector<int> arr2;
    arr2.push_back(6);
    arr2.push_back(7);
    arr2.push_back(8);
    arr2.push_back(9);
    int arr3[] = {10,11,12,13,14,15};

    auto rng1 = range(arr1);
    auto rng2 = range(arr2);
    auto rng3 = range(arr3);
    auto dst = unionAll(unionAll(rng1,rng2),rng3);

    for (int i = 1; i < 16; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(i, dst.front());
        EXPECT_EQ(15, dst.back());
        EXPECT_EQ(i, dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(UnionAllRange, ArrayVectorArrayBack)
{
    int arr1[] = {1,2,3,4,5};
    std::vector<int> arr2;
    arr2.push_back(6);
    arr2.push_back(7);
    arr2.push_back(8);
    arr2.push_back(9);
    int arr3[] = {10,11,12,13,14,15};

    auto rng1 = range(arr1);
    auto rng2 = range(arr2);
    auto rng3 = range(arr3);
    auto dst = unionAll(unionAll(rng1,rng2),rng3);

    for (int i = 15; i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(1, dst.front());
        EXPECT_EQ(i, dst.back());
        EXPECT_EQ(i, dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}