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
    ForwardIterator partition_rand (ForwardIterator first, ForwardIterator last)
    {
        typename std::iterator_traits<ForwardIterator>::difference_type size, step;
        size = std::distance (first, last);
        ForwardIterator pivotIter = first;
        step = random_generator::getRandomInt (0, static_cast<int>(size) - 1);
        std::advance (pivotIter, step);
        /** Method 1: swap pivotIter with first and use partition (first, last). */
//        iter_swap (first, pivotIter);
//        ForwardIterator pos = partition (first, last);
        
        //* Method 2: use for loop. THIS DOES NOT WORK YET */
        ForwardIterator pos = first;
        for (ForwardIterator it = first; it != last; ++it)
        {
            if ( (*pivotIter > *it))
            {
                /** swap the values at it and pos (the left most greater-than-pivot value. */
                if (it != pos)
                    iter_swap (it, pos);
                ++pos;
            }
            if ( (pos == pivotIter) && (std::distance(pos, last) > 1))
                ++pos;
        }
        if (std::distance (pos, pivotIter) > 0)
            iter_swap (pos, pivotIter);
        else if (std::distance (pos, pivotIter) < 0)
        {
            iter_swap (--pos, pivotIter);
        }
        return pos;
    }
    
    template <typename ForwardIterator>
    void quickSortRandom (ForwardIterator first, ForwardIterator last)
    {
        if (std::distance (first, last) <= 1)
            return;
        ++QuickSortRecursionCounter::recursionCounterRandomPivot;
        ForwardIterator pivotIndex = partition_rand (first, last);
        quickSortRandom (first, pivotIndex);
        quickSortRandom (pivotIndex + 1, last);
        
    }
    
    template <typename ForwardIterator>
    int qsortRandom (ForwardIterator first, ForwardIterator last)
    {
        QuickSortRecursionCounter::recursionCounterRandomPivot.clear();
        quickSortRandom (first, last);
        return QuickSortRecursionCounter::recursionCounterRandomPivot.get();
    }
}

#endif /* quickSort_h */
