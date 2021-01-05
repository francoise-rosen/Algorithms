//
//  main.cpp
//  digitalRoot
//
//  Created by syfo_dias on 05/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>

int digitalRoot (int value)
{
    std::string strValue = std::to_string (value);
    if (strValue.length() < 2)
        return value;
    int sum {0};
    for (auto l : strValue)
    {
            std::stringstream sst;
            sst << l;
            int t;
            sst >> t;
            sum += t;
    }
    return digitalRoot (sum);
}

int fak (int num)
{
    if (num == 1)
        return num;
    else
        return num * fak (num - 1);
}

void charToInt ()
{
    // using stringstream
    int val = 123;
    std::string strVal = std::to_string (val);
    int sum {0};
    const char* word = "12455";
    for (auto p : strVal)
    {
        std::stringstream sst;
        sst << p;
        int t;
        sst >> t;
        sum += t;
    }
    int num = std::atoi (word);
    std::cout << num << '\n';
    std::cout << sum << '\n';
}

int main(int argc, const char * argv[]) {
    try
    {
        //std::cout << fak (5) << '\n';
        int value = 12397;
        std::cout << digitalRoot(value) << '\n';
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
