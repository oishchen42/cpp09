#include "include.h"

void printVec(const std::vector<int>& vec)
{
    for(const auto& v : vec)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

void dqPrint(const std::deque<int>& dqs)
{
    for(const auto& dq : dqs)
    {
        std::cout << dq << " ";
    }
    std::cout << std::endl;
}

void checkInput(const std::string& input)
{
    std::regex pattern("^[0-9 ]*$");
    if (!std::regex_match(input, pattern))
        throw std::logic_error("Error: the input contains unallowed values");
}
