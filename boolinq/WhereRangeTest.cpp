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
    int src[] = {1,2,3,4,5,6};
    
    auto rng = range(src);
    auto dst = where(rng, [](int a){return a%2 == 1;});
    
    int ans[] = {1,3,5};

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[0], dst.popFront());
    
    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[1], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[1], dst.popFront());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[2], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[2], dst.popFront());
    
    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, IntOddBack)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a%2 == 1;});

    int ans[] = {1,3,5};

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[2], dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[1], dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[0], dst.back());
    EXPECT_EQ(ans[0], dst.popBack());

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, IntOddFrontBackFront)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a%2 == 1;});

    int ans[] = {1,3,5};

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[0], dst.popFront());
    
    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[1], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[2], dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[1], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[1], dst.popFront());

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, IntOddBackFrontBack)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a%2 == 1;});

    int ans[] = {1,3,5};

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[2], dst.back());
    EXPECT_EQ(ans[2], dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[0], dst.popFront());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[1], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[1], dst.popBack());

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, FirstLetterFront)
{
    std::string src[] =
    {
        "apple",
        "blackberry",
        "adobe",
        "microsoft",
        "nokia",
    };

    auto rng = range(src);
    auto dst = where(rng, [](std::string a){return a[0] == 'a';});

    std::string ans[] =
    {
        "apple",
        "adobe",
    };

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[0], dst.popFront());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[1], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[1], dst.popFront());

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, FirstLetterBack)
{
    std::string src[] =
    {
        "apple",
        "blackberry",
        "adobe",
        "microsoft",
        "nokia",
    };

    auto rng = range(src);
    auto dst = where(rng, [](std::string a){return a[0] == 'a';});

    std::string ans[] =
    {
        "apple",
        "adobe",
    };

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[1], dst.back());
    EXPECT_EQ(ans[1], dst.popBack());

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0], dst.front());
    EXPECT_EQ(ans[0], dst.back());
    EXPECT_EQ(ans[0], dst.popBack());

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, NameAgeLess)
{
    struct NameAge
    {
        std::string name;
        int age;
    };

    NameAge src[] =
    {
        {"man1",20},
        {"man2",15},
        {"man3",30},
        {"man4",14},
        {"man5",18},
    };

    auto rng = range(src);
    auto dst = where(rng, [](const NameAge & a){return a.age < 18;});
    
    NameAge ans[] =
    {
        {"man2",20},
        {"man4",15},
    };

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[0].name, dst.front().name);
    EXPECT_EQ(ans[1].name, dst.back().name);
    EXPECT_EQ(ans[0].name, dst.popFront().name);

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(ans[1].name, dst.front().name);
    EXPECT_EQ(ans[1].name, dst.back().name);
    EXPECT_EQ(ans[1].name, dst.popFront().name);

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, MayToOneFront)
{
    int src[] = {0,1,2};
    
    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 1;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(1, dst.front());
    EXPECT_EQ(1, dst.back());
    EXPECT_EQ(1, dst.popFront());

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, ManyToOneBack)
{
    int src[] = {0,1,2};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 1;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(1, dst.front());
    EXPECT_EQ(1, dst.back());
    EXPECT_EQ(1, dst.popBack());

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, OneToOneFront)
{
    int src[] = {5};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(5, dst.front());
    EXPECT_EQ(5, dst.back());
    EXPECT_EQ(5, dst.popFront());

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, OneToOneBack)
{
    int src[] = {5};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    EXPECT_FALSE(dst.empty());
    EXPECT_EQ(5, dst.front());
    EXPECT_EQ(5, dst.back());
    EXPECT_EQ(5, dst.popBack());

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, ManyToZero)
{
    int src[] = {0,1,2};
    
    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 5;});

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, OneToZero)
{
    int src[] = {5};
    
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
