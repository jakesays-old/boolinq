#pragma once

//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N, typename F>
void CheckRangeFront(R dst, T (&ans)[N], F f)
{
    for (int i = 0; i < N; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[i]),   f(dst.front()));
        EXPECT_EQ(f(ans[N-1]), f(dst.back()));
        EXPECT_EQ(f(ans[i]),   f(dst.popFront()));
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeBack(R dst, T (&ans)[N], F f)
{
    for (int i = N; i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[0]),   f(dst.front()));
        EXPECT_EQ(f(ans[i-1]), f(dst.back()));
        EXPECT_EQ(f(ans[i-1]), f(dst.popBack()));
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeTwisted(R dst, T (&ans)[N], F f, int bit)
{
    int b = 0;
    int e = N-1;

    for (int i = 0; i < N; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[b]), f(dst.front()));
        EXPECT_EQ(f(ans[e]), f(dst.back()));

        if (i % 2 == bit)
            EXPECT_EQ(f(ans[b++]), f(dst.popFront()));
        else
            EXPECT_EQ(f(ans[e--]), f(dst.popBack()));

        bit = 1 - bit;  // reverse bit
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeFrontBack(R dst, T (&ans)[N], F f)
{
    CheckRangeTwisted(dst, ans, f, 0);
}

template<typename R, typename T, int N, typename F>
void CheckRangeBackFront(R dst, T (&ans)[N], F f)
{
    CheckRangeTwisted(dst, ans, f, 1);
}

template<typename R, typename T, int N, typename F>
void CheckRangeAll(R dst, T (&ans)[N], F f)
{
    CheckRangeFront(dst, ans, f);
    CheckRangeBack(dst, ans, f);
    CheckRangeFrontBack(dst, ans, f);
    CheckRangeBackFront(dst, ans, f);
}

//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N>
void CheckRangeFront(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeFront(dst, ans, [](const value_type & a){return a;});
}

template<typename R, typename T, int N>
void CheckRangeBack(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeBack(dst, ans, [](const value_type & a){return a;});
}

template<typename R, typename T, int N>
void CheckRangeFrontBack(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeFrontBack(dst, ans, [](const value_type & a){return a;});
}

template<typename R, typename T, int N>
void CheckRangeBackFront(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeBackFront(dst, ans, [](const value_type & a){return a;});
}

template<typename R, typename T, int N>
void CheckRangeAll(R dst, T (&ans)[N])
{
    typedef typename R::value_type value_type;
    CheckRangeAll(dst, ans, [](const value_type & a){return a;});
}

//////////////////////////////////////////////////////////////////////////