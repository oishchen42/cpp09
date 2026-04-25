#pragma once

#include <list>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Rpn{
public:
    static void calculate(const std::string& expression);
private:
    Rpn() = default;
    Rpn(const Rpn& other) = delete;
    Rpn& operator=(const Rpn& other) = delete;
    ~Rpn() = default;
};