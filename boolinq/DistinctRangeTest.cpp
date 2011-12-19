#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "CommonTests.h"

#include "IterRange.h"
#include "DistinctRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(DistinctRange, Ints1to6)
{
    int src[]   = {4,5,3,1,4,2,1,4,6};
    int ansF[]  = {4,5,3,1,  2,    6};
    int ansB[]  = {4,5,3,    2,1,  6};
    int ansFB[] = {4,5,3,1,  2,    6};
    int ansBF[] = {4,5,3,    2,1,  6};

    auto rng = range(src);
    auto dst = distinct(rng);
    
    CheckRangeFront(dst, ansF);
    CheckRangeBack(dst, ansB);
    CheckRangeFrontBack(dst, ansFB);
    CheckRangeBackFront(dst, ansBF);
}

TEST(DistinctRange, IntMirrorFront)
{
    int src[]   = {3,2,1,0,1,2,3};
    int ansF[]  = {2,1,0,3};
    int ansB[]  = {2,0,1,3};
    int ansFB[] = {2,1,0,3};
    int ansBF[] = {2,0,1,3};

    auto rng = range(src);
    auto dst = distinct(rng);

    CheckRangeFront(dst, ansF);
    CheckRangeBack(dst, ansB);
    CheckRangeFrontBack(dst, ansFB);
    CheckRangeBackFront(dst, ansBF);
}

TEST(DistinctRange, ManyEqualsFront)
{
    int src[] = {1,1,1,1};
    int ans[] = {1};

    auto rng = range(src);
    auto dst = distinct(rng);
    
    CheckRangeAll(dst, ans);
}

TEST(DistinctRange, ManyEqualsWithOneFront)
{
    int src[] = {1,1,2,1};
    int ans[] = {2,1};

    auto rng = range(src);
    auto dst = distinct(rng);

    CheckRangeAll(dst, ans);
}

TEST(DistinctRange, OneFieldFront)
{
    struct Man
    {
        std::string name;
        int age;
    };

    Man src[] =
    {
        {"Anton",1},
        {"Taran",2},
        {"Poker",3},
        {"Agata",4},
        {"Mango",2},
        {"Banan",1},
    };

    Man ans[] =
    {
        {"Taran",2},
        {"Poker",3},
        {"Agata",4},
        {"Banan",1},
    };

    auto rng = range(src);
    auto dst = distinct(rng, [](const Man & man){return man.age;});

    CheckRangeFront(dst, ans, [](const Man & man){return man.name;});
    CheckRangeBack(dst, ans, [](const Man & man){return man.name;});
}