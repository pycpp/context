//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/stl/cstddef.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

struct stack_traits
{
    static bool is_unbounded() noexcept;
    static size_t page_size() noexcept;
    static size_t default_size() noexcept;
    static size_t minimum_size() noexcept;
    static size_t maximum_size() noexcept;
};

PYCPP_END_NAMESPACE
