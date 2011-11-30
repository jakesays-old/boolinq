#include <list>
#include <deque>
#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Range.h"
#include "WhereRange.h"
#include "ExtractRange.h"

TEST(WhereRange, OddIntFilter)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);

    auto rng = range(src);
    auto odd = where(rng, [](int a){return a & 1;});
    auto dst = extract_vector(odd);

    std::vector<int> ans;
    ans.push_back(1);
    ans.push_back(3);
    ans.push_back(5);

    EXPECT_EQ(ans,dst);
}

TEST(WhereRange, StrLetterFilter)
{
    std::vector<std::string> src;
    src.push_back("apple");
    src.push_back("blackberry");
    src.push_back("adobe");
    src.push_back("microsoft");
    src.push_back("nokia");

    auto rng = range(src);
    auto odd = where(rng, [](std::string a){return a[0] == 'a';});
    auto dst = extract_vector(odd);

    std::vector<std::string> ans;
    ans.push_back("apple");
    ans.push_back("adobe");

    EXPECT_EQ(ans,dst);
}

TEST(WhereRange, YangFilter)
{
    struct ABC
    {
        std::string name;
        int age;

        ABC(std::string name, int age)
            : name(name), age(age)
        {
        }
    };

    std::vector<ABC> src;
    src.push_back(ABC("man1",20));
    src.push_back(ABC("man2",15));
    src.push_back(ABC("man3",30));
    src.push_back(ABC("man4",14));
    src.push_back(ABC("man5",18));

    auto rng = range(src);
    auto yang = where(rng, [](const ABC & a){return a.age < 18;});
    
    EXPECT_EQ("man2", yang.popFront().name);
    EXPECT_EQ("man4", yang.popFront().name);
    EXPECT_TRUE(yang.empty());
}