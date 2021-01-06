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
    
    // Single typcasting?
    char ch = '5';
    int num3 = (int)ch - 48;
    std::cout << ch << " == " << num3 << '\n';
 }

void skipToInt()
{
    int count {0};
    if (std::cin.fail())
    {
        std::cout << "clearing the failed state of istream\n";
        std::cin.clear();
        for (char ch; std::cin.get(ch);)
        {
            if (isdigit(ch))
            {
                std::cin.unget();
                return;
            }
            else
            {
                std::cout << ch << '\n';
                std::cout << "Still bad input, try to enter an int\n";
                ++count;
            }
            if (count > 3)
                throw std::runtime_error ("you have screwed the input! Terminating the programme!");
        }
    }
}

int getInt()
{
    int num;
    while (true)
    {
        if (std::cin >> num)
            return num;
        else
        {
            std::cout << "Bad input, please enter an int!\n";
            skipToInt();
        }
    }
}

int getIntInRange (int min, int max)
{
    while (true)
    {
        int temp = getInt();
        if (temp >= min && temp <= max)
            return temp;
    }
        
}

void runNumTimes (const int& numRolls, const int& min, const int& max)
{
    int count {0};
    const std::string term = "stop";
    while (count < numRolls)
    {
        std::cout << "Please enter a number between " << min << " and " << max
        << " .\nOr terminate the program with word stop.\n";
        for (char ch; std::cin >> ch;)
        {
            if (ch == term[0])
            {
                std::string word;
                std::cin.unget();
                std::cin >> word;
                if (word == term)
                    return;
            }
            else
            {
                std::cin.unget();
                int temp = getIntInRange (min, max);
                std::cout << digitalRoot (temp) << '\n';
                ++count;
                break;
            }
            
        }
    }
}

int main(int argc, const char * argv[]) {
    try
    {
        //std::cout << fak (5) << '\n';
        //int value = 12397;
        int value;
        int min = 0;
        int max = 100000;
        runNumTimes(5, min, max);
        //charToInt();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
