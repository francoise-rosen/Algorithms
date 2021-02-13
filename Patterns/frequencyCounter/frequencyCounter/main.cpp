//
//  main.cpp
//  frequencyCounter
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <map>
/**
   Find if elements of second array are squared elements of first
   Frequency must match
 */

/** Naive - quadratic time. */
bool frequencyCounterNaive (const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    if (arr1.size() != arr2.size())
        return false;
    
    std::vector<bool> visited (arr2.size(), false);
    bool match = false;
    for (auto elem : arr1)
    {
        for (int i = 0; i < arr2.size(); ++i)
        {
            if (elem * elem == arr2[i])
            {
                if (! visited[i])
                {
                    visited[i] = true;
                    match = true;
                    break;
                }
            }
            else
                match = false;
        }
        if (match == false)
            return false;
    }
    return true;
}

// helper to print map
void printMap (const std::map<int, int> myMap)
{
    for (auto elem : myMap)
    {
        std::cout << elem.first << " = > " << elem.second << '\n';
    }
}

/** linear time O(n). */
bool frequencyCounter (const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    if (arr1.size() != arr2.size())
        return false;
    std::map<int, int> elemArr1;
    std::map<int, int> elemArr2;
    for (auto elem : arr1) // O(n) -> O (n * log(n)) :(
    {
        (elemArr1.count(elem) > 0) ? elemArr1[elem] += 1 : elemArr1[elem] = 1; // O log(n) -> O (log(n))
    }
    
    for (auto elem : arr2) // O(n)
    {
        elemArr2[elem] += 1; // O (log(n)), but is not save, assuming default int is not 0!
    }
    //printMap(elemArr1);
    //printMap(elemArr2);
    if (elemArr1.size() != elemArr2.size())
        return false;
    typename std::map<int, int>::const_iterator it1, it2;
    while (it1 != elemArr1.end())
    {
        if ( (it1->first * it1->first) != (it2->first) || (it1->second) != (it2->second))
            return false;
        ++it1; ++it2;
    }

    return true;
}

void tryNaive()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    frequencyCounterNaive(a, b);
    assert (frequencyCounterNaive(a, b) == true);
    assert (frequencyCounterNaive(a, c) == false);
    assert (frequencyCounterNaive(c, b) == false);
    assert (frequencyCounterNaive(a, a) == false);
    assert (frequencyCounterNaive(c, d) == true);
    std::cout << "Nainve - Done\n";
}

void tryCounter1()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    frequencyCounter(a, c);
    assert (frequencyCounterNaive(a, b) == true);
    assert (frequencyCounterNaive(a, c) == false);
    assert (frequencyCounterNaive(c, b) == false);
    assert (frequencyCounterNaive(a, a) == false);
    assert (frequencyCounterNaive(c, d) == true);
    std::cout << "Counter - Done\n";
}


int main(int argc, const char * argv[]) {
    try {
        tryNaive();
        tryCounter1();
        
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
