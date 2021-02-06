//
//  main.cpp
//  stringOperations
//
//  Created by syfo_dias on 13/01/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <string>

/** Reverse. */
namespace sfd
{
    template <typename RandomInterator>
    void reverse (RandomInterator first, RandomInterator last)
    {
        RandomInterator back = last;
        --back;
        while (first < back)
        {
            std::swap (*first, *back);
            ++first;
            --back;
        }
    }
    
    template <typename RandomIterator>
    RandomIterator reverse (RandomIterator first, RandomIterator last, RandomIterator first2)
    {
        RandomIterator back = last;
        --back;
        RandomIterator result = first2;
        while (back != first)
        {
            *result = *back;
            --back;
            ++result;
        }
        return result;
    }
    
    template <typename ForwardIterator>
    bool match (ForwardIterator first1, ForwardIterator last1, ForwardIterator first2, ForwardIterator last2)
    {
        while ( (first2 != last2))
        {
            if (*first1 != *first2)
                return false;
            ++first1; ++first2;
        }
        return true;
    }
    
    template <typename ForwardItearator>
    ForwardItearator find_sub (ForwardItearator first1, ForwardItearator last1, ForwardItearator first2, ForwardItearator last2)
    {
        typename std::iterator_traits<ForwardItearator>::difference_type size1, size2;
        size1 = std::distance (first1, last1);
        size2 = std::distance (first2, last2);
        if (size2 > size1)
            return last1;
        
        while ( (first1 != last1))
        {
            if (*first1 == *first2)
            {
                bool m = sfd::match (first1, last1, first2, last2);
                if (m)
                    return first1;
            }
            ++first1;
        }
        return last1;
    }
}

/** Find substring. */
void findSubstring()
{
    std::string fsol = "The Future Sound Of London";
    std::string london = "London";
    std::string sound = "Sound";
    std::string afx = "AFX";
    auto p = sfd::find_sub(fsol.begin(), fsol.end(), london.begin(), london.end());
    if (p == fsol.end())
        std::cout << london << " not found in  " << fsol << '\n';
    auto p2 = sfd::find_sub(fsol.begin(), fsol.end(), sound.begin(), sound.end());
    std::cout << ((p2 == fsol.end()) ? sound + " is not found " : sound + " is found!\n");
}

// C STRING
void printCString (const char* str)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        std::cout << str[i];
    }
}

void reverseCString ()
{
    char str[] = "0 Jynwheithek 0 ";
    int size {0};
    for (auto i = 0; str[i] != 0; ++i )
        ++size;
    char copy[size];
    sfd::reverse (str + 0, str + size, copy);
    std::cout << str << '\n';
}

void reverseString ()
{
    std::cout << "Enter a string: ";
    for (std::string str; std::cin >> str && str != "exit";)
    {
        sfd::reverse (str.begin(), str.end());
        std::cout << str;
        std::cout << "\nPlease enter a string\nOr terminate the loop with \"exit\" \n";
    }
}

int main(int argc, const char * argv[]) {
    try
    {
        reverseCString ();
        reverseString();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
