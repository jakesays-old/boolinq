#pragma once

#include <functional>

namespace boolinq
{
    template<typename F, typename TArg>
    static auto get_return_type(F * f = NULL, TArg * arg = NULL)
                -> decltype((*f)(*arg));

    template<typename R, typename F>
    class SelectRange
    {
    public:
        typedef decltype(get_return_type<F,typename R::value_type>()) value_type;
        
        SelectRange(R r, F f)
            : r(r), f(f) 
        {
        }

        bool empty() const 
        { 
            return r.empty();
        }

        value_type popFront()
        { 
            assert(!empty());
            return f(r.popFront());
        }

        value_type popBack() 
        {
            assert(!empty());
            return f(r.popBack());
        }

        value_type front() const 
        { 
            assert(!empty());
            return f(r.front());
        }

        value_type back() const 
        {
            assert(!empty());
            return f(r.back());
        }

    private:
        R r;
        F f; 
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
        TLINQ<SelectRange<TContent,F> > select(F f) const
        {
            return boolinq::select(((TLINQ<TContent>*)this)->t,f);
        }
    };
}
// namespace boolinq
