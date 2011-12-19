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
void CheckRangeAll(R dst, T (&ans)[N], F f)
{
    CheckRangeFront(dst, ans, f);
    CheckRangeBack(dst, ans, f);
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
void CheckRangeAll(R dst, T (&ans)[N])
{
    CheckRangeFront(dst, ans);
    CheckRangeBack(dst, ans);
}

//////////////////////////////////////////////////////////////////////////