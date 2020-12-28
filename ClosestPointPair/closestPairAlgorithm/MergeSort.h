//
//  MergeSort.h
//  closestPairAlgorithm
//
//  Created by syfo_dias on 20/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#ifndef MergeSort_h
#define MergeSort_h

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
    
    /** Merging the left and the right subranges, sorting their elements*/
    /** @param first1 is the begin() of the left subrange.
     @param last1 is the last element of the left subrange.
     @param first2 is the begin() of the right subrange.
     @param last2 is the last element of the right subrange.
     */
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
    
    /** Accessed by user.
     @param first - begin()
     @param last - end()
     The recursive algorithm from above needs the last to be
     the last element in subrange, the element that can be dereferenced (not the end()).
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
        mergeSort (first, pen);
    }
    
    //==================================================================================
    /** WITH COMPARE. */
    //==================================================================================
    
    /** Merging the left and the right subranges, sorting their elements*/
    /** @param first1 is the begin() of the left subrange.
     @param last1 is the last element of the left subrange.
     @param first2 is the begin() of the right subrange.
     @param last2 is the last element of the right subrange.
     */
    template <typename ForwardIterator, typename Compare>
    void merge (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2, Compare comp)
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
            if (comp (left_array[i], right_array[j]) )
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
    template <typename ForwardIterator, typename Compare>
    void mergeSort (ForwardIterator first, ForwardIterator last, Compare comp)
    {
        if (first == last)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type count;
        count = std::distance(first, last);
        ForwardIterator middle = first;
        std::advance(middle, count / 2);
        /** The left side. */
        mergeSort (first, middle, comp);
        /** The right side. */
        ForwardIterator middleNext = middle;
        std::advance (middleNext, 1);
        mergeSort (middleNext, last, comp);
        merge (first, middle, middleNext, last, comp);
    }
    
    template <typename ForwardIterator, typename Compare>
    void msort (ForwardIterator first, ForwardIterator last, Compare comp)
    {
        if (first == last)
            return;
        typename std::iterator_traits<ForwardIterator>::difference_type sz;
        sz = std::distance (first, last);
        ForwardIterator pen = first;
        std::advance (pen, sz - 1);
        mergeSort (first, pen, comp);
    }
    
}

//============================================================================
// SYFO NAMESPACE END
//============================================================================


#endif /* MergeSort_h */
