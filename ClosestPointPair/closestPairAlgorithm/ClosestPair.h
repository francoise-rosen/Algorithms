//
//  ClosestPair.h
//  closestPairAlgorithm
//
//  Created by syfo_dias on 20/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#ifndef ClosestPair_h
#define ClosestPair_h
#include <vector>
#include "Point.h"
#include "MergeSort.h"

namespace  syfo {
    
    // This must be called if there are at least 2 points in container
    /** @param first - begin()
        @param last - end()
        @return pair of iterators (closest pair of points)
     */
    template <typename ForwardIterator, typename T>
    std::pair<ForwardIterator, ForwardIterator> bruteForce (ForwardIterator first, ForwardIterator last)
    {
        T smallestDistance = std::numeric_limits<T>::max();
        std::pair<ForwardIterator, ForwardIterator> result;
        while (last != first)
        {
            /** Compare the elem pointed to by first to the elem pointed
                to by current, which is initialised as first + 1
             */
            ForwardIterator current = first;
            ++current;
            for (; current < last; ++current)
            {
                T distance = dist(*current, *first);
                if (distance < smallestDistance)
                {
                    result = {first, current};
                    smallestDistance = distance;
                }
            }
            ++first;
        }
        
        return result;
    }
    
    /** @param first - begin()
        @param last - end()
        @param middle - iterator to a middle point (last element in the left subrange)
        @param d - closest pair of points from either subrage (left or right)
        @return pair of iterators to the closest pair of pointers within the strip
        Note that this changes the pair d!
        In case there are several equally spaced points, it will return the pair of
        iterators to either of those.
     */
    template <typename ForwardIterator, typename T>
    std::pair<ForwardIterator, ForwardIterator> splitPair (ForwardIterator first, ForwardIterator last, ForwardIterator middle, std::pair<ForwardIterator, ForwardIterator> d) noexcept
    {
        T delta = dist(*d.first, *d.second);
        std::pair<ForwardIterator, ForwardIterator> closestPairFromSplit = d;
        /** I want to find exact pair of points, not just the distance,
            so I can mark them graphically.
            Therefore, a container of points lying within the strip contains iterators (not just values!) to those points, sorted by y coordinate.
         */
        std::vector<ForwardIterator> strip;
        for (ForwardIterator it = first; it != last; ++it)
        {
            if (abs ((*it).x - (*middle).x) < delta)
            {
                strip.push_back(it);
            }
        }
        
        /** Sort the strip items in respect to their y coordinate. */
        msort (strip.begin(), strip.end(), [] (ForwardIterator a, ForwardIterator b)
               { return (*a).y < (*b).y;});
        for (int i = 0; i < strip.size(); ++i)
        {
            /* The inner loop runs at most 7 times! (Worst case scenario)
              x and y coodinates must be strictly less than delta.
             */
            for (int j = i + 1; (j < strip.size()) && (abs(strip[j]->y - strip[i]->y) < delta); ++j)
            {
                if (dist (*strip[i], *strip[j]) < delta)
                {
                    delta = dist (*strip[i], *strip[j]);
                    closestPairFromSplit = {strip[i], strip[j]};
                }
            }
        }
        return closestPairFromSplit;
    }
    
    /** Split the range in two and recursively search for a closest pair
        @param first - begin() of subrange
        @param last - end() of subrange
        @return pair of iteratirs to the currently closest pair
     */
    template <typename ForwardIterator, typename T>
    std::pair<ForwardIterator, ForwardIterator> closestPair (ForwardIterator first, ForwardIterator last)
    {
        if (std::distance(first, last) < 4)
        {
            return bruteForce<ForwardIterator, T> (first, last);
        }
        
        typename std::iterator_traits<ForwardIterator>::difference_type step;
        step = (last - first) / 2;
        ForwardIterator middle = first;
        std::advance (middle, step);
        
        std::pair <ForwardIterator, ForwardIterator> leftPair = closestPair<ForwardIterator, T> (first, middle);
        std::pair <ForwardIterator, ForwardIterator> rightPair = closestPair<ForwardIterator, T> (middle, last);
 
        T distanceLeft = dist (*leftPair.first, *leftPair.second);
        T distanceRight = dist (*rightPair.first, *rightPair.second);
        T d = std::min (distanceLeft, distanceRight);
        std::pair<ForwardIterator, ForwardIterator> closestPairFromPartition = (distanceLeft > distanceRight) ? rightPair : leftPair;
        std::pair <ForwardIterator, ForwardIterator> split = splitPair<ForwardIterator, T>(first, last, middle, closestPairFromPartition);
        if (dist (*split.first, *split.second) < d)
            closestPairFromPartition = split;
        return closestPairFromPartition;
    }
    
    /** This function merely sorts the incoming conteiner by x coordinate,
        calls the recursive algorithm, and ultimately returns the closest pair.
        @param first - begin()
        @param last - end()
        @return pair of iterators to the closest pair of points
     */
    template <typename ForwardIterator, typename T>
    std::pair<ForwardIterator, ForwardIterator> findClosestDistance (ForwardIterator first, ForwardIterator last)
    {
        syfo::msort (first, last, SortX<T>());
        return closestPair<ForwardIterator, T> (first, last);
    }
}


#endif /* ClosestPair_h */
