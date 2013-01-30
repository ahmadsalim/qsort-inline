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
 * Copyright (c) 1997
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

#ifndef SGI_STL_INTERNAL_HEAP_H
#define SGI_STL_INTERNAL_HEAP_H

namespace std {
// Heap-manipulation functions: push_heap, pop_heap, make_heap, sort_heap.

template <class RandomAccessIterator, class Distance, class T, class Compare>
void
push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value, Compare comp)
{
  Distance parent = (holeIndex - 1) / 2;
  while (holeIndex > topIndex && comp(*(first + parent), value)) {
    *(first + holeIndex) = *(first + parent);
    holeIndex = parent;
    parent = (holeIndex - 1) / 2;
  }
  *(first + holeIndex) = value;
}

template <class RandomAccessIterator, class Compare, class Distance, class T>
inline void 
push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Compare comp, Distance*, T*) 
{
  push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)), comp);
}

template <class RandomAccessIterator, class Compare>
inline void 
push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
  push_heap_aux(first, last, comp, DISTANCETYPE(first), VALUETYPE(first));
}

template <class RandomAccessIterator, class Distance, class T, class Compare>
void
adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value, Compare comp)
{
  Distance topIndex = holeIndex;
  Distance secondChild = 2 * holeIndex + 2;
  while (secondChild < len) {
    if (comp(*(first + secondChild), *(first + (secondChild - 1))))
      secondChild--;
    *(first + holeIndex) = *(first + secondChild);
    holeIndex = secondChild;
    secondChild = 2 * (secondChild + 1);
  }
  if (secondChild == len) {
    *(first + holeIndex) = *(first + (secondChild - 1));
    holeIndex = secondChild - 1;
  }
  push_heap(first, holeIndex, topIndex, value, comp);
}

template <class RandomAccessIterator, class T, class Compare, class Distance>
inline void 
pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Compare comp, Distance*)
{
  *result = *first;
  adjustheap(first, Distance(0), Distance(last - first), value, comp);
}

template <class RandomAccessIterator, class T, class Compare>
inline void 
pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*, Compare comp)
{
  pop_heap(first, last - 1, last - 1, T(*(last - 1)), comp, DISTANCETYPE(first));
}

template <class RandomAccessIterator, class Compare>
inline void 
pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
  pop_heap_aux(first, last, VALUETYPE(first), comp);
}

template <class RandomAccessIterator, class Compare, class T, class Distance>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp, T*, Distance*)
{
  if (last - first < 2) return;
  Distance len = last - first;
  Distance parent = (len - 2)/2;
  while (true) {
    adjustheap(first, parent, len, T(*(first + parent)),
                  comp);
    if (parent == 0) return;
    parent--;
  }
}

template <class RandomAccessIterator, class Compare>
inline void 
make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
  make_heap(first, last, comp, VALUETYPE(first), DISTANCETYPE(first));
}

template <class RandomAccessIterator, class Compare>
void 
sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
  while (last - first > 1)
    pop_heap(first, last--, comp);
}

}
#endif /* __SGI_STL_INTERNAL_HEAP_H */

// Local Variables:
// mode:C++
// End:
