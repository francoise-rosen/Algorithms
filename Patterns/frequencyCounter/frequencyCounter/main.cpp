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

/** linear time O(n). */
bool frequencyCounter (const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    if (arr1.size() != arr2.size())
        return false;
    std::map<int, int> elemArr1;
    std::map<int, int> elemArr2;
    bool match = false;
    return match;
}


int main(int argc, const char * argv[]) {
    try {
        std::vector<int> a {1, 2, 3};
        std::vector<int> b {4, 1, 9};
        std::vector<int> c {4, 1, 4};
        frequencyCounterNaive(a, b);
        assert (frequencyCounterNaive(a, b) == true);
        assert (frequencyCounterNaive(a, c) == false);
        assert (frequencyCounterNaive(c, b) == false);
        assert (frequencyCounterNaive(a, a) == false);
        std::cout << "Done\n";
        
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
