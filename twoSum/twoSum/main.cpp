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

using Pair = std::vector<std::pair<int, int>>;

Pair twoSum (const std::vector<int>& array, int s)
{
    Pair result;
    std::unordered_map<int, int> hashTable;
    for (int i = 0; i < array.size(); ++i)
    {
        hashTable[array[i]];
    }
    
    for (auto elem : array)
    {
        if (hashTable.find(s - elem) != hashTable.end())
            result.push_back (std::make_pair (elem, s - elem));
    }
    return result;
}



int main(int argc, const char * argv[]) {
    std::vector<int> array {3, 5, 2, -4, 8, 11};
    Pair res = std::move (twoSum(array, 7));
    for (auto p : res)
    {
        std::cout << "[ " << p.first << " " << p.second << " ]\n";
    }
    
    return 0;
}
