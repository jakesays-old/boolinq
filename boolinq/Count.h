#pragma once

namespace boolinq
{
    // count(xxx)

    template<typename R>
    int count(R r)
    {
        int index = 0;
        for (; !r.empty(); r.popFront())
            index++;
        return index;
    }

    // xxx.count()

    template<template<typename T> class TLINQ, typename TContent>
    class Count_mixin
    {
    public:
        int count() const
        {
            return boolinq::count(((TLINQ<TContent>*)this)->t);
        }
    };
}
// namespace boolinq