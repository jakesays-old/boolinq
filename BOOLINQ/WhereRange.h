#pragma once

template<typename R, typename F> 
class WhereRange
{
public:
    typedef typename R::iterator_type iterator_type;
    typedef typename R::const_iterator_type const_iterator_type;
    typedef typename R::traits traits;
    
    WhereRange(R r, F & f)
        : r(r), f(f)
    {
        while(!r.empty() && !f(r.front()))
            r.popFront();
        while(!r.empty() && !f(r.back()))
            r.popBack();
    }

    bool empty() const 
    { 
        return r.empty();
    }

    typename traits::value_type popFront() 
    { 
        R tmp = r;
        r.popFront();
        while(!r.empty() && !f(r.front()))
            r.popFront();
        return tmp.front();
    }

    typename traits::value_type popBack() 
    {
        R tmp = r;
        r.popBack();
        while(!r.empty() && !f(r.back()))
            r.popBack();
        return tmp.back();
    }

    typename traits::value_type front() const 
    { 
        return r.front();
    }

private:
    R r;
    F & f;
};

template<typename R, typename F>
WhereRange<R,F> where(R r, F f)
{
    return WhereRange<R,F>(r,f);
}