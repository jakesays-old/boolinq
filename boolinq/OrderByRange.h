#pragma once

namespace boolinq
{
    template<typename T>
    struct JustReturn
    {
        T operator()(const T & a) const
        {
            return a;
        }
    };

    template<typename R, typename F = JustReturn<typename R::value_type> > 
    class OrderByRange
    {
    public:
        typedef typename R::value_type value_type;

        OrderByRange(R r, F f = JustReturn<typename R::value_type>())
            : r(r), f(f)
            , minValue(r)
            , maxValue(r)
            , minIndex(-1)
            , maxIndex(-1)
            , atEnd(false)
        {
            seekMinFirstTime();
            seekMaxFirstTime();
            atEnd = r.empty();
        }

        bool empty() const 
        { 
            return atEnd;
        }

        value_type popFront() 
        { 
            R tmp = minValue;
            seekMin();
            return tmp.front();
        }

        value_type popBack() 
        {
            R tmp = maxValue;
            seekMax();
            return tmp.front();
        }

        value_type front() const 
        { 
            return minValue.front();
        }

        value_type back() const 
        { 
            return maxValue.front();
        }

    private:
        R minValue;
        R maxValue;
        int minIndex;
        int maxIndex;
        bool atEnd;

        void seekMinFirstTime()
        {
            R cur_value = r;
            R min_value = r;
            int cur_index = 0;
            int min_index = 0;

            while(!cur_value.empty())
            {
                if (f(cur_value.front()) < f(min_value.front()))
                {
                    min_value = cur_value;
                    min_index = cur_index;
                }

                cur_value.popFront();
                cur_index++;
            }

            minValue = min_value;
            minIndex = min_index;
        }

        void seekMaxFirstTime()
        {
            R cur_value = r;
            R max_value = r;
            int cur_index = 0;
            int max_index = 0;

            while(!cur_value.empty())
            {
                if (f(cur_value.front()) > f(max_value.front()))
                {
                    max_value = cur_value;
                    max_index = cur_index;
                }

                cur_value.popFront();
                cur_index++;
            }

            maxValue = max_value;
            maxIndex = max_index;
        }

        void seekMin()
        {
            R cur_value = r;
            R min_value = r;
            int cur_index = 0;
            int min_index = -1;

            while(!cur_value.empty())
            {
                if (min_index == -1
                    && f(cur_value.front()) < f(minValue.front()))
                {
                    min_value = cur_value;
                    min_index = cur_index;
                }

                if (f(cur_value.front()) == f(minValue.front())
                    && cur_index > minIndex)
                {
                    min_value = cur_value;
                    min_index = cur_index;
                    break;
                }

                if (f(cur_value.front()) > f(minValue.front())
                    && f(cur_value.front()) < f(min_value.front()))
                {
                    min_value = cur_value;
                    min_index = cur_index;
                }

                cur_value.popFront();
                cur_index++;
            }

            atEnd = (min_index == -1);
            minValue = min_value;
            minIndex = min_index;
        }

        void seekMax()
        {
            R cur_value = r;
            R max_value = r;
            int cur_index = 0;
            int max_index = -1;

            while(!cur_value.empty())
            {
                if (max_index == -1
                    && f(cur_value.front()) > f(maxValue.front()))
                {
                    max_value = cur_value;
                    max_index = cur_index;
                }

                if (f(cur_value.front()) == f(maxValue.front())
                    && cur_index > maxIndex)
                {
                    max_value = cur_value;
                    max_index = cur_index;
                    break;
                }

                if (f(cur_value.front()) < f(maxValue.front())
                    && f(cur_value.front()) > f(max_value.front()))
                {
                    max_value = cur_value;
                    max_index = cur_index;
                }

                cur_value.popFront();
                cur_index++;
            }

            atEnd = (max_index == -1);
            maxValue = max_value;
            maxIndex = max_index;
        }

    private:
        R r;
        F f;
    };

    // orderBy(orderBy(xxx, ...), ...)

    template<typename R>
    OrderByRange<R> orderBy(R r)
    {
        return OrderByRange<R>(r);
    }

    template<typename R, typename F>
    OrderByRange<R,F> orderBy(R r, F f)
    {
        return OrderByRange<R,F>(r,f);
    }

    // xxx.orderBy(...).orderBy(...)

    template<template<typename> class TLinq, typename R>
    class OrderByRange_mixin
    {
    public:
        TLinq<OrderByRange<R> > orderBy() const
        {
            return boolinq::orderBy(((TLinq<R>*)this)->r);
        }

        template<typename F>
        TLinq<OrderByRange<R,F> > orderBy(F f) const
        {
            return boolinq::orderBy(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
