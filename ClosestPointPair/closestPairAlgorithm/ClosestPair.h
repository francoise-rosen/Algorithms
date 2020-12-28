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
    
    /** @return pair of iterators to the closest pair of pointers within the strip
        Note that this changes the pair d!
     */
    template <typename ForwardIterator, typename T>
    std::pair<ForwardIterator, ForwardIterator> splitPair (ForwardIterator first, ForwardIterator last, ForwardIterator middle, std::pair<ForwardIterator, ForwardIterator> d) noexcept
    {
        T delta = dist(*d.first, *d.second);
        std::pair<ForwardIterator, ForwardIterator> closestPairFromSplit = d;
        std::vector<ForwardIterator> strip;
        for (ForwardIterator it = first; it != last; ++it)
        {
            if (abs ((*it).x - (*middle).x) < delta)
            {
                strip.push_back(it);
            }
        }
        
        /** Sort the strip items in respect to their y coordinate. */
        sort (strip.begin(), strip.end(), [] (ForwardIterator a, ForwardIterator b) { return (*a).y < (*b).y;});
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
    
    template <typename ForwardIterator, typename T>
    std::pair<ForwardIterator, ForwardIterator> findClosestDistance (ForwardIterator first, ForwardIterator last)
    {
        //std::sort (first, last, SortX<T>());
        syfo::msort (first, last, SortX<T>());
        return closestPair<ForwardIterator, T> (first, last);
    }
    
//    template <typename ForwardIterator, typename T>
//    std::pair<ForwardIterator, ForwardIterator> findClosestDistance (std::vector<syfo::Point<T>>& points)
//    {
//        sortBy (points, true);
//        // how to move it?
//        //std::vector<Point<T>> pointsY {sortBy (points, false)};
//
//        return closestPair<ForwardIterator, T> (points.begin(), points.end());
//    }
}


#endif /* ClosestPair_h */
