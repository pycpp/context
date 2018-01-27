//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#include <pycpp/context/fcontext.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

struct forced_unwind
{
    fcontext_t fctx = {nullptr};

    forced_unwind() = default;

    forced_unwind(
        fcontext_t f
    ):
        fctx(f)
    {}
};

PYCPP_END_NAMESPACE
