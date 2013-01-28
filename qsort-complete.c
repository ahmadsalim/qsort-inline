#include "qsort-complete.h"
DEF_BASICCMP(sbyte);
DEF_QSORTD(sbyte);
DEF_BASICCMP(int);
DEF_QSORTD(int);
DEF_BASICCMP(short);
DEF_QSORTD(short);
DEF_BASICCMP(long);
DEF_QSORTD(long);
DEF_BASICCMP(byte);
DEF_QSORTD(byte);
DEF_BASICCMP(uint);
DEF_QSORTD(uint);
DEF_BASICCMP(ushort);
DEF_QSORTD(ushort);
DEF_BASICCMP(ulong);
DEF_QSORTD(ulong);
#ifdef C99
  DEF_BASICCMP(llong);
  DEF_QSORTD(llong);
  DEF_BASICCMP(ullong);
  DEF_QSORTD(ullong);
  DEF_BASICCMP(ldouble);
  DEF_QSORTD(ldouble);
  DEF_BASICCMP(_Bool);
  DEF_QSORTD(_Bool);
#endif
INLINE int stringcmp(string *RESTRICT a, string *RESTRICT b) { return strcmp(*a, *b); }
DEF_QSORTD(string);
