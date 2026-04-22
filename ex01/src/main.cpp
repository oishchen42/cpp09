#include "Rpn.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: provide the expression to calculate\n";
        return 1;
    }
    std::string input = av[1];
    try
    {
        Rpn::calculate(input);
    }
    catch(std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}