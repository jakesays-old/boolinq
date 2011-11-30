#pragma once

template<typename R>
class ReverseRange
{
public:
    ReverseRange(R r) : r(r) { }

    bool empty() const { return r.empty(); }
    typename R::traits::value_type popFront() { return r.popBack(); }
    typename R::traits::value_type popBack() { return r.popFront(); }
    typename R::traits::value_type front() const { return r.back(); }
    typename R::traits::value_type back() const { return r.front(); }

    friend template<class R> R reverse(ReverseRange<R> r); // smart needed

private:
    R r;
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