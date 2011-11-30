#pragma once

template<typename R, typename F>
class SelectRange
{
    R r;
    F & f;

public:
    SelectRange(R r, F & f)
        : r(r), f(f) 
    {
    }

    bool empty() const 
    { 
        return r.empty();
    }

    void popFront() 
    { 
        r.popFront();
    }

    void popBack() 
    {
        r.popBack();
    }

    decltype(f(typename R::traits::reference)) front() const 
    { 
        return f(r.front());
    }

    decltype(f(typename R::traits::reference)) back() const 
    {
        return f(r.back());
    }
};

template<typename R, typename F>
SelectRange<R,F> select(R r, F f)
{
    return SelectRange<R,F>(r,f);
}