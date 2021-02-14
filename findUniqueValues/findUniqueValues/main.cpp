//
//  main.cpp
//  findUniqueValues
//
//  Created by syfo_dias on 16/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>

/**
  Counts unique values in the array. If array is sorted, it takes O(n) time
 */

void makeSet (std::vector<int>& result, std::vector<int>& v)
{
    if (v.size() <= 1)
        return;
    std::sort (v.begin(), v.end()); // O (nlogn)
    auto current = v.begin();
    auto next = v.begin() + 1;
    while (current != v.end()) // O (n)
    {
        if (*current == *next)
        {
            while ((*current == *next) && (next != v.end()))
                ++next;
            current = next;
        }
        else
        {
            result.push_back (*current);
            ++current;
        }
        ++next;
    }
}

std::vector<int> findUniqueValues (const std::vector<std::vector<int>>& setOfArrays)
{
    std::vector<int> superVector;
    for (auto p : setOfArrays)
    {
        auto pSize = p.size();
        auto vSize = superVector.size();
        superVector.resize(vSize + pSize);
        std::copy (p.begin(), p.end(), superVector.begin() + vSize);
    }
    std::vector<int> res;
    makeSet(res, superVector);
    return res;
}

void basicTest()
{
    std::vector<int> v {1, 21, 3, 3, 3, 3, 4, 5, 22, 22, 23, 23, 23};
    //std::vector<int> v {1, 21};
    std::vector<int> res;
    makeSet (res, v);
    for (auto p: res)
    {
        std::cout << p << '\n';
    }
}

void basicTest2()
{
    std::vector<int> v1 {2, 9, 11};
    std::vector<int> v2 {0, 1, 11};
    std::vector<int> v3 {0, 1, 7};
    std::vector<std::vector<int>> testSet {v1, v2, v3};
    
    std::vector<int> res = std::move (findUniqueValues (testSet));
    for (auto p : res)
    {
        std::cout << p << '\n';
    }
}

int main(int argc, const char * argv[]) {
    try
    {
        basicTest();
        basicTest2();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "something bad happened\n";
        return 2;
    }
    return 0;
}
