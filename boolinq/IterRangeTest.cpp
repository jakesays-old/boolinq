#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CommonTests.h"

#include "IterRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, ListInt)
{
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);

    int ans[] = {1,2,3,4,5};

    CheckRangeAll(range(lst), ans);
    CheckRangeAll(range(lst.begin(), lst.end()), ans);
    CheckRangeAll(range(lst.cbegin(), lst.cend()), ans);
}

TEST(IterRange, DequeInt)
{
    std::deque<int> dck;
    dck.push_back(1);
    dck.push_back(2);
    dck.push_back(3);
    dck.push_back(4);
    dck.push_back(5);
    
    int ans[] = {1,2,3,4,5};

    CheckRangeAll(range(dck), ans);
    CheckRangeAll(range(dck.begin(), dck.end()), ans);
    CheckRangeAll(range(dck.cbegin(), dck.cend()), ans);
}

TEST(IterRange, VectorInt)
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    int ans[] = {1,2,3,4,5};

    CheckRangeAll(range(vec), ans);
    CheckRangeAll(range(vec.begin(), vec.end()), ans);
    CheckRangeAll(range(vec.cbegin(), vec.cend()), ans);
}

TEST(IterRange, ArrayInt)
{
    int arr[] = {1,2,3,4,5};
    int * ptr = (int*)arr;
    
    int ans[] = {1,2,3,4,5};

    CheckRangeAll(range(arr), ans);
    CheckRangeAll(range(ptr, 5), ans);
    CheckRangeAll(range(ptr, ptr+5), ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, OneElement)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = range(src);

    CheckRangeAll(rng, ans);
}

TEST(IterRange, EmptyVector)
{
    std::vector<int> src;
    
    auto rng = range(src);

    EXPECT_TRUE(rng.empty());
}