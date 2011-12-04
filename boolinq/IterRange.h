#pragma once

#include <iterator>

namespace boolinq
{
    template<typename TContainer>
    struct container_traits 
    {
        typedef typename TContainer::const_iterator const_iter_type;
        typedef typename TContainer::iterator iter_type;
    };

    // Array template specializations

    template<typename T, const int N> 
    struct container_traits<T[N]> 
    {
        typedef const T * const_iter_type;
        typedef T * iter_type;
    };

    template<typename T, const int N> 
    struct container_traits<const T[N]> 
    {
        typedef const T * const_iter_type;
        typedef T * iter_type;
    };

    // Pointer template specializations

    template<typename T> 
    struct container_traits<const T*> 
    {
        typedef const T * const_iter_type;
        typedef T * iter_type;
    };

    template<typename T> 
    struct container_traits<T*> 
    {
        typedef const T * const_iter_type;
        typedef T * iter_type;
    };


    //////////////////////////////////////////////////////////////////////

    template<typename T> 
    class IterRange
    {
        typedef typename container_traits<T>::const_iter_type iter_type;
        typedef std::iterator_traits<iter_type> traits;

    public:
        typedef typename traits::value_type value_type;
        
        IterRange(const T & container)
            : b(container.begin())
            , e(container.end())
        {
        }

        IterRange(iter_type begin,
                  iter_type end)
            : b(begin)
            , e(end)
        {
        }

        bool empty() const
        {
            return (b == e);
        }

        value_type popFront()
        {
            assert(!empty());
            iter_type tmp = b;
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
            iter_type tmp = e;
            --tmp;
            return *tmp;
        }

    private:
        iter_type b;
        iter_type e;
    };

    //////////////////////////////////////////////////////////////////////

    // std::vector<xxx> vec;
    // range(vec)

    template<typename T>
    IterRange<T> range(const T & container)
    {
        return IterRange<T>(container);
    }
    
    // int vec[] = {1,2,3,4,5};
    // range(vec)

    template<typename T, const int N>
    IterRange<T[N]> range(T (&arr)[N])
    {
        return IterRange<T[N]>((T*)arr, (T*)arr+N);
    }

    // std::vector<xxx> vec;
    // range(vec.begin(), vec.end())

    template<typename T>
    IterRange<T> range(typename T::const_iterator b,
                       typename T::const_iterator e)
    {
        return IterRange<T>(b, e);
    }

    // int * xxx = {1,2,3,4,5};
    // range(xxx, xxx+5)

    template<typename T>
    IterRange<T*> range(T * b,
                        T * e)
    {
        return IterRange<T*>(b, e);
    }
}
// namespace boolinq
