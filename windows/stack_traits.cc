//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#include <pycpp/context/stack_traits.h>
#include <pycpp/preprocessor/processor.h>
#include <pycpp/stl/algorithm.h>
#include <pycpp/stl/cassert.h>
#include <pycpp/stl/cmath.h>
#include <pycpp/stl/cstring.h>
#include <pycpp/stl/mutex.h>
#include <pycpp/system/windows.h>

// MACROS
// ------

#if defined(PROCESSOR_X8664)
#   define MIN_STACKSIZE 8 * 1024
#else
#   define MIN_STACKSIZE 4 * 1024
#endif

PYCPP_BEGIN_NAMESPACE

//  HELPERS
// --------

void system_info_(
    SYSTEM_INFO* si
) noexcept
{
    ::GetSystemInfo( si);
}

SYSTEM_INFO
system_info()
noexcept
{
    static SYSTEM_INFO si;
    static once_flag flag;
    call_once(flag, static_cast<void(*)(SYSTEM_INFO*)>(system_info_), &si);

    return si;
}

size_t
pagesize()
noexcept
{
    return static_cast<size_t>(system_info().dwPageSize);
}

// OBJECTS
// -------

// Windows seems not to provide a limit for the stacksize
// libcoco uses 32k+4k bytes as minimum
bool
stack_traits::is_unbounded() noexcept
{
    return true;
}

size_t
stack_traits::page_size()
noexcept
{
    return pagesize();
}

size_t
stack_traits::default_size()
noexcept
{
    return 128 * 1024;
}

// because Windows seams not to provide a limit for minimum stacksize
size_t
stack_traits::minimum_size()
noexcept
{
    return MIN_STACKSIZE;
}

// because Windows seams not to provide a limit for maximum stacksize
// maximum_size() can never be called (pre-condition ! is_unbounded() )
size_t
stack_traits::maximum_size()
noexcept
{
    assert(!is_unbounded());
    return 1 * 1024 * 1024 * 1024;      // 1GB
}

PYCPP_END_NAMESPACE
