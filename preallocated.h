//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <boost/context/config.h>
#include <boost/context/stack_context.h>
#include <boost/stl/cstddef.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

struct preallocated
{
    void* sp;
    size_t size;
    stack_context sctx;

    preallocated(
        void* sp_,
        size_t size_,
        stack_context sctx_
    )
    noexcept:
        sp(sp_),
        size(size_),
        sctx(sctx_)
    {}
};


PYCPP_END_NAMESPACE
