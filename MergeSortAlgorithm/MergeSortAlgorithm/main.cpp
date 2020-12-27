//
//  main.cpp
//  MergeSortAlgorithm
//
//  Created by syfo_dias on 26/12/2020.
//  Copyright © 2020 syfo_dias. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "mergeSort.h"
#include <vector>
#include <array>
#include <string>
#include <map>
#include <list>
#include <random>
#include <forward_list>

/** Random number generator. */
namespace Marsenne
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    /** Set the generator. */
    std::mt19937 generator (static_cast<std::mt19937::result_type>(seed));
}

int getIntValueInRange (const int& min, const int& max)
{
    std::uniform_int_distribution<> value {min, max};
    return value (Marsenne::generator);
}

/** Very basic error handling to keep track on elements
    that are not sorted correctly.
 */
class SortError
{
public:
    SortError() {}
    SortError (const std::string& s, const std::string& i, const std::string& val, const std::string& val_exp)
    :message {s}, index {i}, value {val}, value_expected {val_exp}
    {}
    ~SortError() {}
    
    const std::string what() const
    {
        return message + index + " value obtained " + value +  " value expected " + value_expected;
    }
    
    friend std::ostream& operator<< (std::ostream& os, const SortError& se)
    {
        os << se.what();
        return os;
    }
    
private:
    std::string message;
    std::string index;
    std::string value;
    std::string value_expected;
};

//============================================================================
// TESTS
//============================================================================

/** Accepts containers with begin(), end() inerators.
    This can throw an exception right away.
 */
template <typename ForwardIterator>
void testMergeSort (ForwardIterator first, ForwardIterator last, std::ofstream& ofs_log, const std::string& test_label = "", bool terminateOnFirstFail = false)
{
    bool testStatus = true;
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
            std::string error_message {(test_label == "") ? "Failed! Index : Value : Expected value" : std::string("Failed: " + test_label + " Index : Value : Expected value ")};
            SortError sortError {error_message, std::to_string (index), std::to_string (*first), std::to_string (c_copy[index])};
            if (! terminateOnFirstFail)
            {
                ofs_log << sortError << '\n';
            }
            else
            {
                throw sortError;
            }
        }
        ++first;
        ++index;
    }
    
    if (testStatus)
        ofs_log << "Passed: " <<test_label << '\n';
}

/** Accepts containers with begin(), end() inerators.
    This is the fuction for dynamic arrays, so it must not throw exceptions!
    If requested, it'll register the first error and will exit the function.
 */
template <typename ForwardIterator>
void testMergeSortNoExcept (ForwardIterator first, ForwardIterator last, bool& testStatus, SortError& sortError, std::ofstream& ofs, const std::string& test_label = "", bool terminateOnFirstFail = true) noexcept
{
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance(first, last)};
    typename std::iterator_traits<ForwardIterator>::value_type c_copy[size];
    syfo::copy (first, last, c_copy + 0);
    std::sort (c_copy + 0, c_copy + size);
    syfo::msort (first, last);
    int index {0};
    while (first != last)
    {
        /** this will register an error, and save it in log or terminate the function. */
        if (*first != c_copy[index])
        {
            testStatus = false;
            sortError = SortError ("Failed! Wrong result at index ", std::to_string (index),  std::to_string (*first), std::to_string (c_copy[index]));
            if (! terminateOnFirstFail)
                ofs << sortError << '\n';
            else
                return;
        }
        ++first;
        ++index;
    }
    if (testStatus)
        ofs << "Passed: " << test_label << '\n';
}

/** Basic tests for Random Access Iterators. */
void basicTests (std::ofstream& ofs_log)
{
    /** Special case - empty container. */
    std::forward_list<int> zero;
    testMergeSort (zero.begin(), zero.end(), ofs_log, "Zero sized container");
    
    /** Special case - 1 item. */
    int one[1] {9};
    int one_size = sizeof (one) / sizeof (one[0]);
    testMergeSort (one + 0, one + one_size, ofs_log, "One elem container");
    
    /** Two items. */
    int a[2] {1, 0};
    int a_size = sizeof (a) / sizeof (a[0]);
    testMergeSort (a + 0, a + a_size, ofs_log, "Two elements array");
    
    /** Array with n items (Random Access Iterator) */
    int a2[] {8, 17, -1, 0};
    int a2_size = sizeof (a2) / sizeof (a2[0]);
    testMergeSort (a2, a2 + a2_size, ofs_log, "Array with N elements", false);
    int popArray[] {9, 1, 0, -2, -10000, 10000, 6, 2, 256};
    int popArray_sz = sizeof (popArray) / sizeof(popArray[0]);
    testMergeSort (popArray, popArray + popArray_sz, ofs_log, "Array with N elements", false);
    
    /** Vector (Random Access Iterator). */
    std::vector<double> v {0.0, 0.1, 9.0, 2.3444, 11.2, -4.3};
    testMergeSort (v.begin(), v.end(), ofs_log, "Vector", false);
    
    /** Sorted vector (Random Access Iterator). */
    std::vector<float> vf {10.0f, 11.2f, 33.0f, 89.0f, 112.0f, 235.0f};
    testMergeSort (vf.begin(), vf.end(), ofs_log, "Sorted vector", false);
    
    /** Reversed vector (Random Access Iterator). */
    std::vector<int> vint {19, 17, 11, 7, 4, 2, 0};
    testMergeSort (vint.begin(), vint.end(), ofs_log, "Reversed vector", false);
    
    /** Vector with repeated values. */
    std::vector<int> vint_repeat {2, 2, 2, 2, 0, 0, 0};
    testMergeSort (vint_repeat.begin(), vint_repeat.end(), ofs_log, "Multiple entries with the same value", false);
    
    /** std::array (Random Access Iterator). */
    std::array<int, 10> arr {8, 16, 2, 4, 256, 128, 999, -999, 7, 14};
    testMergeSort (arr.begin(), arr.end(), ofs_log, "std::array", false);
    
}

void testString (std::ofstream& ofs_log)
{
    /** std::string. */
    std::string str {"Confiled"};
    testMergeSort (str.begin(), str.end(), ofs_log, "string");
    /** read test to strings and pass them to test. */
}

/** Basic test for Bidirectional and Forward Iterators. */
void testList (std::ofstream& ofs_log)
{
    /** List (bidirectional iterator) */
    std::list<int> lst {99,23,1,0,-1,9999};
    testMergeSort (lst.begin(), lst.end(), ofs_log, "doubly linked list");
    
    /** Forward list (Forward iterator) */
    std::forward_list<double> flst {12.2, 0.1, -54.3333, 0.2, 0.001, -0.000001};
    testMergeSort (flst.begin(), flst.end(), ofs_log, "forward list");
}

void testRandom()
{
    for (int i = 0; i < 10; ++i)
    {
        std::cout << getIntValueInRange (std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) << '\n';
    }
}

/** This is tricky, since it uses new and delete. Only for testing purposes. */
void testDynamicArray (const int& min, const int& max, const unsigned& arraySize, std::ofstream& log, const std::string& test_label, bool terminateOnFirstFail)
{
    /** Dynamic array (Random Access Iterator) */
    int* dyn_array = new int[arraySize];
    bool testStatus {true};
    SortError se;
    testMergeSortNoExcept (dyn_array, dyn_array+(arraySize), testStatus, se, log, test_label);
    delete[] dyn_array;
    if ( (terminateOnFirstFail) && (! testStatus))
        throw se;
}

void readLog (const std::string& file_name)
{
    std::ifstream ifs_log {file_name};
    if (!ifs_log)
        throw std::runtime_error ("Bad file for reading");

    if (ifs_log.is_open())
    {
        for (char ch; ifs_log.get (ch);)
        {
            std::cout << ch;
        }
    }
    if (! ifs_log.eof())
        throw std::runtime_error ("Bad reading");
}

void runTestsWithRandomFill (const int& nRolls, const int& min, const int& max, const int& size, std::ofstream& ofs_log, bool terminateOnFirstFail = false)
{
    int roll {0};
    while (roll < nRolls)
    {
        std::string test_label = "Random Fill. Test # " + std::to_string (roll);
        testDynamicArray (min, max, 100, ofs_log, test_label, false);
        ++roll;
    }
}

void runAllTests()
{
    /** FILE. */
    const std::string file = "log.txt";
    std::ofstream ofs_log {file};
    if (!ofs_log)
        throw std::runtime_error ("File does not exist!");
    basicTests (ofs_log);
    runTestsWithRandomFill (100, -10000, 10000, 10, ofs_log);
    ofs_log.close();
    readLog (file);
}

void testLog()
{
    std::string file_name = "log.txt";
    std::ofstream ofs_log {file_name};
    if (! ofs_log)
        throw std::runtime_error ("bad file \"log.txt\"");
    for (int i = 0; i < 10; ++i)
    {
        int temp = getIntValueInRange (0, 256);
        ofs_log << "Random number: " << temp << '\n';
        std::cout << temp << '\n';
        
    }
    ofs_log.close();
    readLog (file_name);
}

int main(int argc, const char * argv[]) {
    
    try {
        runAllTests();
    }
    catch (SortError& se)
    {
        std::cerr << se.what() << '\n';
        return 1;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    
    return 0;
}

