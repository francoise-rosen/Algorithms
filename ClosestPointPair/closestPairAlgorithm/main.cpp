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
#include <random>
#include <array>
#include "ClosestPair.h"
#include "MergeSort.h"

//====================================================================================
// Basic Random Number generator
//====================================================================================
namespace Random
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen (static_cast<std::mt19937::result_type>(seed));
}

template <typename T>
T randomValueInRange (const T& min, const T& max)
{
    std::uniform_real_distribution<T> d {min, max};
    return d (Random::gen);
}

template <>
int randomValueInRange (const int& min, const int& max)
{
    std::uniform_int_distribution<> d {min, max};
    return d (Random::gen);
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
void test1(std::ofstream& ofs_log, bool terminateOnFailure = false)
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
    bool status = closestPairCompare<iterator_type, double> (points.begin(), points.end(), ofs_log, "simple_copy");
    if (! status)
        throw std::runtime_error ("Test failed. Terminating. See log for details" );
}

/** Test 2. All x coordinates are the same. */
void test2 (std::ofstream& ofs_log, bool terminateOnFailure = false)
{
    std::vector<syfo::Point<int>> p {
        {1, 2},
        {1, 12},
        {1, 34},
        {1, 35}
    };
    using iter = std::vector<syfo::Point<int>>::iterator;
    bool status = closestPairCompare<iter, int> (p.begin(), p.end(), ofs_log, "same x coordinates");
    if (! status)
        throw std::runtime_error ("Test failed. Terminating. See log for details" );
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
    bool status = closestPairCompare<iter, int> (p.begin(), p.end(), ofs_log, "same y coordinates");
    if (! status)
        throw std::runtime_error ("Test failed. Terminating. See log for details" );
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
    bool status = closestPairCompare<iter, int> (p.begin(), p.end(), ofs_log, "all points are the same");
    if (! status)
        throw std::runtime_error ("Test failed. Terminating. See log for details" );
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
    bool status = closestPairCompare<iter, float> (p.begin(), p.end(), ofs_log, "all points are equally spaced");
    if (! status)
        throw std::runtime_error ("Test failed. Terminating. See log for details" );
}

/** Test 6. Positive and negative values of x and y. */
void test6 (std::ofstream& ofs_log, const int& numRolls, int size, bool terminateOnFailure = false)
{
    using iter = std::vector<syfo::Point<float>>::iterator;
    for (int i = 0; i < numRolls; ++i)
    {
        std::vector<syfo::Point<float>> p;
        for (int j = 0; j < size; ++j)
        {
            float fx = randomValueInRange<float> (-300.0f, 300.0f);
            float fy = randomValueInRange<float> (-100.0f, 100.0f);
            p.push_back({fx, fy});
        }
        std::string message = "Test 6. Random points #" + std::to_string(i);
        bool status = closestPairCompare<iter, float> (p.begin(), p.end(), ofs_log, message);
        if (! status)
            throw std::runtime_error ("Test failed. Terminating. See log for details" );
    }
}

/** Test 7. Very narrow spacing. */
void test7 (std::ofstream& ofs_log, const int& numRolls, int size, bool terminateOnFailure = false)
{
    using iter = std::vector<syfo::Point<long double>>::iterator;
    for (int i = 0; i < numRolls; ++i)
    {
        std::vector<syfo::Point<long double>> p;
        for (int j = 0; j < size; ++j)
        {
            long double dx = randomValueInRange <long double> (0.00001, 0.00002);
            long double dy = randomValueInRange <long double> (0.00001, 0.00002);
            p.push_back ({dx, dy});
        }
        std::string message = "Test 7. Random points #" + std::to_string(i);
        bool status = closestPairCompare<iter, long double> (p.begin(), p.end(), ofs_log, message);
        if (! status)
            throw std::runtime_error ("Test failed. Terminating. See log for details" );
    }
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
    test6 (ofs_log, 100, 20);
    test7 (ofs_log, 100, 200);
}

void testRandom()
{
    double d = randomValueInRange<double> (0.0, 1.0);
    float f = randomValueInRange<float> (0.0f, 1.0f);
    int i = randomValueInRange (1, 11);
    std::cout << i << '\n' << f << '\n' << d << '\n';
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
        //readLog (file);
        testRandom();
    
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';;
        return 1;
    }
    
    return 0;
}
