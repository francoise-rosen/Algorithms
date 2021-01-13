//
//  quickSort.h
//  interativeQuickSort
//
//  Created by syfo_dias on 12/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef quickSort_h
#define quickSort_h
#include "bubbleSort.h"

template <typename ForwardIterator>
ForwardIterator partition (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::value_type pivotValue = *first;
    
    ForwardIterator leftIndex = first;
    ForwardIterator rightSubrangeFirst = first + 1;
    for (ForwardIterator it = rightSubrangeFirst; it != last; ++it)
    {
        if (pivotValue > *it)
        {
            std::swap(*leftIndex, *it);
            ++leftIndex;
            ++rightSubrangeFirst;
        }
    }
    std::swap (*leftIndex, *first);
    return first;
}


template <typename ForwardIterator>
void quickSort (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type size;
    size = std::distance (first, last);
    if (size <= 1)
        return;
    ForwardIterator pivotIndex = partition (first, last);
    quickSort (first, pivotIndex);
    quickSort (pivotIndex + 1, last);
}

#endif /* quickSort_h */
