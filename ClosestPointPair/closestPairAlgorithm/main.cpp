//
//  main.cpp
//  closestPairAlgorithm
//
//  Created by syfo_dias on 09/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <math.h>
#include "ClosestPair.h"
#include "MergeSort.h"

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
bool closestPairCompare (ForwardIterator first, ForwardIterator last, std::ofstream& ofs_log, const std::string test_label = "")
{
    bool testStatus {false};
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance (first, last)};
    using Type = typename std::iterator_traits<ForwardIterator>::value_type;
    std::vector<Type> array_copy (size);
    syfo::copy (first, last, array_copy.begin());
    
    /** Does not compile if I use an array. With vector it does. */
    std::pair<ForwardIterator, ForwardIterator> closestPairBruteForce = syfo::bruteForce<ForwardIterator, double> (array_copy.begin(), array_copy.end());
    std::pair<ForwardIterator, ForwardIterator> closestPairAlgorithm = syfo::findClosestDistance<ForwardIterator, T> (first, last);
    
    testStatus = (syfo::dist<ForwardIterator, T> (closestPairBruteForce) == syfo::dist<ForwardIterator, T>(closestPairAlgorithm)) ? true : false;
    
    if (testStatus)
    {
        std::string message = "Passed: " + test_label;
        ofs_log << message
        << ". Pair: " << *closestPairAlgorithm.first << " and " << *closestPairAlgorithm.second << '\n';
    }
    else
    {
        std::string message = "Failed: " + test_label;
        ofs_log << message << ". Found pair: " << *closestPairAlgorithm.first << " and " << *closestPairAlgorithm.second << '\n'
        << "\nMust be: " << *closestPairBruteForce.first << " and " << *closestPairBruteForce.second << '\n';
    }
    return testStatus;
}

// INPUTS
/** Test 1 - the closest pair is always split if sorted by x,
    so split function must find the closest distance. */
void test1(std::ofstream& ofs_log, bool terminateOnFailure = true)
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
    closestPairCompare<iterator_type, double> (points.begin(), points.end(), ofs_log, "simple_copy");
}

/** Test 2. All x coordinates are the same. */
void test2 (std::ofstream& ofs_log, bool terminateOnFailure = true)
{
    std::vector<syfo::Point<int>> p {
        {1, 2},
        {1, 12},
        {1, 34},
        {1, 35}
    };
    using iter = std::vector<syfo::Point<int>>::iterator;
    closestPairCompare<iter, int> (p.begin(), p.end(), ofs_log, "same x coordinates");
}

/** Test 3. All y coordinates are the same. */
void test3 (std::ofstream& ofs_log, bool terminateOnFailure = true)
{
    std::vector<syfo::Point<int>> p {
        {10, 2},
        {1, 2},
        {11, 2},
        {4, 2},
        {5, 2}
    };
    using iter = std::vector<syfo::Point<int>>::iterator;
    closestPairCompare<iter, int> (p.begin(), p.end(), ofs_log, "same y coordinates");
}

/** Test 4. All points the same. */
void test4 (std::ofstream& ofs_log, bool terminateOnFailure = true)
{
    std::vector<syfo::Point<int>> p {
        {10, 10},
        {10, 10},
        {10, 10},
        {10, 10},
        {10, 10}
    };
    using iter = std::vector<syfo::Point<int>>::iterator;
    closestPairCompare<iter, int> (p.begin(), p.end(), ofs_log, "all points are the same");
}

/** Test 5. Equally spaced points. */
void test5 (std::ofstream& ofs_log, bool terminateOnFailure = true)
{
    std::vector<syfo::Point<float>> p {
        {1.0f, 1.0f},
        {2.0f, 2.0f},
        {3.0f, 3.0f},
        {4.0f, 4.0f},
        {5.0f, 5.0f}
    };
    using iter = std::vector<syfo::Point<float>>::iterator;
    closestPairCompare<iter, float> (p.begin(), p.end(), ofs_log, "all points are equally spaced");
}


void readLog (const std::string& file, bool readFailedOnly = false)
{
    std::ifstream ifs_log {file};
    if (! ifs_log)
    {
        const std::string message = "Bad file " + file;
        throw std::runtime_error (message);
    }
    
    if (readFailedOnly)
    {
        // check if the line starts with "Failed"
    }
    else
    {
        for (char ch; ifs_log.get (ch);)
        {
            std::cout << ch;
        }
    }
}

void runTests (std::ofstream& ofs_log)
{
    /** Tests. */
    test1 (ofs_log);
    test2 (ofs_log);
    test3 (ofs_log);
    test4 (ofs_log);
    test5 (ofs_log);
}

int main(int argc, const char * argv[]) {
    
    try {
        const std::string file {"log.txt"};
        
        /** Start log. */
        std::ofstream ofs_log {file};
        if (! ofs_log)
        {
            const std::string message = "Bad file name: " + file;
            throw std::runtime_error (message);
        }
        
        runTests (ofs_log);
        ofs_log.close();
        readLog (file);
    
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';;
        return 1;
    }
    
    return 0;
}
