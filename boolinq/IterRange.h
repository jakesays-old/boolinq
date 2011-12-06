#pragma once

#include <iterator>
#include <vector>

namespace boolinq
{
    template<typename TIter> 
    class IterRange
    {
    public:
        typedef typename std::iterator_traits<TIter>::value_type value_type;
        
        template<typename TContainer>
        IterRange(const TContainer & container)
            : b(container.begin())
            , e(container.end())
        {
        }

        template<typename TContainer, const int N>
        IterRange(const TContainer (&arr)[N])
            : b((const value_type*)arr)
            , e((const value_type*)arr + N)
        {
        }

        IterRange(TIter b,
                  TIter e)
            : b(b)
            , e(e)
        {
        }

        bool empty() const
        {
            return (b == e);
        }

        value_type popFront()
        {
            assert(!empty());
            TIter tmp = b;
            ++b;
            return *tmp;
        }

        value_type popBack()
        {
            assert(!empty());
            return *(--e);
        }

        value_type front() const
        {
            assert(!empty());
            return *b;
        }

        value_type back() const
        {
            assert(!empty());
            TIter tmp = e;
            --tmp;
            return *tmp;
        }

    private:
        TIter b;
        TIter e;
    };

    //////////////////////////////////////////////////////////////////////

    template<typename T>
    IterRange<typename T::const_iterator> range(const T & container)
    {
        return IterRange<typename T::const_iterator>(container);
    }
    
    template<typename T, const int N>
    IterRange<const T*> range(const T (&arr)[N])
    {
        return IterRange<const T*>(arr);
    }

    template<typename T>
    IterRange<T> range(T b, T e)
    {
        return IterRange<T>(b,e);
    }
    
    template<typename T>
    IterRange<const T*> range(const T * b, const T * e)
    {
        return IterRange<const T*>(b,e);
    }
}
// namespace boolinq
