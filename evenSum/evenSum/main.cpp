//
//  main.cpp
//  evenSum
//
//  Created by syfo_dias on 03/03/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <vector>

// add up all the elems in container counting from back
// even elemens must be multiplied by 2, exluding the last elem (regardless odd or even)



int main(int argc, const char * argv[]) {
    // insert code here...
    std::vector<int> array {1, 2, 3, 4, 5, 6, 7, 8, 9};
    typename std::vector<int>::iterator it;
    it = array.end();
    --it;
    int count {1};
    int sum {0};
    while (it != array.begin())
    {
        sum += (count % 2 == 0) ? *it * 2: *it;
        --it; ++count;
    }
    // add the first element
    sum += (count % 2 == 0) ? *it * 2: *it;
    std::cout << sum << '\n';
    
    return 0;
}
