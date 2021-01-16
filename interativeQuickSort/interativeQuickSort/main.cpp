//
//  main.cpp
//  interativeQuickSort
//
//  Created by syfo_dias on 12/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <vector>
#include "quickSort.h"

void containersAddress()
{
    std::vector<int> vi {4, 12, 55, 4322};
    vi.push_back (44);
    for (int i = 0; i < vi.size(); ++i)
    {
        std::cout << &vi[i] << '\n';
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
//    int testArray[] {-122, -234, 0, 2, 3, -2, 187};
//    int size = sizeof (testArray) / sizeof (testArray[0]);
//    quickSort(testArray, testArray + size);
//    //bubbleSort(testArray, testArray + size);
//    for (int i = 0; i < size; ++i)
//    {
//        std::cout << testArray[i] << " ";
//    }
//    std::cout << '\n';
    containersAddress();
    return 0;
}
