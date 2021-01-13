//
//  bubbleSort.h
//  interativeQuickSort
//
//  Created by syfo_dias on 13/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef bubbleSort_h
#define bubbleSort_h

template <typename T>
void sfd_swap (T* left, T* right)
{
    T temp = *left;
    *left = *right;
    *right = temp;
}

template <typename ForwardIterator>
void bubbleSort (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type size, i;
    size = std::distance (first, last);
    
    for (i = 0; i < size; ++i)
    {
        bool isSwapped {false};
        ForwardIterator current = first;
        ForwardIterator next = current + 1;
        while (next != last - i)
        {
            if (*current > *next)
            {
                sfd_swap (current, next);
                isSwapped = true;
            }
            current = next;
            ++next;
        }
        if (! isSwapped)
            return;
    }
}

#endif /* bubbleSort_h */
