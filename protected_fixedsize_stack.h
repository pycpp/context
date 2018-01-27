//  :copyright: (c) 2009 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#pragma once

#include <pycpp/context/config.h>
#if defined(OS_WINDOWS)
#   include <pycpp/context/windows/protected_fixedsize_stack.hpp>
#else
#   include <pycpp/context/posix/protected_fixedsize_stack.hpp>
#endif
