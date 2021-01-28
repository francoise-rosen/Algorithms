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
int partition (ForwardIterator first, ForwardIterator last, ForwardIterator pivot)
{
    
}

template <typename ForwardIterator, typename T>
int findIndex (ForwardIterator first, ForwardIterator last, T value)
{
    // recursive call of just one subrange, where the value is
}

template <typename C, typename T>
int nOrderStatistic (C container, T value)
{
    return findIndex (container.begin(), container.end(), value);
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
