#pragma once

#include <list>

namespace boolinq
{
    // toList(xxx)

    template<typename R>
    std::list<typename R::value_type> toList(R r)
    {
        std::list<typename R::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toList()

    template<template<typename> class TLINQ, typename TContent>
    class ToList_mixin
    {
    public:
        std::list<typename TContent::value_type> toList() const
        {
            return boolinq::toList(((TLINQ<TContent>*)this)->t);
        }
    };
}
// namespace boolinq
