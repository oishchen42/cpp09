#include "BitExchange.hpp"

int main()
{
    try
    {
        BitExchange a;
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}