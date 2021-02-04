//
//  main.cpp
//  deterministicSelection
//
//  Created by syfo_dias on 04/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>

namespace algo
{
    
    /** recursively find the median of C. */
    template <typename ForwardIterator>
    void findMedian (ForwardIterator first, ForwardIterator last)
    {
        
    }
    
    template <typename ForwardIterator>
    void choosePivot (ForwardIterator first, ForwardIterator last)
    {
        typename std::iterator_traits<ForwardIterator>::difference_type size, numSubarrays;
        using T = typename std::iterator_traits<ForwardIterator>::value_type;
        size = std::distance (first, last);
        std::vector<T> C;
        // divide a container into sub arrays of 5
        ForwardIterator it = first;
        ForwardIterator it_back = first;
        
        numSubarrays = size / 5;
        for (auto i = 0; i < numSubarrays; ++i)
        {
            
            (std::distance (first, last) > 5) ? std::advance (it_back, 5) : std::advance (it_back, std::distance (first, last) - 1);
        }
        
        // sort each sub array, find median and add it to an array of medians
        // recursively find the median of that array (value at index n / 2)
        
    }
    
    template <typename ForwardIterator>
    ForwardIterator dSelect (ForwardIterator first, ForwardIterator last, int index)
    {
        // choose pivot
        // run recursive call depending on pivot > index
    }
    
    template <typename C, typename T>
    T nth_order_statistic (C container, int index)
    {
        
    }
}

int main(int argc, const char * argv[]) {
    
    return 0;
}
