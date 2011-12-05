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

    //////////////////////////////////////////////////////////////////////////
    // from<CustomLinq>(xxx)
    //////////////////////////////////////////////////////////////////////////

    template<template<typename T> class TLinq, typename X>
    TLinq<IterRange<X> > from(const X & x)
    {
        return range(x);
    }

    template<template<typename T> class TLinq, typename X, const int N>
    TLinq<IterRange<const X[N]> > from(const X (&x)[N])
    {
        return range(x);
    }

    //template<template<typename T> class TLinq, typename X, const int N>
    //TLinq<IterRange<X[N]> > from(X (&x)[N])
    //{
    //    return range(x);
    //}

    //template<template<typename T> class TLinq, typename X>
    //TLinq<IterRange<X> > from(typename X::const_iterator b,
    //                          typename X::const_iterator e)
    //{
    //    return range(b,e);
    //}

    template<template<typename T> class TLinq, typename X>
    TLinq<IterRange<const X*> > from(const X * b,
                                     const X * e)
    {
        return range(b,e);
    }

    //template<template<typename T> class TLinq, typename X>
    //TLinq<IterRange<X*> > from(X * b,
    //                           X * e)
    //{
    //    return range(b,e);
    //}

    //////////////////////////////////////////////////////////////////////////
    // from(xxx)
    //////////////////////////////////////////////////////////////////////////

    template<typename X>
    Linq<IterRange<X> > from(const X & x)
    {
        return from<Linq>(x);
    }

    template<typename X, const int N>
    Linq<IterRange<const X[N]> > from(const X (&x)[N])
    {
        return from<Linq>(x);
    }

    //template<typename X, const int N>
    //Linq<IterRange<X[N]> > from(X (&x)[N])
    //{
    //    return from<Linq>(x);
    //}

    //template<typename X>
    //Linq<IterRange<X> > from(typename X::const_iterator b,
    //                         typename X::const_iterator e)
    //{
    //    return from<Linq>(b, e);
    //}

    template<typename X>
    Linq<IterRange<const X*> > from(const X * b,
                                    const X * e)
    {
        return from<Linq>(b,e);
    }

    //template<typename X>
    //Linq<IterRange<X*> > from(X * b,
    //                          X * e)
    //{
    //    return from<Linq>(b,e);
    //}
}
// namespace boolinq
