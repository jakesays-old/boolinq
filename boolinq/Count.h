#pragma once

namespace boolinq
{
    // count(xxx) and count(xxx,lambda)

    template<typename R, typename F>
    int count(R r, F f)
    {
        int index = 0;
        for (; !r.empty(); r.popFront())
            if (f(r.front()))
                index++;
        return index;
    }

    template<typename R>
    int count(R r)
    {
        typedef typename R::value_type value_type;
        return count(r,[](const value_type &){return true;});
    }

    // xxx.count() and xxx.count(lambda)

    template<template<typename> class TLinq, typename R>
    class Count_mixin
    {
    public:
        int count() const
        {
            return boolinq::count(((TLinq<R>*)this)->r);
        }

        template<typename F>
        int count(F f) const
        {
            return boolinq::count(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq