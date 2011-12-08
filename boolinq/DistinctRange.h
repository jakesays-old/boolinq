#pragma once

namespace boolinq
{
    template<typename T>
    struct JustReturn_dist
    {
        T operator()(const T & a) const
        {
            return a;
        }
    };

    template<typename R, typename F = JustReturn_dist<typename R::value_type>> 
    class DistinctRange
    {
    public:
        typedef typename R::value_type value_type;

        DistinctRange(R r, F f = JustReturn_dist<typename R::value_type>())
            : r(r), f(f)
            , fullRange(r)
            , leftIndex(0)
            , rightIndex(0)
        {
            if (isDuplicate(f(r.front()),1,0))
                popFront();
        }

        bool empty() const 
        { 
            return r.empty();
        }

        value_type popFront() 
        { 
            assert(!empty());
            R tmp = r;
            do 
            {
                r.popFront();
                leftIndex++;
            } while (!r.empty() && isDuplicate(f(r.front()),1,0));
            return tmp.front();
        }

        value_type popBack() 
        {
            assert(!empty());
            R tmp = r;
            do
            {
                r.popBack();
                rightIndex++;
            } while (!r.empty() && isDuplicate(f(r.back()),0,1));
            return tmp.back();
        }

        value_type front() const 
        { 
            assert(!empty());
            return r.front();
        }

        value_type back() const 
        { 
            assert(!empty());
            return r.back();
        }

    private:
        template<typename T>
        bool isDuplicate(const T & value, int left, int right) const
        {
            R dr = r;
            dr.popFront();
            if (dr.empty())
            {
                left = 0;
                right = 0;
                return false;
            }

            R tmp = fullRange;
            for(int i = 0 ; i < leftIndex + right; i++)
            {
                if (value == f(tmp.popFront()))
                    return true;
            }

            tmp = fullRange;
            for(int i = 0 ; i < rightIndex + left; i++)
            {
                if (value == f(tmp.popBack()))
                    return true;
            }

            return false;
        }

    private:
        R r;
        F f;

        R fullRange;
        int leftIndex;
        int rightIndex;
    };

    // distinct(distinct(xxx))

    template<typename R>
    DistinctRange<R> distinct(R r)
    {
        return DistinctRange<R>(r);
    }

    template<typename R, typename F>
    DistinctRange<R,F> distinct(R r, F f)
    {
        return DistinctRange<R,F>(r,f);
    }

    // xxx.distinct().distinct()

    template<template<typename T> class TLINQ, typename TContent>
    class DistinctRange_mixin
    {
    public:
        TLINQ<DistinctRange<TContent> > distinct() const
        {
            return boolinq::distinct(((TLINQ<TContent>*)this)->t);
        }

        template<typename F>
        TLINQ<DistinctRange<TContent,F> > distinct(F f) const
        {
            return boolinq::distinct(((TLINQ<TContent>*)this)->t,f);
        }
    };
}
// namespace boolinq
