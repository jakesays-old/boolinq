#pragma once

namespace boolinq
{
    template<typename R, typename F>
    class SelectRange
    {
    public:
        SelectRange(R r, F & f)
            : r(r), f(f) 
        {
        }

        bool empty() const 
        { 
            return r.empty();
        }

        decltype(f(typename R::traits::value_type)) popFront() 
        { 
            return f(r.popFront());
        }

        decltype(f(typename R::traits::value_type)) popBack() 
        {
            return f(r.popBack());
        }

        decltype(f(typename R::traits::value_type)) front() const 
        { 
            return f(r.front());
        }

        decltype(f(typename R::traits::value_type)) back() const 
        {
            return f(r.back());
        }

    private:
        R r;
        F & f;
    };

    template<typename R, typename F>
    SelectRange<R,F> select(R r, F f)
    {
        return SelectRange<R,F>(r,f);
    }
}
// namespace boolinq
