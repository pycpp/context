//  :copyright: (c) 2014 Oliver Kowalke.
//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: Boost, see licenses/boost.md for more details.

#include <pycpp/config.h>
#include <pycpp/preprocessor/cache.h>
#include <pycpp/preprocessor/compiler.h>

// MACROS
// ------

#undef PYCPP_USE_SEGMENTED_STACKS
#if defined(PYCPP_GCC) && PYCPP_COMPILER_VERSION_CODE >= PYCPP_COMPILER_VERSION(4, 6, 0)
#   define PYCPP_USE_SEGMENTED_STACKS 1
#elif defined(PYCPP_CLANG) && PYCPP_COMPILER_VERSION_CODE >= PYCPP_COMPILER_VERSION(2, 3, 0)
#   define PYCPP_USE_SEGMENTED_STACKS 1
#endif

#if defined(PYCPP_USE_SEGMENTED_STACKS) && !defined(PYCPP_CONTEXT_SEGMENTS)
#   define PYCPP_CONTEXT_SEGMENTS 10
#endif

//#undef BOOST_CONTEXT_CALLDECL
//#if (defined(i386) || defined(__i386__) || defined(__i386) \
//     || defined(__i486__) || defined(__i586__) || defined(__i686__) \
//     || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) \
//     || defined(__I86__) || defined(__INTEL__) || defined(__IA32__) \
//     || defined(_M_IX86) || defined(_I86_)) && defined(BOOST_WINDOWS)
//# define BOOST_CONTEXT_CALLDECL __cdecl
//#else
//# define BOOST_CONTEXT_CALLDECL
//#endif
