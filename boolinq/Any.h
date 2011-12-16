#pragma once

namespace boolinq
{
    // any(xxx) and any(xxx,lambda)

    template<typename R>
    bool any(R r)
    {
        while (!r.empty())
            if (r.popFront())
                return true;
        return false;
    }

    template<typename R, typename F>
    bool any(R r, F f)
    {
        while (!r.empty())
            if (f(r.popFront()))
                return true;
        return false;
    }

    // xxx.any() and xxx.any(lambda)

    template<template<typename> class TLinq, typename R>
    class Any_mixin
    {
    public:
        bool any() const
        {
            return boolinq::any(((TLinq<R>*)this)->r);
        }

        template<typename F>
        bool any(F f) const
        {
            return boolinq::any(((TLinq<R>*)this)->r,f);
        }
    };
}
