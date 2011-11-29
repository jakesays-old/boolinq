#pragma once

template<typename R>
class ReverseRange
{
    R r;

public:
    ReverseRange(R r) : r(r) { }

    bool empty() const { return r.empty(); }
    void popFront() { r.popBack(); }
    void popBack() { r.popFront(); }
    typename R::traits::reference front() const { return r.back(); }
    typename R::traits::reference back() const { return r.front(); }

    friend template<class R> R reverse(ReverseRange<R> r); // smart needed
};

template<typename R>
ReverseRange<R> reverse(R r)
{
    return ReverseRange<R>(r);
}

template<typename R>
R reverse(ReverseRange<R> r)
{
    return r.r; // smart
}