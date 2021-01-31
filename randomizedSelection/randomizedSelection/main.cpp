//
//  main.cpp
//  randomizedSelection
//
//  Created by syfo_dias on 28/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
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

// Helper. Swappes the values.
template <typename ForwardIterator>
void swap_value (ForwardIterator left, ForwardIterator right)
{
    typename std::iterator_traits<ForwardIterator>::value_type temp = *left;
    *left = *right;
    *right = temp;
}

template <typename ForwardIterator>
ForwardIterator partition (ForwardIterator first, ForwardIterator last)
{
    typename std::iterator_traits<ForwardIterator>::difference_type step;
    step = getRandomInt (0, static_cast<int>(std::distance(first, last) - 1));
    ForwardIterator pivot = first;
    std::advance (pivot, step);
    ForwardIterator res_index = first;
    for (ForwardIterator it = first; it != last; ++it)
    {
        if (*pivot > *it)
        {
            if (it != res_index)
            {
                // this looks like it may be unstable at first.
                // but ++res_index can point to end only if all elements are smaller
                // than the pivot value and if and only if the pivot is the
                // last element
                // in this case this contition will always be false though,
                // because *pivot > *it (pivot) is false.
                swap_value (it, (res_index == pivot) ? ++res_index : res_index);
            }
            ++res_index;
        }
    }
    // if res index is on the right from the pivot
    // we need to swap the pivot value with
    if (pivot < res_index)
    {
        --res_index;
    }
    swap_value (pivot, res_index);
    return res_index;
}

/** This will return iterator to the nth smallest value. */
template <typename ForwardIterator>
ForwardIterator nSmallestValue (ForwardIterator first, ForwardIterator last, const ForwardIterator begin, int index)
{
    // recursive call of just one subrange, where the value is
    ForwardIterator pivotIndex = partition (first, last);
    if (std::distance (begin, pivotIndex) > index)
    {
        return nSmallestValue (first, pivotIndex, begin, index);
    }
    if (std::distance (begin, pivotIndex) < index)
    {
        return nSmallestValue(++pivotIndex, last, begin, index);
    }
    return pivotIndex;
    
}

template <typename C, typename T>
T nth_smallest (C container, int index)
{
    if ( (index < 0) || (index >= container.size()) )
    {
        throw std::runtime_error ("index is out of range");
    }
    auto begin = container.begin();
    return *nSmallestValue (container.begin(), container.end(), begin, index);
}

void testNthSmallest()
{
    std::vector<int> test {1, 22, 3, 5, 12, 15};
    int nth = nth_smallest<std::vector<int>, int> (test, 4);
    std::cout << "5th smallest value: " << nth << '\n';
}

// random tests

// unit tests

int main(int argc, const char * argv[]) {
    try {
        testNthSmallest();
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
