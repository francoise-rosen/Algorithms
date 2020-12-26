//
//  mergeSort.h
//  MergeSortAlgorithm
//
//  Created by syfo_dias on 26/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#ifndef mergeSort_h
#define mergeSort_h

//============================================================================
// SYFO NAMESPACE BEGIN
//============================================================================
namespace syfo
{
    /** This is the STL's copy. */
    template <typename InputIterator, typename OutputIterator>
    OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
    {
        while (first != last)
        {
            *result = *first;
            ++result; ++first;
        }
        return result;
    }
    
    /** Here last1 and last 2 are poining to the last elem. */
    template <typename ForwardIterator>
    void merge (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2)
    {
        typename std::iterator_traits<ForwardIterator>::difference_type size_left, size_right, current;
        /** Move one beyond the last element to use end() in copy
            and for calculating the distance.
         */
        size_left = std::distance (first1, ++last1);
        size_right = std::distance (first2, ++last2);
        /** Create and fill temp arrays with the left side range
         and the right side range.
         */
        typename std::iterator_traits<ForwardIterator>::value_type left_array[size_left], right_array[size_right];
        syfo::copy (first1, last1, left_array);
        syfo::copy (first2, last2, right_array);
        
        /** Merge sorted ranges into the final range [first1, last2].
         Values are compared and added as per condition.
         */
        current = 0;
        int i {0}, j {0};
        while ( (i < size_left) && (j < size_right) )
        {
            if (left_array[i] < right_array[j])
            {
                *first1 = left_array[i];
                ++i;
            }
            else
            {
                *first1 = right_array[j];
                ++j;
            }
            ++current;
            ++first1;
        }
        
        /** Append the reminder - either the left or the right range.
         */
        for (;i < size_left; ++i)
        {
            *first1 = left_array[i];
            ++current;
            ++first1;
        }
        for (;j < size_right; ++j)
        {
            *first1 = right_array[j];
            ++current;
            ++first1;
        }
    }
    
    /** Split and merge recursevly.
     @param first is begin()
     @param last is one elem before end()
     */
    template <typename ForwardIterator>
    void mergeSort (ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type count;
        count = std::distance(first, last);
        ForwardIterator middle = first;
        std::advance(middle, count / 2);
        /** The left side. */
        mergeSort (first, middle);
        /** The right side. */
        ForwardIterator middleNext = middle;
        std::advance (middleNext, 1);
        mergeSort (middleNext, last);
        merge (first, middle, middleNext, last);
    }
    
    /** Special case - 0 elem is ignored.
     The above algorithm does not use iterator to one-past-last (end())
     */
    template <typename ForwardIterator>
    void msort (ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type sz;
        sz = std::distance(first, last);
        ForwardIterator pen = first;
        std::advance (pen, sz - 1);
        mergeSort(first, pen);
    }
    
}

//============================================================================
// SYFO NAMESPACE END
//============================================================================


#endif /* mergeSort_h */
