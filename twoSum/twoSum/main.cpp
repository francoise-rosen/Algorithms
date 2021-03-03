//
//  main.cpp
//  twoSum
//
//  Created by syfo_dias on 27/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using vPair = std::set<std::pair<int, int>>;

vPair twoSum (const std::vector<int>& array, int s)
{
    vPair result;
    std::unordered_map<int, bool> hashTable;
    
    for (auto elem : array)
    {
        if (hashTable.find(s - elem) != hashTable.end())
        {
            result.insert (std::make_pair (elem, s - elem));
            return result;
        }
        hashTable[elem] = true;
    }
    return result;
}



int main(int argc, const char * argv[]) {
    std::vector<int> array {3, 5, 2, -4, 8, 11, 11, -4};
    vPair res = twoSum(array, 7);
    for (auto p : res)
    {
        std::cout << "[ " << p.first << " " << p.second << " ]\n";
    }
    
    return 0;
}
