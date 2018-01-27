//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#include <pycpp/stl/cstddef.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

#if defined(PYCPP_USE_SEGMENTED_STACKS)     // PYCPP_USE_SEGMENTED_STACKS

struct stack_context
{
    using segments_context = void*[BOOST_CONTEXT_SEGMENTS];

    size_t size = 0;
    void* sp = nullptr;
    segments_context segments_ctx;

    stack_context() = default;
};

#else                                       // !PYCPP_USE_SEGMENTED_STACKS

struct stack_context
{
    size_t size = 0;
    void* sp = nullptr;

    stack_context() = default;
};

#endif                                      // PYCPP_USE_SEGMENTED_STACKS

PYCPP_END_NAMESPACE
