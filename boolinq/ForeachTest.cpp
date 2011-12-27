#include <list>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "Foreach.h"

using namespace boolinq;

TEST(Foreach, ThreeCharsSum)
{
    std::vector<char> src;
    src.push_back('a');
    src.push_back('b');
    src.push_back('c');

    std::string str = "";
    foreach(range(src), [&](char a){str += a;});

    EXPECT_EQ("abc", str);
}

TEST(Foreach, ThreeCharsUpperSum)
{
    std::vector<char> src;
    src.push_back('a');
    src.push_back('b');
    src.push_back('c');

    std::string str = "";
    foreach(range(src), [&](char a){str += a + ('A' - 'a');});

    EXPECT_EQ("ABC", str);
}

TEST(Foreach, ThreeIntsSum)
{
    std::vector<int> src;
    src.push_back(10);
    src.push_back(20);
    src.push_back(30);

    int sum = 0;
    foreach(range(src), [&](int a){sum += a;});

    EXPECT_EQ(60, sum);
}
