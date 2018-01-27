//  :copyright: (c) 2009 Oliver Kowalke.
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
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

PYCPP_BEGIN_NAMESPACE

// MACROS
// ------

#if !defined(MAP_ANON) && defined(MAP_ANONYMOUS)
#   define MAP_ANON MAP_ANONYMOUS
#endif

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
    noexcept :
        size_(size)
    {}

    stack_context
    allocate()
    {
        // calculate how many pages are required
        size_t pages = static_cast<size_t>(ceil(static_cast<float>(size_) / traits_type::page_size()));
        // add one page at bottom that will be used as guard-page
        size_t size = (pages + 1) * traits_type::page_size();

        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        void* vp = ::mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (vp == MAP_FAILED) {
            throw bad_alloc();
        }

        // conforming to POSIX.1-2001
        int result(::mprotect(vp, traits_type::page_size(), PROT_NONE));
        assert(result == 0);

        stack_context sctx;
        sctx.size = size;
        sctx.sp = static_cast<char*>(vp) + sctx.size;
        return sctx;
    }

    void deallocate(
        stack_context& sctx
    )
    noexcept
    {
        assert(sctx.sp);
        void * vp = static_cast<char*>(sctx.sp) - sctx.size;
        // conform to POSIX.4 (POSIX.1b-1993, _POSIX_C_SOURCE=199309L)
        ::munmap(vp, sctx.size);
    }

private:
    size_t size_;
};

// ALIASES
// -------

using protected_fixedsize_stack = basic_protected_fixedsize_stack<stack_traits>;

PYCPP_END_NAMESPACE
