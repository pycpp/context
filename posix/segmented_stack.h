//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#include <boost/context/stack_context.hpp>
#include <boost/context/stack_traits.hpp>
#include <pycpp/stl/cstddef.h>
#include <pycpp/stl/new.h>

// forward declaration for splitstack-functions defined in libgcc
extern "C"
{

void*
__splitstack_makecontext(
    std::size_t,
    void*[PYCPP_CONTEXT_SEGMENTS],
    std::size_t*
);

void
__splitstack_releasecontext(
    void*[PYCPP_CONTEXT_SEGMENTS]
);

void
__splitstack_resetcontext(
    void*[PYCPP_CONTEXT_SEGMENTS]
);

void
__splitstack_block_signals_context(
    void*[PYCPP_CONTEXT_SEGMENTS],
    int* new_value, int* old_value
);

}   /* C */


PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

template <typename TraitsT>
class basic_segmented_stack
{
public:
    using traits_type = TraitsT;

    basic_segmented_stack(
        size_t size = traits_type::default_size()
    )
    noexcept:
        size_(size)
    {}

    stack_context
    allocate()
    {
        stack_context sctx;
        void* vp = __splitstack_makecontext(size_, sctx.segments_ctx, & sctx.size);
        if (vp == nullptr) {
            throw bad_alloc();
        }

        // sctx.size is already filled by __splitstack_makecontext
        sctx.sp = static_cast<char*>(vp) + sctx.size;

        int off = 0;
        __splitstack_block_signals_context(sctx.segments_ctx, & off, 0);

        return sctx;
    }

    void
    deallocate(
        stack_context& sctx
    )
    noexcept
    {
        __splitstack_releasecontext(sctx.segments_ctx);
    }

private:
    std::size_t size_;
};

// ALIASES
// ------

using segmented_stack = basic_segmented_stack<stack_traits>;

# if defined(PYCPP_USE_SEGMENTED_STACKS)
    using default_stack = segmented_stack;
# endif

PYCPP_END_NAMESPACE
