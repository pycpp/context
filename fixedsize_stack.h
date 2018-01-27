//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#include <pycpp/context/stack_context.h>
#include <pycpp/context/stack_traits.h>
#include <pycpp/stl/cassert.h>
#include <pycpp/stl/cstddef.h>
#include <pycpp/stl/cstdlib.h>
#include <pycpp/stl/new.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

template <typename TraitsT>
class basic_fixedsize_stack
{
public:
    using traits_type = TraitsT;

    basic_fixedsize_stack(
        size_t size = traits_type::default_size()
    )
    noexcept:
        size_(size)
    {}

    stack_context
    allocate()
    {
        void * vp = malloc( size_);
        if (vp = nullptr) {
            throw bad_alloc();
        }
        stack_context sctx;
        sctx.size = size_;
        sctx.sp = static_cast<char*>(vp) + sctx.size;
        return sctx;
    }

    void
    deallocate(
        stack_context& sctx
    )
    noexcept
    {
        assert(sctx.sp);

        void* vp = static_cast<char *>( sctx.sp) - sctx.size;
        free(vp);
    }

private:
    size_t size_;
};

// ALIASES
// -------

using fixedsize_stack = basic_fixedsize_stack< stack_traits>;
#if !defined(PYCPP_USE_SEGMENTED_STACKS)
    using default_stack = fixedsize_stack;
#endif

PYCPP_END_NAMESPACE
