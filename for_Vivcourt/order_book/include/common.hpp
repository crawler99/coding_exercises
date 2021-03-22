#ifndef _VIVCOURT_COMMON_H_
#define _VIVCOURT_COMMON_H_

#ifdef __GNUC__
    #ifdef NDEBUG
        #define ALWAYS_INLINE __attribute__((always_inline))
    #else
        #define ALWAYS_INLINE // otherwise difficult to debug
    #endif
    #define LIKELY(x)   __builtin_expect(!!(x),1)
    #define UNLIKELY(x) __builtin_expect(!!(x),0)
#else
    #define FORCE_INLINE
    #define FORCE_NOINLINE
    #define LIKELY(x)   (x)
    #define UNLIKELY(x) (x)
#endif

#endif // _VIVCOURT_COMMON_H_