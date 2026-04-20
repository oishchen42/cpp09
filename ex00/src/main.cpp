#include "BitExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file.\n";
        return 1;
    }
    std::string file_name = av[1];
    try
    {
        BitExchange a;
        a.inputFile(file_name);
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}