#pragma once

namespace boolinq
{
    // all(xxx)

    template<typename R>
    bool all(R r)
    {
        while (!r.empty())
            if (!r.popFront())
                return false;
        return true;
    }

    template<typename R, typename F>
    bool all(R r, F f)
    {
        while (!r.empty())
            if (!f(r.popFront()))
                return false;
        return true;
    }

    // xxx.all()

    template<template<typename> class TLinq, typename R>
    class All_mixin
    {
    public:
        bool all() const
        {
            return boolinq::all(((TLinq<R>*)this)->r);
        }

        template<typename F>
        bool all(F f) const
        {
            return boolinq::all(((TLinq<R>*)this)->r,f);
        }
    };
}
