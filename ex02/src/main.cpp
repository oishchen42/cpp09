#include <Wrapp.hpp>

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: the usage is ./<binary> <sequence> (the nb of inputs == 2)\n";
        return 1;
    }
    std::string input = av[1];
    try
    {
        Wrapp::sortVec(input);
        Wrapp::sortDque(input);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

// for input generation: $(shuf -i 1-100000 -n 3000 | tr '\n' ' ')