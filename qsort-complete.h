#include "qsort-inline.h"
#include "versions.h"
#include <string.h>

#ifndef __QSORT__COMPLETE__H
#define __QSORT__COMPLETE__H
#ifdef C90
  #define CONST const
#else
  #define CONST
#endif
#ifdef C99
  #define INLINE static inline 
  #define RESTRICT restrict
#else
  #define INLINE static
  #define RESTRICT
#endif
#define BASICCMP(T) T##cmp
#define DEF_BASICCMP(T) \
  INLINE int BASICCMP(T) (CONST T *RESTRICT a, CONST T *RESTRICT b) { \
    return (*a < *b) ? -1 : (*a > *b); \
  }
#define QSORTD_(...) QSORT(__VA_ARGS__)
#define QSORTD(T) QSORTD_(T, BASICCMP(T))
#define DEF_QSORTD_(...) DEF_QSORT(__VA_ARGS__)
#define DEF_QSORTD(T) DEF_QSORTD_(T, BASICCMP(T))

#define DECL_QSORT(T, CMP) void QSORT(T, CMP) (T*, size_t)
#define DECL_QSORTD_(...) DECL_QSORT(__VA_ARGS__)
#define DECL_QSORTD(T) DECL_QSORTD_(T, BASICCMP(T))

typedef signed char sbyte;
typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;
DECL_QSORTD(sbyte);
DECL_QSORTD(int);
DECL_QSORTD(short);
DECL_QSORTD(long);
DECL_QSORTD(byte);
DECL_QSORTD(uint);
DECL_QSORTD(ushort);
DECL_QSORTD(ulong);
#ifdef C99
  typedef long long llong;
  typedef unsigned long long ullong;
  typedef long double ldouble;
  DECL_QSORTD(llong);
  DECL_QSORTD(ullong);
  DECL_QSORTD(ldouble);
  DECL_QSORTD(_Bool);
#endif
typedef char * string;
DECL_QSORTD(string);

#endif //__QSORT__COMPLETE__H
