#  :copyright: (c) 2017-2018 Alex Huszagh.
#  :license: MIT, see licenses/mit.md for more details.

add_headers(
    continuation.h
    execution_context.h
    fixedsize_stack.h
    flags.h
    pooled_fixedsize_stack.h
    preallocated.h
    protected_fixedsize_stack.h
    segmented_stack.h
    stack_context.h
    stack_traits.h
)

if(WIN32)
    add_headers(windows/protected_fixedsize_stack.h)
    add_sources(windows/stack_traits.cc)
else()
    add_headers(
        posix/protected_fixedsize_stack.h
        posix/segmented_stack.h
    )
    add_sources(posix/stack_traits.cc)
endif()

# TODO: need to get the correct architecture...
