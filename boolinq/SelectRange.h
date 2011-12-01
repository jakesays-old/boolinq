#pragma once

#include <functional>

namespace boolinq
{
    template<typename R, typename F>
    static auto get_return_type(R * r = NULL, F * f = NULL)
                -> decltype((*f)(r->front()));

    template<typename R, typename F>
    class SelectRange
    {
        typedef typename R::traits::value_type prev_value_type;

    public:
        typedef typename R::iterator_type iterator_type;
        typedef typename R::const_iterator_type const_iterator_type;
        typedef typename R::traits traits;
        
        SelectRange(R r, F & f)
            : r(r), f(f) 
        {
        }

        bool empty() const 
        { 
            return r.empty();
        }

        decltype(get_return_type<R,F>()) popFront()
        { 
            return f(r.popFront());
        }

        decltype(get_return_type<R,F>()) popBack() 
        {
            return f(r.popBack());
        }

        decltype(get_return_type<R,F>()) front() const 
        { 
            return f(r.front());
        }

        decltype(get_return_type<R,F>()) back() const 
        {
            return f(r.back());
        }

    private:
        R r;
        F & f; 
    };

    // select(select(xxx, ...), ...)

    template<typename R, typename F>
    SelectRange<R,F> select(R r, F f)
    {
        return SelectRange<R,F>(r,f);
    }

    // xxx.select(...).select(...)

    template<template<typename T> class TLINQ, typename TContent>
    class SelectRange_mixin
    {
    public:
        template<typename F>
        TLINQ<SelectRange<TContent,F> > select(F & f) const
        {
            return boolinq::select(((TLINQ<TContent>*)this)->t,f);
        }
    };
}
// namespace boolinq
