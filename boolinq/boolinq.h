#pragma once

#include "IterRange.h"
#include "WhereRange.h"
#include "SelectRange.h"
#include "ReverseRange.h"
#include "OrderByRange.h"
#include "GroupByRange.h"
#include "DistinctRange.h"
#include "Count.h"
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
        , public GroupByRange_mixin<Linq,T>
        , public DistinctRange_mixin<Linq,T>
        , public Count_mixin<Linq,T>
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

    //////////////////////////////////////////////////////////////////////////
    // from<CustomLinq>(xxx)
    //////////////////////////////////////////////////////////////////////////

    template<template<typename T> class TLinq, typename X>
    TLinq<IterRange<typename X::const_iterator> > from(const X & x)
    {
        return range(x);
    }
    
    template<template<typename T> class TLinq, typename X, const int N>
    TLinq<IterRange<const X*> > from(const X (&x)[N])
    {
        return range(x);
    }
    
    template<template<typename T> class TLinq, typename X>
    TLinq<IterRange<X> > from(X b, X e)
    {
        return range(b,e);
    }
    
    template<template<typename T> class TLinq, typename X>
    TLinq<IterRange<const X*> > from(const X * b, const X * e)
    {
        return range(b,e);
    }

    //////////////////////////////////////////////////////////////////////////
    // from(xxx)
    //////////////////////////////////////////////////////////////////////////

    template<typename X>
    Linq<IterRange<typename X::const_iterator> > from(const X & x)
    {
        return range(x);
    }

    template<typename X, const int N>
    Linq<IterRange<const X*> > from(const X (&x)[N])
    {
        return range(x);
    }

    template<typename X>
    Linq<IterRange<X> > from(X b, X e)
    {
        return range(b,e);
    }

    template<typename X>
    Linq<IterRange<const X*> > from(const X * b, const X * e)
    {
        return range(b,e);
    }

    //////////////////////////////////////////////////////////////////////////
    // Linq equality operator for container and array
    //////////////////////////////////////////////////////////////////////////

    template<typename R, typename X>
    bool operator == (const Linq<R> & rng, const X & x)
    {
        Linq<R> tmp = rng;
        for (auto it = x.begin(); it != x.end(); ++it)
        {
            if (tmp.empty())
                return false;
            if (tmp.popFront() != *it)
                return false;
        }

        return tmp.empty();
    }

    template<typename R, typename X>
    bool operator == (const X & x, const Linq<R> & rng)
    {
        return rng == x;
    }

    template<typename R, typename X, const int N>
    bool operator == (const Linq<R> & rng, const X (&x)[N])
    {
        Linq<R> tmp = rng;
        for (int i = 0; i < N; i++)
        {
            if (tmp.empty())
                return false;
            if (tmp.popFront() != x[i])
                return false;
        }

        return tmp.empty();
    }

    template<typename R, typename X, const int N>
    bool operator == (const X (&x)[N], const Linq<R> & rng)
    {
        return rng == x;
    }
}
// namespace boolinq
