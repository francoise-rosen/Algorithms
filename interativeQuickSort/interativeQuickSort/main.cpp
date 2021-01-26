//
//  main.cpp
//  interativeQuickSort
//
//  Created by syfo_dias on 12/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include "quickSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "bubbleSort.h"

template <typename C>
void printAll (const C& container)
{
    if (container.begin() == container.end())
        return;
    std::cout << "[" << container[0] << ",";
    for (int i = 1; i < container.size() - 1; ++i)
    {
        if (i%10 == 0)
            std::cout << '\n';
        std::cout << container[i] << ",";
    }
    std::cout << container[container.size() - 1] << "]";
        
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

/** Sort identifiers. */
enum class Algorithm {Bubble, Selection, Insertion, Quick, MergeSort, HeapSort};

/** Helper functions. */
template <typename ForwardIterator>
bool isSequenceAscending (ForwardIterator first, ForwardIterator last)
{
    ForwardIterator next = first;
    ++next;
    while (next != last)
    {
        if (next < first)
            return false;
        ++next; ++first;
    }
    return true;
}

template <typename ForwardIterator>
bool isSequenceDescending (ForwardIterator first, ForwardIterator last)
{
    ForwardIterator next = first;
    ++next;
    while (next != last)
    {
        if (next > first)
            return false;
        ++next; ++first;
    }
    return true;
}

/** Helper that runs tested functions and records to log or throws error if failed. */
template <typename ForwardIterator>
void testSort (Algorithm algo, ForwardIterator first, ForwardIterator last, std::ofstream& ofs_log, const std::string& test_label = "", bool terminateOnFirstFail = false)
{
    bool testStatus = true;
    typename std::iterator_traits<ForwardIterator>::difference_type size {std::distance(first, last)};
    typename std::iterator_traits<ForwardIterator>::value_type c_copy[size];
    
    /** replace this with pointer?. */
    if (algo == Algorithm::Bubble)
    {
        bubbleSort (first, last);
    }
    else if (algo == Algorithm::Selection)
    {
        selectionSort (first, last);
    }
    else if (algo == Algorithm::Insertion)
    {
        insertionSort (first, last);
    }
    else if (algo == Algorithm::Quick)
    {
        quickSort (first, last);
    }
    else
    {
        throw std::runtime_error ("Unidentified test case");
    }
    
    /** Check the result. */
    
}
// SPECIAL CASES

void quickSortTest1()
{
    std::vector<int> v {9, 19, 0, 2, 1, 11, 290, 521, 72, 3, -5};
    std::vector<int> sortedV {-5, 0, 1, 2, 3, 9, 11, 19, 72, 290, 521 };
    int numRec1 = sfd::qsort (v.begin(), v.end());
    int numRec2 = sfd::qsort (sortedV.begin(), sortedV.end());
    printAll(v);
    std::cout << "\nNum of recursive calls in v of size: " << v.size() << " is " <<  numRec1 << '\n';
    printAll(sortedV);
    
    std::cout << "\nNum of recursive calls in sorted v of size: " << sortedV.size() << " is " << numRec2 << '\n';
}

void testCounter ()
{
    sfd::Counter c;
    for (int i = 0; i < 10; ++i)
        ++c;
    std::cout << c.get() << '\n';
    
}

// RANDOM FILL

void testQuickSortWithRandomFill (const int& numRolls, const int& containerSize)
{
    
}

// PERFORMANCE TESTS

int main(int argc, const char * argv[]) {
    try {
        quickSortTest1();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
