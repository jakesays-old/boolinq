#pragma once

#include "IterRange.h"
#include "WhereRange.h"
#include "SelectRange.h"
#include "OrderByRange.h"
#include "ToList.h"
#include "ToDeque.h"
#include "ToVector.h"

namespace boolinq
{
    template<typename T>
    class Linq
        : public WhereRange_mixin<Linq,T>
        , public SelectRange_mixin<Linq,T>
        , public OrderByRange_mixin<Linq,T>
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

        bool empty() const { return t.empty(); }
        typename T::value_type popFront()    { return t.popFront(); }
        typename T::value_type popBack()     { return t.popBack(); }
        typename T::value_type front() const { return t.front(); }
        typename T::value_type back() const  { return t.back(); }

    public:
        T t;
    };

    template<typename X>
    Linq<IterRange<X> > from(const X & x)
    {
        return IterRange<X>(x);
    }

    template<typename X, template<typename T> class TLinq>
    TLinq<IterRange<X> > from(const X & x)
    {
        return IterRange<X>(x);
    }
}
// namespace boolinq
