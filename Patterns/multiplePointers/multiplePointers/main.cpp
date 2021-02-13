//
//  main.cpp
//  multiplePointers
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>
#include "subZero.h"

void testSubZero ()
{
    using Iterator = typename std::vector<int>::const_iterator;
    std::vector<int> v {-4, -3, -2, 0, 1, 3, 7};
    std::pair<Iterator, Iterator> p = subZero<std::vector<int>> (v);
    if (p == std::pair<Iterator, Iterator>{v.end(), v.end()})
        std::cout << "no 0 sum!";
    else
    {
        int first = *p.first;
        int second = *p.second;
        std::cout << first << " " << second << '\n';
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    testSubZero();
    return 0;
}
