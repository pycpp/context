//  :copyright: (c) 2009 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#include <pycpp/stl/cstdint.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------

using fcontext_t = void*;

struct transfer_t
{
    fcontext_t fctx;
    void* data;
};

// FUNCTIONS
// ---------

// TODO: restore
//extern "C" BOOST_CONTEXT_DECL
//transfer_t BOOST_CONTEXT_CALLDECL jump_fcontext( fcontext_t const to, void * vp);
//extern "C" BOOST_CONTEXT_DECL
//fcontext_t BOOST_CONTEXT_CALLDECL make_fcontext( void * sp, std::size_t size, void (* fn)( transfer_t) );
//
//// based on an idea of Giovanni Derreta
//extern "C" BOOST_CONTEXT_DECL
//transfer_t BOOST_CONTEXT_CALLDECL ontop_fcontext( fcontext_t const to, void * vp, transfer_t (* fn)( transfer_t) );

PYCPP_END_NAMESPACE
