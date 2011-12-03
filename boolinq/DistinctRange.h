#pragma once

namespace boolinq
{
    template<typename R> 
    class DistinctRange
    {
    public:
        typedef typename R::value_type value_type;

        DistinctRange(R r)
            : r(r)
            , fullRange(r)
            , leftIndex(0)
            , rightIndex(0)
        {
            if (isDuplicate(r.front(),1,0))
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
            } while (!r.empty() && isDuplicate(r.front(),1,0));
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
            } while (!r.empty() && isDuplicate(r.back(),0,1));
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
        bool isDuplicate(const value_type & value, int left, int right) const
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
                if (value == tmp.popFront())
                    return true;
            }

            tmp = fullRange;
            for(int i = 0 ; i < rightIndex + left; i++)
            {
                if (value == tmp.popBack())
                    return true;
            }

            return false;
        }

    private:
        R r;
        R fullRange;
        int leftIndex;
        int rightIndex;
    };

    // where(where(xxx, ...), ...)

    template<typename R>
    DistinctRange<R> distinct(R r)
    {
        return DistinctRange<R>(r);
    }

    // xxx.where(...).where(...)

    template<template<typename T> class TLINQ, typename TContent>
    class DistinctRange_mixin
    {
    public:
        template<typename F>
        TLINQ<DistinctRange<TContent> > distinct(F f) const
        {
            return boolinq::distinct(((TLINQ<TContent>*)this)->t,f);
        }
    };
}
// namespace boolinq
