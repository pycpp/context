//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#include <pycpp/context/stack_traits.h>
#include <pycpp/stl/algorithm.h>
#include <pycpp/stl/cassert.h>
#include <pycpp/stl/cmath.h>
#include <pycpp/stl/mutex.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

// MACROS
// ------

#if !defined(SIGSTKSZ)
#   define SIGSTKSZ (32768)         // 32kb minimum allowable stack
#   define UDEF_SIGSTKSZ
#endif

#if !defined(MINSIGSTKSZ)
#   define MINSIGSTKSZ (131072)     // 128kb recommended stack size
#   define UDEF_MINSIGSTKSZ
#endif

PYCPP_BEGIN_NAMESPACE

//  HELPERS
// --------

void
pagesize_(
    size_t* size
)
noexcept
{
    // conform to POSIX.1-2001
    * size = ::sysconf(_SC_PAGESIZE);
}

void
stacksize_limit_(
    rlimit* limit
)
noexcept
{
    // conforming to POSIX.1-2001
    ::getrlimit( RLIMIT_STACK, limit);
}

size_t
pagesize()
noexcept
{
    static size_t size = 0;
    static once_flag flag;
    call_once(flag, pagesize_, & size);

    return size;
}

rlimit
stacksize_limit()
noexcept
{
    static rlimit limit;
    static once_flag flag;
    call_once(flag, stacksize_limit_, &limit);

    return limit;
}

// OBJECTS
// -------

bool
stack_traits::is_unbounded()
noexcept
{
    return RLIM_INFINITY == stacksize_limit().rlim_max;
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

size_t
stack_traits::minimum_size()
noexcept
{
    return MINSIGSTKSZ;
}

size_t
stack_traits::maximum_size()
noexcept
{
    assert(!is_unbounded());
    return static_cast<size_t>(stacksize_limit().rlim_max);
}

PYCPP_END_NAMESPACE
