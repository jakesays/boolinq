#pragma once

namespace boolinq
{
    template<typename R, typename F> 
    class WhereRange
    {
    public:
        typedef typename R::value_type value_type;
        
        WhereRange(R r, F f)
            : r(r), f(f)
        {
            seekFront();
            seekBack();
        }

        bool empty() const 
        { 
            return r.empty();
        }

        value_type popFront() 
        { 
            R tmp = r;
            r.popFront();
            seekFront();
            return tmp.front();
        }

        value_type popBack() 
        {
            R tmp = r;
            r.popBack();
            seekBack();
            return tmp.back();
        }

        value_type front() const 
        { 
            return r.front();
        }

        value_type back() const 
        { 
            return r.back();
        }

    private:
        void seekFront()
        {
            while(!r.empty() && !f(r.front()))
                r.popFront();
        }

        void seekBack()
        {
            while(!r.empty() && !f(r.back()))
                r.popBack();
        }

    private:
        R r;
        F f;
    };

    // where(where(xxx, ...), ...)

    template<typename R, typename F>
    WhereRange<R,F> where(R r, F f)
    {
        return WhereRange<R,F>(r,f);
    }
    
    // xxx.where(...).where(...)

    template<template<typename> class TLINQ, typename TContent>
    class WhereRange_mixin
    {
    public:
        template<typename F>
        TLINQ<WhereRange<TContent,F> > where(F f) const
        {
            return boolinq::where(((TLINQ<TContent>*)this)->t,f);
        }
    };
}
// namespace boolinq
