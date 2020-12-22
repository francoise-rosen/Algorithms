//
//  main.cpp
//  closestPairAlgorithm
//
//  Created by syfo_dias on 09/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include <math.h>
#include "ClosestPair.h"


void printPoints (const std::vector<syfo::Point<double>>& array, const std::string& label = "")
{
    std::cout << "Points ";
    if (label != "")
        std::cout << "sorted by " << label;
    std::cout << ":\n";
    for (auto p: array)
    {
        std::cout << p << '\n';
    }
}

/** ACTUAL ALGORITHMS. */
template <typename T>
std::pair<syfo::Point<T>, syfo::Point<T>> bruteForce (const std::vector<syfo::Point<T>>& points)
{
    std::pair<syfo::Point<T>, syfo::Point<T>> closestPair;
    T smallestDistance = std::numeric_limits<T>::max();
    for (int i = 0; i < points.size(); ++i)
    {
        for (int j = i + 1; j < points.size(); ++j)
        {
            T temp = dist (points[i], points[j]);
            if (temp < smallestDistance)
            {
                smallestDistance = temp;
                closestPair = {points[i], points[j]};
            }
        }
    }
    return closestPair;
}

// This must be called if there are at least 2 points in container
template <typename ForwardIterator, typename T>
std::pair<ForwardIterator, ForwardIterator> bruteForce (ForwardIterator first, ForwardIterator last)
{
    T smallestDistance = std::numeric_limits<T>::max();
    std::pair<ForwardIterator, ForwardIterator> result;
    while (last != first)
    {
        for (ForwardIterator current = first + 1; current < last; ++current)
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
    
    std::cout << "MIN FINALE: " << delta << '\n';
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
    
    // find min distance of those
//    std::cout << "Left closest pair:"
//    << *leftPair.first << " " << *leftPair.second << '\n';
    T distanceLeft = dist (*leftPair.first, *leftPair.second);
    T distanceRight = dist (*rightPair.first, *rightPair.second);
    T d = std::min (distanceLeft, distanceRight);
    std::pair<ForwardIterator, ForwardIterator> closestPairFromPartition = (distanceLeft > distanceRight) ? rightPair : leftPair;
    std::pair <ForwardIterator, ForwardIterator> split = splitPair<ForwardIterator, T>(first, last, middle, closestPairFromPartition);
    if (dist (*split.first, *split.second) < d)
        closestPairFromPartition = split;
    return closestPairFromPartition;
    //return rightPair;
}

template <typename ForwardIterator, typename T>
std::pair<ForwardIterator, ForwardIterator> findClosestDistance (std::vector<syfo::Point<T>>& points)
{
    sortBy(points, true);
    // how to move it?
    //std::vector<Point<T>> pointsY {sortBy (points, false)};
    
    return closestPair<ForwardIterator, T> (points.begin(), points.end());
}

// TESTS

// TEST PRINT
template <typename T>
void testPrint (const std::vector<syfo::Point<T>>& v)
{
    for (auto p : v)
    {
        std::cout << p << '\n';
    }
}

// TEST BRUTE FORCE
template <typename T, typename ForwardIterator>
void testBruteForce()
{
    // this will pass w/o strip, because the closest pair
    // will always be on the right
//    std::vector<Point<T>> points
//    {
//        {0.0, 1.0},
//        {10.0, 10.0},
//        {8.9, 11},
//        {10, 60},
//        {2.2, 10.1},
//        {5, 0.1},
//        {5, -0.4},
//        {0.1, 19},
//        {7.2, 9.9},
//        {21.01, 21.008},
//        {21.01, 21.009}
//    };
    
    // this will fail tho
    std::vector<syfo::Point<T>> points
    {
        {0.0, 1.0},
        {10.0, 10.0},
        {28.9, 11},
        {100, 6},
        {2.2, 10.1},
        {5, 0.1},
        {5, -0.4},
        {0.1, 19},
        {7.2, 9.9},
        {21.01, 21.008},
        {21.01, 21.009}
    };
    
    // this will fail tho
//    std::vector<Point<T>> points
//    {
//        {0.0, 1.0},
//        {7.2, 9.9},
//        {100, 6},
//        {5, 0.1},
//        {5, -0.4},
//        {21.01, 21.008},
//        {21.01, 21.009}
//    };
    
    std::pair<ForwardIterator, ForwardIterator> closestPair = findClosestDistance<ForwardIterator, double> (points);
    
    sortBy (points);
    testPrint (points);
    
    std::pair<ForwardIterator, ForwardIterator> closestPairBruteForce = bruteForce<ForwardIterator, double> (points.begin(), points.end());
    if (closestPair == closestPairBruteForce)
    {
        std::cout << "Pair:\n" << *closestPair.first << " " << *closestPair.second << '\n';

        std::cout << "Distance: " << dist (*(closestPair.first), *(closestPair.second)) << '\n';
    }
    else
    {
        std::cout << "Failed!\n";
        std::cout << "Closest pair: " << *closestPair.first << " " << *closestPair.second << "\nDistance: " << dist (*(closestPair.first), *(closestPair.second))
        << "\nMust be:\n" << *closestPairBruteForce.first << " " << *closestPairBruteForce.second << "\nDistance: "
        << dist (*(closestPairBruteForce.first), *(closestPairBruteForce.second)) << '\n';
    }
    
//    std::cout << "Must be:\n" << *closestPairBruteForce.first << " " << *closestPairBruteForce.second << "\nDistance: "
//            << dist (*(closestPairBruteForce.first), *(closestPairBruteForce.second)) << '\n';
    
}

int main(int argc, const char * argv[]) {
    
    try {
        
        testBruteForce<double, typename std::vector<syfo::Point<double>>::iterator>();
    
    } catch (std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
    
    return 0;
}
