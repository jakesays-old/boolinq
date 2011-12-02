#include <vector>
#include <string>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "IterRange.h"
#include "WhereRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, IntOddFront)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a & 1;});
    
    std::vector<int> ans;
    ans.push_back(1);
    ans.push_back(3);
    ans.push_back(5);

    for(unsigned i = 0; i < ans.size(); i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i], dst.front());
        EXPECT_EQ(ans[i], dst.popFront());
    }
    
    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, IntOddBack)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a & 1;});

    std::vector<int> ans;
    ans.push_back(1);
    ans.push_back(3);
    ans.push_back(5);

    for(int i = ans.size(); i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i-1], dst.back());
        EXPECT_EQ(ans[i-1], dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, IntOddFrontBack)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);
    src.push_back(6);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a & 1;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(1, dst.front());
    EXPECT_EQ(5, dst.back());
    EXPECT_EQ(1, dst.popFront());
    
    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(3, dst.front());
    EXPECT_EQ(5, dst.back());
    EXPECT_EQ(5, dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(3, dst.front());
    EXPECT_EQ(3, dst.back());
    EXPECT_EQ(3, dst.popFront());

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, FirstLetterFront)
{
    std::vector<std::string> src;
    src.push_back("apple");
    src.push_back("blackberry");
    src.push_back("adobe");
    src.push_back("microsoft");
    src.push_back("nokia");

    auto rng = range(src);
    auto dst = where(rng, [](std::string a){return a[0] == 'a';});

    std::vector<std::string> ans;
    ans.push_back("apple");
    ans.push_back("adobe");

    for(unsigned i = 0; i < ans.size(); i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i], dst.front());
        EXPECT_EQ(ans[i], dst.popFront());
    }

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, FirstLetterBack)
{
    std::vector<std::string> src;
    src.push_back("apple");
    src.push_back("blackberry");
    src.push_back("adobe");
    src.push_back("microsoft");
    src.push_back("nokia");

    auto rng = range(src);
    auto dst = where(rng, [](std::string a){return a[0] == 'a';});

    std::vector<std::string> ans;
    ans.push_back("apple");
    ans.push_back("adobe");

    for(unsigned i = ans.size(); i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i-1], dst.back());
        EXPECT_EQ(ans[i-1], dst.popBack());
    }

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, NameAgeLess)
{
    struct NameAge
    {
        std::string name;
        int age;

        NameAge(std::string name, int age)
            : name(name), age(age)
        {
        }
    };

    std::vector<NameAge> src;
    src.push_back(NameAge("man1",20));
    src.push_back(NameAge("man2",15));
    src.push_back(NameAge("man3",30));
    src.push_back(NameAge("man4",14));
    src.push_back(NameAge("man5",18));

    auto rng = range(src);
    auto dst = where(rng, [](const NameAge & a){return a.age < 18;});
    
    std::vector<NameAge> ans;
    ans.push_back(NameAge("man2",20));
    ans.push_back(NameAge("man4",15));

    for(unsigned i = 0; i < ans.size(); i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(ans[i].name, dst.front().name);
        EXPECT_EQ(ans[i].name, dst.popFront().name);
    }

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, MayToOneFront)
{
    std::vector<int> src;
    src.push_back(0);
    src.push_back(1);
    src.push_back(2);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 1;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(1, dst.front());
    EXPECT_EQ(1, dst.popFront());
    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, ManyToOneBack)
{
    std::vector<int> src;
    src.push_back(0);
    src.push_back(1);
    src.push_back(2);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 1;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(1, dst.back());
    EXPECT_EQ(1, dst.popBack());
    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, OneToOneFront)
{
    std::vector<int> src;
    src.push_back(5);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(5, dst.front());
    EXPECT_EQ(5, dst.popFront());
    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, OneToOneBack)
{
    std::vector<int> src;
    src.push_back(5);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(5, dst.back());
    EXPECT_EQ(5, dst.popBack());
    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, ManyToZero)
{
    std::vector<int> src;
    src.push_back(0);
    src.push_back(1);
    src.push_back(2);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 5;});

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, OneToZero)
{
    std::vector<int> src;
    src.push_back(5);

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>10;});

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, ZeroToZero)
{
    std::vector<int> src;

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    EXPECT_TRUE(rng.empty());
}
