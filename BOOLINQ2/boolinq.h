#pragma once

#include "IteratorRange.h"
#include "WhereRange.h"
#include "ExtractRange.h"

namespace boolinq
{
    template<typename T>
    class Linq
        : public WhereRange_linq<Linq,T>
    {
    public:
        typedef typename T::iterator_type iterator_type;
        typedef typename T::const_iterator_type const_iterator_type;
        typedef typename T::traits traits;

        Linq(const T & t)
            : t(t)
        {
        }

        bool empty() const { return t.empty(); }
        typename T::traits::value_type popFront() { return t.popFront(); }
        typename T::traits::value_type popBack() { return t.popBack(); }
        typename T::traits::value_type front() const { return t.front(); }
        typename T::traits::value_type back() const { return t.back(); }

    public:
        T t;
    };

    template<typename X>
    Linq<IteratorRange<X> > from(const X & x)
    {
        return IteratorRange<X>(x);
    }
}
// namespace boolinq
