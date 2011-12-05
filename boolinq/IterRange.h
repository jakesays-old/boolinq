#pragma once

#include <iterator>
#include <vector>

namespace boolinq
{
    template<typename TContainer>
    struct container_traits 
    {
        typedef typename TContainer::const_iterator const_iterator_type;
        typedef typename TContainer::iterator iter_type;
    };

    // Array template specializations

    template<typename T, const int N> 
    struct container_traits<const T[N]> 
    {
        typedef const T * const_iterator_type;
        typedef T * iter_type;
    };

    //template<typename T, const int N> 
    //struct container_traits<T[N]> 
    //{
    //    typedef const T * const_iterator_type;
    //    typedef T * iter_type;
    //};

    // Pointer template specializations

    template<typename T> 
    struct container_traits<const T*> 
    {
        typedef const T * const_iterator_type;
        typedef T * iter_type;
    };

    //template<typename T> 
    //struct container_traits<T*> 
    //{
    //    typedef const T * const_iterator_type;
    //    typedef T * iter_type;
    //};

    //////////////////////////////////////////////////////////////////////

    template<typename T> 
    class IterRange
    {
        typedef typename container_traits<T>::const_iterator_type const_iterator_type;
        typedef std::iterator_traits<const_iterator_type> traits;

    public:
        typedef typename traits::value_type value_type;
        
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

        value_type popFront()
        {
            assert(!empty());
            const_iterator_type tmp = b;
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
            const_iterator_type tmp = e;
            --tmp;
            return *tmp;
        }

    private:
        const_iterator_type b;
        const_iterator_type e;
    };

    //////////////////////////////////////////////////////////////////////

    // std::vector<xxx> vec;
    // range(vec)

    template<typename T>
    IterRange<T> range(const T & container)
    {
        return IterRange<T>(container);
    }
    
    //

    // int vec[] = {1,2,3,4,5};
    // range(vec)

    template<typename T, const int N>
    IterRange<const T[N]> range(const T (&arr)[N])
    {
        return IterRange<const T[N]>((const T*)arr,(const T*)arr+N);
    }
    
    //template<typename T, const int N>
    //IterRange<T[N]> range(T (&arr)[N])
    //{
    //    return IterRange<T[N]>((T*)arr,(T*)arr+N);
    //}

    //

    // std::vector<xxx> vec;
    // range(vec.begin(), vec.end())

    //template<typename T>
    //IterRange<T> range(typename T::const_iterator b,
    //                   typename T::const_iterator e)
    //{
    //    return IterRange<T>(b,e);
    //}
    
    //template<typename T>
    //IterRange<T> range(typename T::iterator b,
    //                   typename T::iterator e)
    //{
    //    return IterRange<T>(b,e);
    //}

    //

    // int * xxx = {1,2,3,4,5};
    // range(xxx, xxx+5)

    template<typename T>
    IterRange<const T*> range(const T * b,
                              const T * e)
    {
        return IterRange<const T*>(b,e);
    }

    //template<typename T>
    //IterRange<T*> range(T * b,
    //                    T * e)
    //{
    //    return IterRange<T*>(b,e);
    //}
}
// namespace boolinq
