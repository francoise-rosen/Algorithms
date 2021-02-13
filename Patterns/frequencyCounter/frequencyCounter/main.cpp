//
//  main.cpp
//  frequencyCounter
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "naiveCounter.h"
#include "freqCounterMap.h"
#include "freqCounterUMap.h"
#include "string"
/**
   Find if elements of second array are squared elements of first
   Frequency must match
 */

// helper to print map
void printMap (const std::map<int, int> myMap)
{
    for (auto elem : myMap)
    {
        std::cout << elem.first << " = > " << elem.second << '\n';
    }
}

void printUnorderedMap (const std::unordered_map<int, int> myMap)
{
    for (auto elem : myMap)
    {
        std::cout << elem.first << " = > " << elem.second << '\n';
    }
}

bool isAnagram (const std::string& a, const std::string& b)
{
    return true;
}

void tryNaive()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    sfd::frequencyCounterNaive(a, b);
    assert (sfd::frequencyCounterNaive(a, b) == true);
    assert (sfd::frequencyCounterNaive(a, c) == false);
    assert (sfd::frequencyCounterNaive(c, b) == false);
    assert (sfd::frequencyCounterNaive(a, a) == false);
    assert (sfd::frequencyCounterNaive(c, d) == true);
    std::cout << "Nainve - Done\n";
}

void tryCounter1()
{
    using C = std::vector<int>;
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    sfd::frequencyCounterMap<C, int> (a, c);
    sfd::frequencyCounterMap<C, int> (a, b);
    bool ab = sfd::frequencyCounterMap<C, int>(a, b);
    bool ac = sfd::frequencyCounterMap<C, int>(a, c);
    bool cb = sfd::frequencyCounterMap<C, int>(c, b);
    bool aa = sfd::frequencyCounterMap<C, int>(a, a);
    bool cd = sfd::frequencyCounterMap<C, int>(c, d);
    assert (ab == true);
    assert (ac == false);
    assert (cb == false);
    assert (aa == false);
    assert (cd == true);
    std::cout << "Counter - Done\n";
}

void tryCounter2()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    std::vector<int> e {16, 16, 1, 1};
    sfd::frequencyCounterUMap (c, d);
    assert (sfd::frequencyCounterUMap(a, b) == true);
    assert (sfd::frequencyCounterUMap(a, c) == false);
    assert (sfd::frequencyCounterUMap(c, b) == false);
    assert (sfd::frequencyCounterUMap(a, a) == false);
    assert (sfd::frequencyCounterUMap(c, d) == true);
    assert (sfd::frequencyCounterUMap(c, e) == false);
    std::cout << "Counter 2 - Done\n";
}

int main(int argc, const char * argv[]) {
    try {
        tryNaive();
        tryCounter1();
        tryCounter2();
        
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
