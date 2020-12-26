//
//  main.cpp
//  MergeSortAlgorithm
//
//  Created by syfo_dias on 26/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#include <iostream>
#include "mergeSort.h"
#include <vector>
#include <array>
#include <string>
#include <map>
#include <list>
#include <forward_list>

/** Very basic error handling to keep track on elements
    that are not sorted correctly.
 */
class SortError
{
public:
    SortError() {}
    SortError (const std::string& s, int i, int val, int val_exp)
    :message {s}, index {i}, value {val}, value_expected {val_exp}
    {}
    ~SortError() {}
    
    std::string what()
    {
        return message + std::to_string(index) + " value obtained " + std::to_string(value) +  " value expected " + std::to_string(value_expected);
    }
private:
    std::string message;
    int index;
    int value;
    int value_expected;
};

//============================================================================
// TESTS
//============================================================================

/** This test will not terminate the program,
 it will merely print out failed elements and their indecies.
 */
template <typename ForwardIterator>
void testSortAndPrint (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance(first, last)};
    typename std::iterator_traits<ForwardIterator>::value_type c_copy[size];
    syfo::copy (first, last, c_copy + 0);
    std::sort (c_copy + 0, c_copy + size);
    syfo::msort (first, last);
    int index {0};
    while (first != last)
    {
        if (*first == c_copy[index])
            std::cout << *first << " : " << c_copy[index] << '\n';
        else
            std::cout << "Failed at index " << index << " : " << *first
            << " != " << c_copy[index] << '\n';
        ++first;
        ++index;
    }
}

/** Accepts containers with begin(), end() inerators. */
template <typename ForwardIterator>
void testMergeSort (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance(first, last)};
    typename std::iterator_traits<ForwardIterator>::value_type c_copy[size];
    syfo::copy (first, last, c_copy + 0);
    std::sort (c_copy + 0, c_copy + size);
    syfo::msort (first, last);
    int index {0};
    while (first != last)
    {
        if (*first != c_copy[index])
            throw SortError ("Failed! Wrong result at index ", index, *first, c_copy[index]);
        std::cout << *first << '\n';
        ++first;
        ++index;
    }
    std::cout << "Passed!\n";
}

/** Accepts containers with begin(), end() inerators.
 This is the fuction for dynamic arrays, so it must not throw exceptions!
 */
template <typename ForwardIterator>
void testMergeSortNoExcept (ForwardIterator first, ForwardIterator last, bool& testStatus, SortError& se) noexcept
{
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance(first, last)};
    typename std::iterator_traits<ForwardIterator>::value_type c_copy[size];
    syfo::copy (first, last, c_copy + 0);
    std::sort (c_copy + 0, c_copy + size);
    syfo::msort (first, last);
    int index {0};
    while (first != last)
    {
        if (*first != c_copy[index])
        {
            testStatus = false;
            se = SortError ("Failed! Wrong result at index ", index,  *first, c_copy[index]);
            return;
        }
        std::cout << *first << '\n';
        ++first;
        ++index;
    }
    std::cout << "Passed!\n";
}


void basicTests()
{
    /** Special case - empty container. */
    std::forward_list<int> zero;
    testSortAndPrint (zero.begin(), zero.end());
    
    /** Special case - 1 item. */
    int one[1] {9};
    int one_size = sizeof (one) / sizeof (one[0]);
    testSortAndPrint (one + 0, one + one_size);
    
    /** Two items. */
    int a[2] {1, 0};
    int a_size = sizeof (a) / sizeof (a[0]);
    testSortAndPrint (a + 0, a + a_size);
    
    /** Array with n items (Random Access Iterator) */
    int a2[4] {8, 17, -1, 0};
    int a2_size = sizeof (a2) / sizeof (a2[0]);
    testSortAndPrint (a2, a2 + a2_size);
    int popArray[9] {9, 1, 0, -2, -10000, 10000, 6, 2, 256};
    testMergeSort (popArray, popArray + 9);
    
    /** Vector (Random Access Iterator). */
    std::vector<double> v {0.0, 0.1, 9.0, 2.3444, 11.2, -4.3};
    testMergeSort (v.begin(), v.end());
    
    /** Sorted vector (Random Access Iterator). */
    std::vector<float> vf {10.0f, 11.2f, 33.0f, 89.0f, 112.0f, 235.0f};
    testSortAndPrint (vf.begin(), vf.end());
    
    /** Reversed vector (Random Access Iterator). */
    std::vector<int> vint {19, 17, 11, 7, 4, 2, 0};
    testSortAndPrint (vint.begin(), vint.end());
    
    /** Vector with repeated values. */
    std::vector<int> vint_repeat {2, 2, 2, 2, 0, 0, 0};
    testSortAndPrint (vint_repeat.begin(), vint_repeat.end());
    
    /** std::array (Random Access Iterator). */
    std::array<int, 10> arr {8, 16, 2, 4, 256, 128, 999, -999, 7, 14};
    testSortAndPrint (arr.begin(), arr.end());
    
}

void testDynamicArray(const int& min, const int& max, const unsigned& arraySize, const unsigned& numTest, bool terminateOnFirstFail = true)
{
    /** Dynamic array (Random Access Iterator) */
    int* dyn_array = new int[arraySize];
    bool testStatus {true};
    SortError se;
    testMergeSortNoExcept (dyn_array, dyn_array+(arraySize), testStatus, se);
    delete[] dyn_array;
    if (! testStatus)
        throw se;
}

void testLIST()
{
    /** List (bidirectional iterator) */
    std::list<int> lst {99,23,1,0,-1,9999};
    testMergeSort (lst.begin(), lst.end());
    for (auto elem : lst)
        std::cout << elem << " ";
    std::cout << '\n';
    
    /** Forward list (Forward iterator) */
    std::forward_list<double> flst {12.2, 0.1, -54.3333, 0.2, 0.001, -0.000001};
    testMergeSort (flst.begin(), flst.end());
    for (auto elem: flst)
        std::cout << elem << " ";
    std::cout << '\n';
}

void testString()
{
    /** std::string. */
    std::string str {"Confiled"};
    testMergeSort (str.begin(), str.end());
    /** read test to strings and pass them to test. */
}

int main(int argc, const char * argv[]) {
    
    try {
        basicTests();
        testLIST();
    }
    catch (SortError& se)
    {
        std::cerr << se.what() << '\n';
        return 1;
    }
    
    return 0;
}

