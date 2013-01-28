/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef SGI_STL_INTERNAL_ALGO_H
#define SGI_STL_INTERNAL_ALGO_H

namespace std {

#include "stl_heap.h"

template <class ForwardIter1, class ForwardIter2, class T>
inline void iter_swap(ForwardIter1 a, ForwardIter2 b, T*) {
  T tmp = *a;
  *a = *b;
  *b = tmp;
}

template <class ForwardIter1, class ForwardIter2>
inline void iter_swap(ForwardIter1 a, ForwardIter2 b) {
  iter_swap(a, b, VALUETYPE(a));
}

// median (an extension, not present in the C++ standard).
template <class T>
inline const T& median(const T& a, const T& b, const T& c) {
  if (a < b)
    if (b < c)
      return b;
    else if (a < c)
      return c;
    else
      return a;
  else if (a < c)
    return a;
  else if (b < c)
    return c;
  else
    return b;
}

template <class T, class Compare>
inline const T& median(const T& a, const T& b, const T& c, Compare comp) {
  if (comp(a, b))
    if (comp(b, c))
      return b;
    else if (comp(a, c))
      return c;
    else
      return a;
  else if (comp(a, c))
    return a;
  else if (comp(b, c))
    return c;
  else
    return b;
}

template <class RandomAccessIter, class T>
RandomAccessIter unguarded_partition(RandomAccessIter first, RandomAccessIter last, T pivot) 
{
  while (true) {
    while (*first < pivot) ++first;
    --last;
    while (pivot < *last) --last;
    if (!(first < last)) return first;
    iter_swap(first, last);
    ++first;
  }
}

template <class RandomAccessIter, class T, class Compare>
RandomAccessIter unguarded_partition(RandomAccessIter first, RandomAccessIter last, T pivot, Compare comp) 
{
  while (true) {
    while (comp(*first, pivot))
      ++first;
    --last;
    while (comp(pivot, *last))
      --last;
    if (!(first < last))
      return first;
    iter_swap(first, last);
    ++first;
  }
}

const int stlthreshold = 16;

// sort() and its auxiliary functions. 

template <class RandomAccessIter, class T>
void unguarded_linear_insert(RandomAccessIter last, T val) {
  RandomAccessIter next = last;
  --next;
  while (val < *next) {
    *last = *next;
    last = next;
    --next;
  }
  *last = val;
}

template <class RandomAccessIter, class T, class Compare>
void unguarded_linear_insert(RandomAccessIter last, T val, Compare comp) {
  RandomAccessIter next = last;
  --next;
  while (comp(val, *next)) {
    *last = *next;
    last = next;
    --next;
  }
  *last = val;
}

template <class RandomAccessIter, class T>
inline void linear_insert(RandomAccessIter first, RandomAccessIter last, T*) {
  T val = *last;
  if (val < *first) {
    copybackward(first, last, last + 1);
    *first = val;
  }
  else
    unguarded_linear_insert(last, val);
}

template <class RandomAccessIter, class T, class Compare>
inline void linear_insert(RandomAccessIter first, RandomAccessIter last, T*, Compare comp) {
  T val = *last;
  if (comp(val, *first)) {
    copybackward(first, last, last + 1);
    *first = val;
  }
  else
    unguarded_linear_insert(last, val, comp);
}

//ValueType = basetype for iterator
//DistanceType = type for representing difference between two of the same type

template <class RandomAccessIter>
void insertion_sort(RandomAccessIter first, RandomAccessIter last) {
  if (first == last) return; 
  for (RandomAccessIter i = first + 1; i != last; ++i)
    linear_insert(first, i, VALUETYPE(first));
}

template <class RandomAccessIter, class Compare>
void insertion_sort(RandomAccessIter first,
                      RandomAccessIter last, Compare comp) {
  if (first == last) return;
  for (RandomAccessIter i = first + 1; i != last; ++i)
    linear_insert(first, i, VALUETYPE(first), comp);
}

template <class RandomAccessIter, class T>
void unguarded_insertion_sort_aux(RandomAccessIter first, RandomAccessIter last, T*) {
  for (RandomAccessIter i = first; i != last; ++i)
    unguarded_linear_insert(i, T(*i));
}

template <class RandomAccessIter>
inline void unguarded_insertion_sort(RandomAccessIter first, RandomAccessIter last) {
  unguarded_insertion_sort_aux(first, last, VALUETYPE(first));
}

template <class RandomAccessIter, class T, class Compare>
void unguarded_insertion_sort_aux(RandomAccessIter first, RandomAccessIter last, T*, Compare comp) {
  for (RandomAccessIter i = first; i != last; ++i)
    unguarded_linear_insert(i, T(*i), comp);
}

template <class RandomAccessIter, class Compare>
inline void unguarded_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp) {
  unguarded_insertion_sort_aux(first, last, VALUETYPE(first), comp);
}

template <class RandomAccessIter>
void final_insertion_sort(RandomAccessIter first, RandomAccessIter last) {
  if (last - first > stlthreshold) {
    insertion_sort(first, first + stlthreshold);
    unguarded_insertion_sort(first + stlthreshold, last);
  }
  else
    insertion_sort(first, last);
}

template <class RandomAccessIter, class Compare>
void final_insertion_sort(RandomAccessIter first, RandomAccessIter last, Compare comp) {
  if (last - first > stlthreshold) {
    insertion_sort(first, first + stlthreshold, comp);
    unguarded_insertion_sort(first + stlthreshold, last, comp);
  }
  else
    insertion_sort(first, last, comp);
}

template <class Size>
inline Size lg(Size n) {
  Size k;
  for (k = 0; n != 1; n >>= 1) ++k;
  return k;
}

template <class RandomAccessIter, class T>
void partial_sort(RandomAccessIter first, RandomAccessIter middle, RandomAccessIter last, T*) {
  make_heap(first, middle);
  for (RandomAccessIter i = middle; i < last; ++i)
    if (*i < *first) 
      pop_heap(first, middle, i, T(*i), DISTANCETYPE(first));
  sort_heap(first, middle);
}

template <class RandomAccessIter>
inline void partial_sort(RandomAccessIter first, RandomAccessIter middle, RandomAccessIter last) {
  partial_sort(first, middle, last, VALUETYPE(first));
}

template <class RandomAccessIter, class T, class Compare>
void partial_sort(RandomAccessIter first, RandomAccessIter middle, RandomAccessIter last, T*, Compare comp) {
  make_heap(first, middle, comp);
  for (RandomAccessIter i = middle; i < last; ++i)
    if (comp(*i, *first))
      pop_heap(first, middle, i, T(*i), comp, DISTANCETYPE(first));
  sort_heap(first, middle, comp);
}

template <class RandomAccessIter, class Compare>
inline void partial_sort(RandomAccessIter first, RandomAccessIter middle, RandomAccessIter last, Compare comp) {
  partial_sort(first, middle, last, VALUETYPE(first), comp);
}

template <class RandomAccessIter, class T, class Size>
void introsort_loop(RandomAccessIter first, RandomAccessIter last, T*, Size depthlimit)
{
  while (last - first > stlthreshold) {
    if (depthlimit == 0) {
      partial_sort(first, last, last);
      return;
    }
    --depthlimit;
    RandomAccessIter cut =
      unguarded_partition(first, last,
                            T(median(*first, *(first + (last - first)/2), *(last - 1))));
    introsort_loop(cut, last, (T*) 0, depthlimit);
    last = cut;
  }
}

template <class RandomAccessIter, class T, class Size, class Compare>
void introsort_loop(RandomAccessIter first, RandomAccessIter last, T*, Size depthlimit, Compare comp)
{
  while (last - first > stlthreshold) {
    if (depthlimit == 0) {
      partial_sort(first, last, last, comp);
      return;
    }
    --depthlimit;
    RandomAccessIter cut =
      unguarded_partition(first, last,
                            T(median(*first,
                                         *(first + (last - first)/2),
                                         *(last - 1), comp)),
       comp);
    introsort_loop(cut, last, (T*) 0, depthlimit, comp);
    last = cut;
  }
}

template <class RandomAccessIter>
inline void sort(RandomAccessIter first, RandomAccessIter last) {
  if (first != last) {
    introsort_loop(first, last, VALUETYPE(first), lg(last - first) * 2);
    final_insertion_sort(first, last);
  }
}

template <class RandomAccessIter, class Compare>
inline void sort(RandomAccessIter first, RandomAccessIter last, Compare comp) {
  if (first != last) {
    introsort_loop(first, last, VALUETYPE(first), lg(last - first) * 2, comp);
    final_insertion_sort(first, last, comp);
  }
}

}

#endif /* SGI_STL_INTERNAL_ALGO_H */

// Local Variables:
// mode:C++
// End:
