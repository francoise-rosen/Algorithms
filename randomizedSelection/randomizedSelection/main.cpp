//
//  main.cpp
//  randomizedSelection
//
//  Created by syfo_dias on 28/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <random>

namespace random_generator
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen {static_cast<std::mt19937::result_type>(seed)};
}

int getRandomInt (const int& min, const int& max)
{
    std::uniform_int_distribution<> value {min, max};
    return value (random_generator::gen);
}

template <typename ForwardIterator>
ForwardIterator partition (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type step;
}

template <typename ForwardIterator>
ForwardIterator nSmallestValue (ForwardIterator first, ForwardIterator last, int index)
{
    // recursive call of just one subrange, where the value is
    ForwardIterator pivotIndex = partition (first, last);
    if (std::distance (first, pivotIndex) > index)
    {
        return nSmallestValue (first, pivotIndex, index);
    }
    if (std::distance (first, pivotIndex) < index)
    {
        return nSmallestValue(++pivotIndex, last, index);
    }
    return pivotIndex;
    
}

template <typename C, typename T>
T nth_smallest (C container, int index)
{
    auto p = nSmallestValue (container.begin(), container.end(), index);
    T val = *p;
    return val;
}

int main(int argc, const char * argv[]) {
    try {
        for (int i = 0; i < 10; ++i)
        {
            std::cout << getRandomInt(-5, 5) << '\n';
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
