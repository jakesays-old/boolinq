#pragma once

namespace boolinq
{
    template<typename R>
    class ReverseRange
    {
    public:
        typedef typename R::value_type value_type; 
        
        ReverseRange(R r) : r(r) { }

        bool empty() const { return r.empty(); }
        value_type popFront() { return r.popBack(); }
        value_type popBack() { return r.popFront(); }
        value_type front() const { return r.back(); }
        value_type back() const { return r.front(); }

        //template<typename R2>
        //friend R2 reverse(ReverseRange<R2> r); // smart needed

    private:
        R r;
    };

    // reverse(reverse(xxx))

    template<typename R>
    ReverseRange<R> reverse(R r)
    {
        return ReverseRange<R>(r);
    }

    // Should be comennted because of test
    // with xx.reverse().reverse() notation

    //template<typename R>
    //R reverse(ReverseRange<R> r)
    //{
    //    return r.r; // smart
    //}

    // xxx.reverse().reverse()

    template<template<typename T> class TLINQ, typename TContent>
    class ReverseRange_mixin
    {
    public:
        TLINQ<ReverseRange<TContent> > reverse() const
        {
            return boolinq::reverse(((TLINQ<TContent>*)this)->t);
        }
    };
}
// namespace boolinq
