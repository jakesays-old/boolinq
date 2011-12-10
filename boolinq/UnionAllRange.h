#pragma once

#include <type_traits>

namespace boolinq
{
    template<typename R1, typename R2> 
    class UnionAllRange
    {
        static_assert(std::tr1::is_same<typename R1::value_type,
                                        typename R2::value_type>::value,
                      "Error unioning ranges with different value types");

    public:
        typedef typename R1::value_type value_type;

        UnionAllRange(R1 r1, R2 r2)
            : r1(r1), r2(r2)
        {
        }
    
        bool empty() const 
        { 
            return r1.empty() && r2.empty();
        }

        value_type popFront()
        {
            if (r1.empty())
                return r2.popFront();
            return r1.popFront();
        }

        value_type popBack()
        {
            if (r2.empty())
                return r1.popBack();
            return r2.popBack();
        }

        value_type front() const 
        {
            if (r1.empty())
                return r2.front();
            return r1.front();
        }

        value_type back() const
        { 
            if (r2.empty())
                return r1.back();
            return r2.back();
        }

    private:
        R1 r1;
        R2 r2;
    };

    /// chain(chain(xxx,yyy),zzz)

    template<typename R1, typename R2>
    UnionAllRange<R1,R2> unionAll(R1 r1, R2 r2)
    {
        return UnionAllRange<R1,R2>(r1,r2);
    }
}
// namespace boolinq
