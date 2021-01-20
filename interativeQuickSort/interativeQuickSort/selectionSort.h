//
//  selectionSort.h
//  interativeQuickSort
//
//  Created by syfo_dias on 18/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef selectionSort_h
#define selectionSort_h

namespace sfd
{
    template <typename ForwardIterator>
    void selectionSort (ForwardIterator first, ForwardIterator last)
    {
        while (first != last)
        {
            ForwardIterator currentMin = first;
            for (ForwardIterator it = first; it != last; ++it)
            {
                if (*it < *currentMin)
                    currentMin = it;
            }
            typename std::iterator_traits<ForwardIterator>::value_type temp = *currentMin;
            *currentMin = *first;
            *first = temp;
            ++first;
        }
    }
}

#endif /* selectionSort_h */
