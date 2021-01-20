//
//  insertionSort.h
//  interativeQuickSort
//
//  Created by syfo_dias on 18/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef insertionSort_h
#define insertionSort_h

namespace sfd
{
    template <typename ForwardIterator>
    void insertionSort (ForwardIterator first, ForwardIterator last)
    {
        typename std::iterator_traits<ForwardIterator>::value_type key, temp;
        const ForwardIterator begin = first;
        while (++first != last)
        {
            key = *first;
            ForwardIterator jth = first;
            --jth;
            
            while ( (std::distance (begin, jth)) >= 0 && (*jth > key))
            {
                temp = *(jth);
                *(++jth) = temp;
                std::advance (jth, -2);
            }
            *(++jth) = key;
        }
    }
}

#endif /* insertionSort_h */
