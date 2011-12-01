#pragma once

#include <iterator>

namespace boolinq
{
    template<typename T> 
    class IterRange
    {
    public:
        typedef typename T::iterator iterator_type;
        typedef typename T::const_iterator const_iterator_type;
        typedef std::iterator_traits<iterator_type> traits;
    
        IterRange(const T & container)
            : b(container.begin())
            , e(container.end())
        {
        }

        IterRange(const_iterator_type begin,
              const_iterator_type end)
            : b(begin)
            , e(end)
        {
        }

        bool empty() const
        {
            return (b == e);
        }

        typename traits::value_type popFront()
        {
            assert(!empty());
            const_iterator_type tmp = b;
            ++b;
            return *tmp;
        }

        typename traits::value_type popBack()
        {
            assert(!empty());
            const_iterator_type tmp = --e;
            return *tmp;
        }

        typename traits::value_type front() const
        {
            assert(!empty());
            return *b;
        }

        typename traits::value_type back() const
        {
            assert(!empty());
            return *(e-1);
        }

    private:
        const_iterator_type b;
        const_iterator_type e;
    };

    template<typename T>
    IterRange<T> range(const T & container)
    {
        return IterRange<T>(container);
    }

    template<typename T>
    IterRange<T> range(typename T::iterator b,
                   typename T::iterator e)
    {
        return IterRange<T>(b, e);
    }
}
// namespace boolinq
