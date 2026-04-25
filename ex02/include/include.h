#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <regex>
#include <stdexcept>
#include <string>
#include <charconv>
#include <sys/time.h>


// non-generic helpers
void printVec(const std::vector<int>& vec);
void dqPrint(const std::deque<int>& dqs);
void checkInput(const std::string& input);

// helpers for debugin + mergeSort functions for fun
template <typename I>
bool isSorted(I first, I last)
{
    if (first == last)
        return true;
    I next = first;
    next++;
    while (next != last)
    {
        if (*first > *next)
            return false;
        first++;
        next++;
    }
    return true;
}

template <typename T>
void pairsPrint(const T& box)
{
    for (const auto& item : box)
    {
        std::cout << "[" << item.first << "; " << item.second << "] ";
    }
    std::cout << std::endl;
}

//merge-sort functions:
template <typename T>
void mergeBoth(T& larry, T& rarry, T& vec)
{
    size_t l = 0;
    size_t r = 0;
    size_t v = 0;
    while (l < larry.size() && r < rarry.size())
    {
        if (larry.at(l) <= rarry.at(r)) 
        {
            vec.at(v) = larry.at(l);
            l++;
        }
        else 
        {
            vec.at(v) = rarry.at(r);
            r++;
        }
        v++;
    }
    while (l < larry.size())
    {
        vec.at(v) = larry.at(l);
        v++;
        l++;
    }
    while (r < rarry.size())
    {
        vec.at(v) = rarry.at(r);
        v++;
        r++;
    }
}

template <typename T>
static void mergeSort(T& vec)
{
    if (vec.size() <= 1)
        return ;
    size_t left_array = vec.size() / 2;
    T larry(vec.begin(), vec.begin() + left_array);
    T rarry(vec.begin() + left_array, vec.end());
    mergeSort(larry);
    mergeSort(rarry);
    mergeBoth(larry, rarry, vec);
}