#pragma once

namespace boolinq
{
    template<typename R1, typename R2> 
    class ChainRange
    {
    public:
        typedef R1::value_type value_type;

        ChainRange(R1 r1, R2 r2)
            : r1(r1), r2(r2)
        {
        }
    
        bool empty() const 
        { 
            return r1.empty() && r2.empty();
        }

        value_type popFront()
        {
            return (r1.empty() ? r2 : r1).popFront();
        }

        value_type popBack()
        {
            return (r2.empty() ? r1 : r2).popEnd();
        }

        value_type front() const 
        {
            return (r1.empty() ? r2 : r1).front();
        }

        value_type back() const
        { 
            return (r2.empty() ? r1 : r2).back();
        }

    private:
        R1 r1;
        R2 r2;
    };

    /// chain(chain(xxx,yyy),zzz)

    template<typename R1, typename R2>
    ChainRange<R1,R2> chain(R1 r1, R2 r2)
    {
        return ChainRange<R1,R2>(r1,r2);
    }
}
// namespace boolinq
