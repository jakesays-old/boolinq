#pragma once

#include <deque>

namespace boolinq
{
    // toVector(xxx)

    template<typename R>
    std::deque<typename R::traits::value_type> toDeque(R r)
    {
        std::deque<typename R::traits::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toVector()

    template<template<typename T> class TLINQ, typename TContent>
    class ToDeque_mixin
    {
    public:
        std::deque<typename TContent::traits::value_type> toDeque() const
        {
            return boolinq::toDeque(((TLINQ<TContent>*)this)->t);
        }
    };
}
// namespace boolinq