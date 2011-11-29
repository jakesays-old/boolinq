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

    void popFront() 
    { 
        r.popFront();
        while(!r.empty() && !f(r.front()))
            r.popFront();
    }

    void popBack() 
    {
        r.popBack();
        while(!r.empty() && !f(r.back()))
            r.popBack();
    }

    typename traits::value_type front() const 
    { 
        return r.front();
    }

    typename traits::value_type back() const 
    {
        return r.back(); 
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