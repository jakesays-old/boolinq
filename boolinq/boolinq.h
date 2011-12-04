#pragma once

#include "IterRange.h"
#include "WhereRange.h"
#include "SelectRange.h"
#include "ReverseRange.h"
#include "OrderByRange.h"
#include "DistinctRange.h"
#include "ToList.h"
#include "ToDeque.h"
#include "ToVector.h"

namespace boolinq
{
    template<typename T>
    class Linq
        : public WhereRange_mixin<Linq,T>
        , public SelectRange_mixin<Linq,T>
        , public ReverseRange_mixin<Linq,T>
        , public OrderByRange_mixin<Linq,T>
        , public DistinctRange_mixin<Linq,T>
        , public ToList_mixin<Linq,T>
        , public ToDeque_mixin<Linq,T>
        , public ToVector_mixin<Linq,T>
    {
    public:
        typedef typename T::value_type value_type;

        Linq(const T & t)
            : t(t)
        {
        }

        bool empty() const       { return t.empty(); }
        value_type popFront()    { return t.popFront(); }
        value_type popBack()     { return t.popBack(); }
        value_type front() const { return t.front(); }
        value_type back() const  { return t.back(); }

    public:
        T t;
    };

    // from(xxx)

    template<typename X>
    Linq<IterRange<X> > from(const X & x)
    {
        return range(x);
    }

    template<typename X, const int N>
    Linq<IterRange<X[N]> > from(X (&x)[N])
    {
        return range(x);
    }

    // from<CustomLinq>(xxx)

    template<template<typename T> class TLinq, typename X>
    TLinq<IterRange<X> > from(const X & x)
    {
        return range(x);
    }

    template<template<typename T> class TLinq, typename X, const int N>
    TLinq<IterRange<X[N]> > from(const X (&x)[N])
    {
        return range(x);
    }
}
// namespace boolinq
