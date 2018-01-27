//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#include <pycpp/context/stack_context.hpp>
#include <pycpp/context/stack_traits.hpp>
#include <pycpp/stl/cassert.h>
#include <pycpp/stl/cmath.h>
#include <pycpp/stl/cstddef.h>
#include <pycpp/stl/new.h>
#include <pycpp/system/windows.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

template <typename TraitsT>
class basic_protected_fixedsize_stack
{
public:
    using traits_type = TraitsT;

    basic_protected_fixedsize_stack(
        size_t size = traits_type::default_size()
    )
    noexcept:
        size_(size)
    {}

    stack_context
    allocate()
    {
        // calculate how many pages are required
        size_t pages = static_cast<size_t>(ceil(static_cast<float>(size_) / traits_type::page_size()));
        // add one page at bottom that will be used as guard-page
        size_t size = (pages + 1) * traits_type::page_size();

        void* vp = ::VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
        if (vp == nullptr) {
            throw bad_alloc();
        }

        DWORD old_options;
        BOOL result = ::VirtualProtect(vp, traits_type::page_size(), PAGE_READWRITE | PAGE_GUARD, &old_options);
        assert(FALSE != result);

        stack_context sctx;
        sctx.size = size;
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

        void * vp = static_cast<char*>(sctx.sp) - sctx.size;
        ::VirtualFree(vp, 0, MEM_RELEASE);
    }

private:
    size_t size_;
};

// ALIASES
// -------

using protected_fixedsize_stack = basic_protected_fixedsize_stack<stack_traits>;

PYCPP_END_NAMESPACE
