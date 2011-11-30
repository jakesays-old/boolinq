#pragma once

template<typename R1, typename R2> 
class ChainRange
{
public:
    ChainRange(R1 r1, R2 r2)
        : r1(r1), r2(r2)
    {
    }
    
    bool empty() const 
    { 
        return r1.empty() && r2.empty();
    }

    typename R1::traits::value_type popFront()
    {
        assert(!r1.empty() || !r2.empty());
        return (r1.empty() ? r2 : r1).popFront();
    }

    typename R1::traits::value_type popBack()
    {
        assert(!r2.empty() || !r1.empty());
        return (r2.empty() ? r1 : r2).popEnd();
    }

    typename R1::traits::value_type front() const 
    {
        assert(!r1.empty() || !r2.empty());
        return (r1.empty() ? r2 : r1).front();
    }

    typename R1::traits::value_type back() const
    { 
        assert(!r2.empty() || !r1.empty());
        return (r2.empty() ? r1 : r2).back();
    }

private:
    R1 r1;
    R2 r2;
};

template<typename R1, typename R2>
ChainRange<R1,R2> chain(R1 r1, R2 r2)
{
    return ChainRange<R1,R2>(r1,r2);
}