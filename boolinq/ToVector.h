#pragma once

#include <vector>

namespace boolinq
{
    // toVector(xxx)

    template<typename R>
    std::vector<typename R::traits::value_type> toVector(R r)
    {
        std::vector<typename R::traits::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toVector()

    template<template<typename T> class TLINQ, typename TContent>
    class ToVector_mixin
    {
    public:
        std::vector<typename TContent::traits::value_type> toVector() const
        {
            return boolinq::toVector(((TLINQ<TContent>*)this)->t);
        }
    };
}
// namespace boolinq