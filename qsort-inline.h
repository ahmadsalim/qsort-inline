/*
 * Copyright (c) 2000-2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1995 NeXT Computer, Inc. All Rights Reserved
 *
 * Copyright (c) 1992, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)qsort.c  8.1 (Berkeley) 6/4/93
 */
//Modified as qsort-inline.h by AS

#ifndef __QSORT__INLINE__H
#define __QSORT__INLINE__H
#include <sys/types.h>

static inline void   swapfunc(char *, char *, int, int);

#define min_(a, b)  (a) < (b) ? a : b

/*
 * Qsort routine from Bentley & McIlroy's "Engineering a Sort Function".
 */
#define swapcode(TYPE, parmi, parmj, n) {     \
  long i = (n) / sizeof (TYPE);       \
  TYPE *pi = (TYPE *) (parmi);       \
  TYPE *pj = (TYPE *) (parmj);       \
  do {             \
    TYPE  t = *pi;      \
    *pi++ = *pj;        \
    *pj++ = t;        \
        } while (--i > 0);        \
}

#define SWAPINIT(a, es) swaptype = ((char *)a - (char *)0) % sizeof(long) || \
  es % sizeof(long) ? 2 : es == sizeof(long)? 0 : 1;

static inline void
swapfunc(char *a, char *b, int n, int swaptype)
{
  if(swaptype <= 1) 
    swapcode(long, a, b, n)
  else
    swapcode(char, a, b, n)
}

#define swap_(a, b)          \
  if (swaptype == 0) {        \
    long t = *(long *)(a);      \
    *(long *)(a) = *(long *)(b);    \
    *(long *)(b) = t;      \
  } else            \
    swapfunc((char *)a, (char *)b, es, swaptype)

#define vecswap(a, b, n)   if ((n) > 0) swapfunc((char *)a, (char *)b, n, swaptype)


#define QSORT(T,CMP) qsort##T##CMP
#define MED3(T,CMP) med3##T##CMP
#define DEF_QSORT(T, CMP)  \
static inline char * \
MED3(T, CMP) (char *a, char *b, char *c) \
{ \
    return CMP(a, b) < 0 ?\
    (CMP(b, c) < 0 ? b : (CMP(a, c) < 0 ? c : a )) \
    :(CMP(b, c) > 0 ? b : (CMP(a, c) < 0 ? a : c )); \
} \
void QSORT(T,CMP) (T *a, size_t n)      \
{                              \
  size_t es = sizeof(T);       \
  char *pa, *pb, *pc, *pd, *pl, *pm, *pn; \
  int d, swaptype, swap_cnt;   \
  int r;                       \
                               \
loop:  SWAPINIT(a, es);        \
  swap_cnt = 0;                \
  if (n < 7) {                 \
    for (pm = (char *)a + es; pm < (char*)a + n * es; pm += es) \
      for (pl = pm; pl > (char*)a && CMP(pl - es, pl) > 0; \
           pl -= es)           \
        swap_(pl, pl - es);     \
    return;                    \
  } \
  pm = (char*)a + (n / 2) * es; \
  if (n > 7) { \
    pl = (char*)a; \
    pn = (char*)a + (n - 1) * es; \
    if (n > 40) { \
      d = (n / 8) * es; \
      pl = MED3(T, CMP) (pl, pl + d, pl + 2 * d);\
      pm = MED3(T, CMP) (pm - d, pm, pm + d); \
      pn = MED3(T, CMP) (pn - 2 * d, pn - d, pn); \
    } \
    pm = MED3(T, CMP) (pl, pm, pn); \
  } \
  swap_(a, pm); \
  pa = pb = (char*)a + es; \
    \
  pc = pd = (char*)a + (n - 1) * es; \
  for (;;) { \
    while (pb <= pc && (r = CMP(pb, a)) <= 0) { \
      if (r == 0) { \
        swap_cnt = 1; \
        swap_(pa, pb); \
        pa += es; \
      } \
      pb += es; \
    } \
    while (pb <= pc && (r = CMP(pc, a)) >= 0) { \
      if (r == 0) { \
        swap_cnt = 1; \
        swap_(pc, pd); \
        pd -= es; \
      } \
      pc -= es; \
    } \
    if (pb > pc) \
      break; \
    swap_(pb, pc); \
    swap_cnt = 1; \
    pb += es; \
    pc -= es; \
  } \
  if (swap_cnt == 0) {  /* Switch to insertion sort */ \
    for (pm = (char*)a + es; pm < (char*)a + n * es; pm += es) \
      for (pl = pm; pl > (char*)a && CMP(pl - es, pl) > 0; \
           pl -= es) \
        swap_(pl, pl - es); \
    return; \
  } \
   \
  pn = (char*)a + n * es; \
  r = min_(pa - (char*)a, pb - pa); \
  vecswap(a, pb - r, r); \
  r = min_((size_t)(pd - pc), pn - pd - es); \
  vecswap(pb, pn - r, r); \
  if ((size_t)(r = pb - pa) > es) \
    QSORT(T, CMP) (a, r / es); \
  if ((size_t)(r = pd - pc) > es) {  \
    /* Iterate rather than recurse to save stack space */ \
    a = (T*)(pn - r); \
    n = r / es; \
    goto loop; \
  } \
/*    QSORT(T, CMP)(pn - r, r / es);*/ \
}
#endif //__QSORT__INLINE__H