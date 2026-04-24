#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <regex>
#include <stdexcept>
#include <string>
#include <charconv>
#include <sys/time.h>

class Wrapp
{
public:
    static void sortVec(const std::string& input);
    static void sortDque(const std::string& input);
private:
    Wrapp() = default;
    ~Wrapp() = default;

    Wrapp(const Wrapp& other) = delete;
    Wrapp& operator=(const Wrapp& other) = delete;
};