//
//  freqCounterUMap.h
//  frequencyCounter
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#ifndef freqCounterUMap_h
#define freqCounterUMap_h
#include <unordered_map>

namespace sfd {
    /** Linear time?
     Based on this:
     https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
     */
    
    bool frequencyCounterUMap (const std::vector<int>& arr1, const std::vector<int>& arr2)
    {
        if (arr1.size() != arr2.size())
            return false;
        std::unordered_map<int, int> u_map1 {arr1.size()}, u_map2 {arr2.size()}; // O(1)
        
        // frequency counter - O(n) average.
        for (int i = 0; i < arr1.size(); ++i) // O (n)
        {
            ++u_map1[arr1[i]]; // operator[] - O(1) average, O(n) worst case
            ++u_map2[arr2[i]];
        }
        
        if (u_map1.size() != u_map2.size()) // O(1)
            return false;
        
        for (auto elem : u_map1)
        {
            if (u_map2.find (elem.first * elem.first) == u_map1.end()) // O(1) average, O(n) worst case
                return false;
            if (u_map2[elem.first * elem.first] != u_map1[elem.first]) // O(1) average, O(n) worst case
                return false;
        }
        return true;
    };
}

#endif /* freqCounterUMap_h */
