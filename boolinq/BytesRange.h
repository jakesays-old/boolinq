#pragma once

namespace boolinq
{
    enum ByteOrder
    {
        FirstToLast,
        LastToFirst,
    };

    template<typename R, ByteOrder byteOrder> 
    class BytesRange
    {
        typedef typename R::value_type old_value_type;
        enum 
        { 
            startByte  = (byteOrder == FirstToLast) ? 0 : (sizeof(old_value_type)-1),
            finishByte = (byteOrder == FirstToLast) ? (sizeof(old_value_type)-1) : 0,
            stepByte   = (byteOrder == FirstToLast) ? 1 : -1,
        };

    public:
        typedef int value_type;

        BytesRange(R rng)
            : r(rng)
            , frontByte(startByte)
            , backByte(finishByte)
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

            if (frontByte != finishByte)
                frontByte += stepByte;
            else
            {
                frontByte = startByte;
                r.popFront();
            }   

            return tmp; 
        }

        value_type popBack()
        {
            int tmp = back();
            if(checkForEmpty())
                return tmp;

            if (backByte != startByte)
                backByte -= stepByte;
            else
            {
                backByte = finishByte;
                r.popBack();
            }   

            return tmp;
        }

        value_type front() const 
        {
            old_value_type val = r.front();
            return ((unsigned char *)&val)[frontByte];
        }

        value_type back() const  
        {
            old_value_type val = r.back();
            return ((unsigned char *)&val)[backByte];     
        }

    private:
        bool checkForEmpty()
        {
            R tmp = r;
            tmp.popFront();
            if (tmp.empty()
                && frontByte == backByte)
            {
                atEnd = true;                
            }

            return atEnd;
        }

    private:
        R r;
        int frontByte;
        int frontBit;
        int backByte;
        int backBit;
        bool atEnd;
    };

    // bytes(xxx, ...)

    template<ByteOrder byteOrder, typename R>
    BytesRange<R,byteOrder> bytes(R r)
    {
        return BytesRange<R,byteOrder>(r);
    }

    // xxx.bytes(...)

    template<template<typename> class TLinq, typename R>
    class BytesRange_mixin
    {
    public:
        template<ByteOrder byteOrder>
        TLinq<BytesRange<R,byteOrder> > bytes() const
        {
            return boolinq::bytes(((TLinq<R>*)this)->r,byteOrder);
        }
    };
}
// namespace boolinq
