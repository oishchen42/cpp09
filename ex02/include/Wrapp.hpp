#pragma once

#include "include.h"

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