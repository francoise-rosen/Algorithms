//
//  main.cpp
//  SlidingWindow
//
//  Created by syfo_dias on 14/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>

template <typename C, typename T = typename C::value_type>
T maxSubArraySumNaive (const C& array, int num = 3)
{
    if (array.size() == 0)
        return static_cast<T>(0);
    int sum {std::numeric_limits<T>::lowest()};
    for (int i = 0; i < array.size() - num + 1; ++i)
    {
        int temp = array[i];
        for (int j = 1; j < num; ++j)
        {
            temp += array[i + j];
            if (temp > sum) sum = temp;
        }
    }
    
    return sum;
    
}

template <typename C, typename T = typename C::value_type>
T maxSubArraySumSlidingWindow (const C& array, int n = 3)
{
    if (array.size() < n || n < 1)
        return static_cast<T>(0);
    /** sum first n values. save the temp sum
        move pointer to i + n, subtract array[i], add array[i + n] and replace temp sum
     */
    using iterator = typename C::iterator;
    using const_iterator = typename C::const_iterator;
    const_iterator c_first = array.begin();
    const_iterator sub_last = c_first;
    std::advance (sub_last, n);
    const_iterator c_last = array.end();
    
    T maxSum = 0;
    T tempSum = 0;
    
    for (auto it = c_first; it != sub_last; ++it) // O(n)
        maxSum += *it;

    tempSum = maxSum;
    while (sub_last != c_last) // O(size)
    {
        tempSum = tempSum - *c_first + *sub_last;
        ++c_first; ++sub_last;
        if (tempSum > maxSum) maxSum = tempSum;
    }
    return maxSum;
}

void testNaive()
{
    std::vector<int> v {1, 2, 3, 4, 5 ,6, 0};
    int res = maxSubArraySumNaive(v);
    std::cout << res << '\n';
    assert (res == 15);
}

void testSliding()
{
    std::vector<int> v {1, -2, 3, 4, 5 ,6, 0};
    int res = maxSubArraySumSlidingWindow (v);
    std::cout << res << '\n';
    assert (res == 15);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    try {
        std::cout << std::numeric_limits<double>::min() << '\n' << std::numeric_limits<double>::lowest() << '\n';
        testNaive();
        testSliding();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
