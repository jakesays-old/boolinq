#pragma once

namespace boolinq
{
    // foreach(foreach(xxx, ...), ...)

    template<typename R, typename F>
    void foreach(R r, F f)
    {
        while (!r.empty())
            f(r.popFront());
    }

    // xxx.foreach(...).foreach(...)

    template<template<typename> class TLinq, typename R>
    class Foreach_mixin
    {
    public:
        template<typename F>
        void foreach(F f) const
        {
            return boolinq::foreach(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
