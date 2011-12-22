#pragma once

#include <limits.h>

#include "BytesRange.h"

namespace boolinq
{
    enum BitOrder
    {
        HighToLow,
        LowToHigh,
    };

    template<typename R, BitOrder bitOrder> 
    class BitsRange
    {
        typedef typename R::value_type old_value_type;
        enum 
        { 
            startBit  = (bitOrder == LowToHigh) ? 0 : (CHAR_BIT-1),
            finishBit = (bitOrder == LowToHigh) ? (CHAR_BIT-1) : 0,
            stepBit   = (bitOrder == LowToHigh) ? 1 : -1,
        };

    public:
        typedef int value_type;

        BitsRange(R rng)
            : r(rng)
            , frontBit(startBit)
            , backBit(finishBit)
            , atEnd(false)
        {
        }

        bool empty() const       
        {
            return atEnd;
        }

        value_type popFront()    
        {
            int tmp = front();
            if(checkForEmpty())
                return tmp;

            if (frontBit != finishBit)
                frontBit += stepBit;
            else
            {
                frontBit = startBit;
                r.popFront();   
            }   

            return tmp; 
        }

        value_type popBack()
        {
            int tmp = back();
            if(checkForEmpty())
                return tmp;
            
            if (backBit != startBit)
                backBit -= stepBit;
            else
            {
                backBit = finishBit;
                r.popBack();  
            }   

            return tmp;
        }
        
        value_type front() const 
        {
            return (r.front() >> frontBit) & 1;
        }

        value_type back() const  
        {
            return (r.back() >> backBit) & 1;     
        }

    private:
        bool checkForEmpty()
        {
            R tmp = r;
            tmp.popFront();
            if (tmp.empty()
                && frontBit == backBit)
            {
                atEnd = true;                
            }

            return atEnd;
        }


    private:
        R r;
        int frontBit;
        int backBit;
        bool atEnd;
    };

    // bits(xxx, ...)

    template<BitOrder bitOrder, ByteOrder byteOrder, typename R>
    BitsRange<BytesRange<R,byteOrder>,bitOrder> bits(R r)
    {
        auto rng = boolinq::bytes<byteOrder>(r);
        return BitsRange<BytesRange<R,byteOrder>,bitOrder>(rng);
    }

    //template<BitOrder bitOrder, ByteOrder byteOrder, typename R>
    //BitsRange<BytesRange<R,byteOrder>,bitOrder> bits(BytesRange<R,byteOrder> r)
    //{
    //    auto rng = boolinq::bytes<byteOrder>(r);
    //    return BitsRange<BytesRange<R,byteOrder>,bitOrder>(rng);
    //}

    // xxx.bits(...)

    template<template<typename> class TLinq, typename R>
    class BitsRange_mixin
    {
    public:
        template<BitOrder bitOrder, ByteOrder byteOrder>
        TLinq<BitsRange<BytesRange<R,byteOrder>,bitOrder> > bits() const
        {
            auto rng = boolinq::bytes<byteOrder>(((TLinq<R>*)this)->r);
            return boolinq::bits<bitOrder>(rng);
        }
    };

    //template<template<typename> class TLinq, typename R, ByteOrder byteOrder>
    //class BitsRange_mixin<TLinq,BytesRange<R,byteOrder> >
    //{
    //public:
    //    template<BitOrder bitOrder, ByteOrder byteOrder>
    //    TLinq<BitsRange<BytesRange<R,byteOrder>,bitOrder> > bits() const
    //    {
    //        return boolinq::bits<bitOrder>(((TLinq<BytesRange<R,byteOrder> >*)this)->r);
    //    }
    //};
}
// namespace boolinq
