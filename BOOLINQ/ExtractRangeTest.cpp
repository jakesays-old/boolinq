#include <list>
#include <deque>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Range.h"
#include "ExtractRange.h"

using namespace boolinq;

// List To Any

TEST(ExtractRange, List2List)
{
    std::list<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = extract_list(rng);

    EXPECT_EQ(dst,src);
}

TEST(ExtractRange, List2Vector)
{
    std::list<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);
    
    auto rng = range(src);
    auto dst = extract_vector(rng);

    auto it1 = src.begin();
    auto it2 = dst.begin();
    for(; it1 != src.end() && it2 != dst.end(); ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

TEST(ExtractRange, List2Deque)
{
    std::list<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);
    
    auto rng = range(src);
    auto dst = extract_deque(rng);

    auto it1 = src.begin();
    auto it2 = dst.begin();
    for(; it1 != src.end() && it2 != dst.end(); ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

// Vector To Any

TEST(ExtractRange, Vector2List)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = extract_list(rng);

    auto it1 = src.begin();
    auto it2 = dst.begin();
    for(; it1 != src.end() && it2 != dst.end(); ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

TEST(ExtractRange, Vector2Vector)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);
    
    auto rng = range(src);
    auto dst = extract_vector(rng);

    EXPECT_EQ(dst,src);
}

TEST(ExtractRange, Vector2Deque)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);
    
    auto rng = range(src);
    auto dst = extract_deque(rng);

    auto it1 = src.begin();
    auto it2 = dst.begin();
    for(; it1 != src.end() && it2 != dst.end(); ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

// Deque To Any

TEST(ExtractRange, Deque2List)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = extract_list(rng);

    auto it1 = src.begin();
    auto it2 = dst.begin();
    for(; it1 != src.end() && it2 != dst.end(); ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

TEST(ExtractRange, Deque2Vector)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);
    
    auto rng = range(src);
    auto dst = extract_vector(rng);

    auto it1 = src.begin();
    auto it2 = dst.begin();
    for(; it1 != src.end() && it2 != dst.end(); ++it1, ++it2)
        EXPECT_EQ(*it1, *it2);
}

TEST(ExtractRange, Deque2Deque)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);
    
    auto rng = range(src);
    auto dst = extract_deque(rng);

    EXPECT_EQ(dst,src);
}
