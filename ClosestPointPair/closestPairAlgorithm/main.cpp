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
#include "MergeSort.h"


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
    
    std::pair<ForwardIterator, ForwardIterator> closestPair = syfo::findClosestDistance<ForwardIterator, double> (points.begin(), points.end());
    
    syfo::msort (points.begin(), points.end(), syfo::SortX<T>());
    testPrint (points);
    
    std::pair<ForwardIterator, ForwardIterator> closestPairBruteForce = bruteForce<ForwardIterator, double> (points.begin(), points.end());
    
    /** Test against BruteForce algo, which we assume is correct by definition. */
    if (syfo::dist<ForwardIterator, double> (closestPair) == syfo::dist<ForwardIterator, double> (closestPairBruteForce))
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

//====================================================================================
// BASIC TESTS
//====================================================================================

template <typename ForwardIterator>
void printAll (ForwardIterator first, ForwardIterator last)
{
    while (first != last)
    {
        std::cout << *first << '\n';
        ++first;
    }
}

// FUNCTION TO COMPARE BRUTE FORCE AND CLOSEST PAIR ALGORITHM RESULTS
template <typename ForwardIterator, typename T>
bool closestPairCompare (ForwardIterator first, ForwardIterator last, const std::string test_label = "")
{
    bool testStatus {false};
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance (first, last)};
    using Type = typename std::iterator_traits<ForwardIterator>::value_type;
    std::vector<Type> array_copy (size);
    syfo::copy (first, last, array_copy.begin());
    
    /** Does not compile if I use an array. With vector it does. */
    std::pair<ForwardIterator, ForwardIterator> closestPairBruteForce = bruteForce<ForwardIterator, double> (array_copy.begin(), array_copy.end());
    std::pair<ForwardIterator, ForwardIterator> closestPairAlgorithm = syfo::findClosestDistance<ForwardIterator, T> (first, last);
    
    testStatus = (syfo::dist<ForwardIterator, T> (closestPairBruteForce) == syfo::dist<ForwardIterator, T>(closestPairAlgorithm)) ? true : false;
    
    if (testStatus)
    {
        std::string message {"Test passed"};
        std::cout << "Pair: " << *closestPairAlgorithm.first << " and " << *closestPairAlgorithm.second << '\n';
    }
    else
    {
        std::string message {"Test failed"};
        std::cout << "Found pair: " << *closestPairAlgorithm.first << " and " << *closestPairAlgorithm.second << '\n'
        << "Must be: " << *closestPairBruteForce.first << " and " << *closestPairBruteForce.second << '\n';
    }
    return testStatus;
}

// INPUTS
/** Test 1 - the closest pair is always split if sorted by x,
    so split function must find the closest distance. */
void test1()
{
    std::vector<syfo::Point<double>> points
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
    using iterator_type = std::vector<syfo::Point<double>>::iterator;
    printAll (points.begin(), points.end());
    bool test = closestPairCompare<iterator_type, double> (points.begin(), points.end(), "simple_copy");
    if (test)
        std::cout << "Passed\n";
    else
        std::cout << "Failed\n";
}

int main(int argc, const char * argv[]) {
    
    try {
        test1();
        //testBruteForce();
        
        
    
    } catch (std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
    
    return 0;
}
