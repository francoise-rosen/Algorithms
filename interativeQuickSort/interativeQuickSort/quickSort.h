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
#include "randomGenerator.h"
#include <string>

namespace sfd
{
    class Counter
    {
    public:
        Counter(int init = 0)
        :value {init}
        {}
        
        Counter operator++()
        {
            ++value;
            return *this;
        }
        
        int get() const
        {
            return value;
        }
        
        void clear()
        {
            value = 0;
        }
    private:
        int value;
    };
    
    namespace QuickSortRecursionCounter
    {
        static Counter recursionCounterLeftPivot;
        static Counter recursionCounterRandomPivot;
    }
    
    template <typename ForwardIterator>
    void iter_swap (ForwardIterator left, ForwardIterator right)
    {
        typename std::iterator_traits<ForwardIterator>::value_type temp = *left;
        *left = *right;
        *right = temp;
    }
    
    template <typename ForwardIterator>
    ForwardIterator partition (ForwardIterator first, ForwardIterator last)
    {
        typename std::iterator_traits<ForwardIterator>::value_type pivotValue = *first;
    
        ForwardIterator new_pivot = first;
        ForwardIterator it = first;
        ++it;
        while (it != last)
        {
            if (pivotValue > *it)
            {
                ++new_pivot;
                iter_swap (new_pivot, it);
            }
            ++it;
        }
        iter_swap (first, new_pivot);
        return new_pivot;
    }
    
    template <typename ForwardIterator>
    void quickSort (ForwardIterator first, ForwardIterator last)
    {
        typename std::iterator_traits<ForwardIterator>::difference_type size;
        size = std::distance (first, last);
        if (size <= 1)
            return;
        ++QuickSortRecursionCounter::recursionCounterLeftPivot;
        ForwardIterator pivotIndex = partition (first, last);
        quickSort (first, pivotIndex);
        quickSort (pivotIndex + 1, last);
    }
    
    template <typename ForwardIterator>
    int qsort (ForwardIterator first, ForwardIterator last)
    {
        QuickSortRecursionCounter::recursionCounterLeftPivot.clear();
        quickSort(first, last);
        return QuickSortRecursionCounter::recursionCounterLeftPivot.get();
    }
    
    // Using random pivot
    template <typename ForwardIterator>
    int qsortRandom (ForwardIterator first, ForwardIterator last)
    {
        QuickSortRecursionCounter::recursionCounterRandomPivot.clear();
    }
}

#endif /* quickSort_h */
