#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

template<typename R>
void IterRangeFront_rng12345(R rng)
{
    for (int i = 1; i <= 5; i++)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(i, rng.front());
        EXPECT_EQ(5, rng.back());
        EXPECT_EQ(i, rng.popFront());
    }

    EXPECT_TRUE(rng.empty());
}

template<typename R>
void IterRangeBack_rng12345(R rng)
{
    for (int i = 5; i >= 1; i--)
    {
        EXPECT_FALSE(rng.empty());
        EXPECT_EQ(1, rng.front());
        EXPECT_EQ(i, rng.back());
        EXPECT_EQ(i, rng.popBack());
    }

    EXPECT_TRUE(rng.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, Rng12345)
{
    std::list<int> lst;
        lst.push_back(1);
        lst.push_back(2);
        lst.push_back(3);
        lst.push_back(4);
        lst.push_back(5);
    std::deque<int> dck;
        dck.push_back(1);
        dck.push_back(2);
        dck.push_back(3);
        dck.push_back(4);
        dck.push_back(5);
    std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5);
    int arr[] = {1,2,3,4,5};
    int * ptr = (int*)arr;


    // Non-const front

    IterRangeFront_rng12345(range(lst));
    IterRangeFront_rng12345(range(lst.begin(), lst.end()));
    IterRangeFront_rng12345(range(lst.cbegin(), lst.cend()));

    IterRangeFront_rng12345(range(dck));
    IterRangeFront_rng12345(range(dck.begin(), dck.end()));
    IterRangeFront_rng12345(range(dck.cbegin(), dck.cend()));

    IterRangeFront_rng12345(range(vec));
    IterRangeFront_rng12345(range(vec.begin(), vec.end()));
    IterRangeFront_rng12345(range(vec.cbegin(), vec.cend()));

    IterRangeFront_rng12345(range(arr));
    IterRangeFront_rng12345(range(ptr, 5));
    IterRangeFront_rng12345(range(ptr, ptr+5));

    // Non-const back

    IterRangeBack_rng12345(range(lst));
    IterRangeBack_rng12345(range(lst.begin(), lst.end()));
    IterRangeBack_rng12345(range(lst.cbegin(), lst.cend()));

    IterRangeBack_rng12345(range(dck));
    IterRangeBack_rng12345(range(dck.begin(), dck.end()));
    IterRangeBack_rng12345(range(dck.cbegin(), dck.cend()));

    IterRangeBack_rng12345(range(vec));
    IterRangeBack_rng12345(range(vec.begin(), vec.end()));
    IterRangeBack_rng12345(range(vec.cbegin(), vec.cend()));

    IterRangeBack_rng12345(range(arr));
    IterRangeBack_rng12345(range(ptr, 5));
    IterRangeBack_rng12345(range(ptr, ptr+5));
}

TEST(IterRange, ConstRng12345)
{
    std::list<const int> clst;
        clst.push_back(1);
        clst.push_back(2);
        clst.push_back(3);
        clst.push_back(4);
        clst.push_back(5);
    std::deque<const int> cdck;
        cdck.push_back(1);
        cdck.push_back(2);
        cdck.push_back(3);
        cdck.push_back(4);
        cdck.push_back(5);
    std::vector<const int> cvec;
        cvec.push_back(1);
        cvec.push_back(2);
        cvec.push_back(3);
        cvec.push_back(4);
        cvec.push_back(5);
    const int carr[] = {1,2,3,4,5};
    const int * cptr = (const int*)carr;

    // Const front

    IterRangeFront_rng12345(range(clst));
    IterRangeFront_rng12345(range(clst.begin(), clst.end()));
    IterRangeFront_rng12345(range(clst.cbegin(), clst.cend()));

    IterRangeFront_rng12345(range(cdck));
    IterRangeFront_rng12345(range(cdck.begin(), cdck.end()));
    IterRangeFront_rng12345(range(cdck.cbegin(), cdck.cend()));

    IterRangeFront_rng12345(range(cvec));
    IterRangeFront_rng12345(range(cvec.begin(), cvec.end()));
    IterRangeFront_rng12345(range(cvec.cbegin(), cvec.cend()));

    IterRangeFront_rng12345(range(carr));
    IterRangeFront_rng12345(range(cptr, 5));
    IterRangeFront_rng12345(range(cptr, cptr+5));
    
    // Const back

    IterRangeBack_rng12345(range(clst));
    IterRangeBack_rng12345(range(clst.begin(), clst.end()));
    IterRangeBack_rng12345(range(clst.cbegin(), clst.cend()));

    IterRangeBack_rng12345(range(cdck));
    IterRangeBack_rng12345(range(cdck.begin(), cdck.end()));
    IterRangeBack_rng12345(range(cdck.cbegin(), cdck.cend()));

    IterRangeBack_rng12345(range(cvec));
    IterRangeBack_rng12345(range(cvec.begin(), cvec.end()));
    IterRangeBack_rng12345(range(cvec.cbegin(), cvec.cend()));

    IterRangeBack_rng12345(range(carr));
    IterRangeBack_rng12345(range(cptr, 5));
    IterRangeBack_rng12345(range(cptr, cptr+5));
    
}

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, OneElementFront)
{
    int src[] = {5};

    auto rng = range(src);

    EXPECT_FALSE(rng.empty());
    EXPECT_EQ(5, rng.front());
    EXPECT_EQ(5, rng.back());
    EXPECT_EQ(5, rng.popFront());

    EXPECT_TRUE(rng.empty());
}

TEST(IterRange, OneElementBack)
{
    int src[] = {5};

    auto rng = range(src);

    EXPECT_FALSE(rng.empty());
    EXPECT_EQ(5, rng.front());
    EXPECT_EQ(5, rng.back());
    EXPECT_EQ(5, rng.popBack());

    EXPECT_TRUE(rng.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, EmptyVector)
{
    std::vector<int> src;
    
    auto rng = range(src);

    EXPECT_TRUE(rng.empty());
}