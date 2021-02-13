//
//  main.cpp
//  frequencyCounter
//
//  Created by syfo_dias on 13/02/2021.
//  Copyright © 2021 syfo_dias. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "naiveCounter.h"
#include "freqCounterMap.h"
#include "freqCounterUMap.h"
#include <string>
#include <sstream>
/**
   Find if elements of second array are squared elements of first
   Frequency must match. This employs frequency counter algorithms.
   naiveCounter - nested for loop O(n*n)
   freqCounterMap - using map O nlogn
   freqCounterUMap - using unordered_map O(n) on average, O (n*n) worst case
 */

// helper to print map
void printMap (const std::map<int, int> myMap)
{
    for (auto elem : myMap)
    {
        std::cout << elem.first << " = > " << elem.second << '\n';
    }
}

void printUnorderedMap (const std::unordered_map<int, int> myMap)
{
    for (auto elem : myMap)
    {
        std::cout << elem.first << " = > " << elem.second << '\n';
    }
}

bool isAnagram (const std::string& a, const std::string& b)
{
    bool match = sfd::anagramMap<std::string, char> (a, b);
    return match;
}

void tryNaive()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    sfd::elemSquaredNaive(a, b);
    assert (sfd::elemSquaredNaive(a, b) == true);
    assert (sfd::elemSquaredNaive(a, c) == false);
    assert (sfd::elemSquaredNaive(c, b) == false);
    assert (sfd::elemSquaredNaive(a, a) == false);
    assert (sfd::elemSquaredNaive(c, d) == true);
    std::cout << "Nainve - Done\n";
}

void tryCounter1()
{
    using C = std::vector<int>;
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    sfd::elemSquared<C, int> (a, c);
    sfd::elemSquared<C, int> (a, b);
    bool ab = sfd::elemSquared<C, int>(a, b);
    bool ac = sfd::elemSquared<C, int>(a, c);
    bool cb = sfd::elemSquared<C, int>(c, b);
    bool aa = sfd::elemSquared<C, int>(a, a);
    bool cd = sfd::elemSquared<C, int>(c, d);
    assert (ab == true);
    assert (ac == false);
    assert (cb == false);
    assert (aa == false);
    assert (cd == true);
    std::cout << "Counter - Done\n";
}

void tryCounter2()
{
    std::vector<int> a {1, 2, 3};
    std::vector<int> b {4, 1, 9};
    std::vector<int> c {4, 1, 4};
    std::vector<int> d {16, 16, 1};
    std::vector<int> e {16, 16, 1, 1};
    sfd::frequencyCounterUMap (c, d);
    assert (sfd::frequencyCounterUMap(a, b) == true);
    assert (sfd::frequencyCounterUMap(a, c) == false);
    assert (sfd::frequencyCounterUMap(c, b) == false);
    assert (sfd::frequencyCounterUMap(a, a) == false);
    assert (sfd::frequencyCounterUMap(c, d) == true);
    assert (sfd::frequencyCounterUMap(c, e) == false);
    std::cout << "Counter 2 - Done\n";
}

void tryAnagram()
{
    static const std::string terminator = "stop";
//    std::cin.clear();
//    std::cin.ignore (INT_MAX, '\n');
    while (true)
    {
        std::cout << "Please enter 2 words:\n ";
        std::string word1;
        std::string word2;
        std::cin >> word1;
        if (word1 == terminator)
            return;
        std::cin >> word2;
        std::cout << word1 << " and " << word2 << " are" << ( (sfd::anagramMap<std::string, char>(word1, word2)) ? " anagrams" : " not anagrams.") << '\n';
        std::cin.clear();
        std::cin.ignore (INT_MAX, '\n');
        /** how to clean cin if there's still rubbish left? */
    }
}

void tryAnagramLine()
{
    static const std::string terminator = "stop";
    while (true)
    {
        std::cout << "Please enter 2 lines:\n ";
        std::string line1;
        std::string line2;
        std::getline (std::cin, line1);
        if (line1 == terminator)
            return;
        std:getline(std::cin, line2);
        std::cout << line1 << " and " << line2 << " are" << ( (sfd::anagramMap<std::string, char>(line1, line2)) ? " anagrams" : " not anagrams.") << '\n';
        /** how to clean cin if there's still rubbish left? */
    }
}

void testAnagram()
{
    using S = std::string;
    using c = char;
    bool match1 = sfd::anagramMap<S, c>("anna", "nnaa");
    assert (match1 == true);
    bool match2 = sfd::anagramMap<S, c>("aphex twin", "waxthe nip");
    assert (match2 == true);
    bool unmatch1 = sfd::anagramMap<S, c>("aphex twin", "ahexp winn");
    assert (unmatch1 == false);
}

void testFreqCounter()
{
    std::stringstream sentence;
    sentence << "I wish the milkman wound deliver my milk in the mording I wish the milkman would deliver my milk when I am yawning";
    using vector = std::vector<std::string>;
    vector words;
    std::string word;
    for (;sentence >> word;)
        words.push_back (word);
    std::map<std::string, int> res = sfd::frequencyCounter_M1<vector> (words);
    for (auto elem : res)
        std::cout << elem.first << " => " << elem.second << '\n';
}


int main(int argc, const char * argv[]) {
    try {
        tryNaive();
        tryCounter1();
        tryCounter2();
        //tryAnagram();
        //tryAnagramLine();
        testAnagram();
        testFreqCounter();
        
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
