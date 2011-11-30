#include <list>
#include <deque>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Range.h"
#include "WhereRange.h"
#include "ExtractRange.h"

// List To Any

TEST(WhereRange, BasicFilter)
{
    std::vector<int> src;
    src.push_back(101);
    src.push_back(202);
    src.push_back(303);
    src.push_back(404);
    src.push_back(505);

    auto rng = range(src);
    auto filtered = where(rng,[](int a){return a & 1;});
    auto dst = extract_vector(filtered);

    EXPECT_EQ(3, dst.size());
    EXPECT_EQ(101, dst[0]);
    EXPECT_EQ(303, dst[1]);
    EXPECT_EQ(505, dst[2]);
}