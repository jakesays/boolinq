#pragma once

#include <functional>

namespace boolinq
{
    template<typename R, typename F>
    class SelectRange
    {
        template<typename F, typename TArg>
        static auto get_return_type(F * f = NULL, TArg * arg = NULL)
                    -> decltype((*f)(*arg));
    public:
        typedef decltype(get_return_type<F,typename R::value_type>()) value_type;

        SelectRange(R r, F f)
            : r(r), f(f) 
        {
        }

        bool empty() const { return r.empty(); }
        value_type popFront()    { return f(r.popFront()); }
        value_type popBack()     { return f(r.popBack());  }
        value_type front() const { return f(r.front());    }
        value_type back() const  { return f(r.back());     }

    private:
        R r;
        F f; 
    };

    // select(select(xxx, ...), ...)

    template<typename R, typename F>
    SelectRange<R,F> select(R r, F f)
    {
        return SelectRange<R,F>(r,f);
    }

    // xxx.select(...).select(...)

    template<template<typename T> class TLINQ, typename TContent>
    class SelectRange_mixin
    {
    public:
        template<typename F>
        TLINQ<SelectRange<TContent,F> > select(F f) const
        {
            return boolinq::select(((TLINQ<TContent>*)this)->t,f);
        }
    };
}
// namespace boolinq
