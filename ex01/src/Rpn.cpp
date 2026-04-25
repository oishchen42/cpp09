#include "Rpn.hpp"

void Rpn::calculate(const std::string& input)
{
    std::list<int> _stack;
    std::istringstream pure_input(input);
    char sign;
    while(pure_input >> sign)
    {
        if (std::isdigit(sign))
            _stack.push_back(sign - '0');
        else if (_stack.size() >= 2 && (sign == '-' || sign == '/' || sign == '+' || sign == '*'))
        {
            int right_op = _stack.back();
            _stack.pop_back();
            int left_op = _stack.back();
            _stack.pop_back();
            switch (sign)
            {
                case '+':
                    _stack.push_back(left_op + right_op);
                    break;
                case '-':
                    _stack.push_back(left_op - right_op);
                    break;
                case '*':
                    _stack.push_back(left_op * right_op);
                    break;
                case '/':
                    if (right_op == 0)
                    {
                        throw std::runtime_error("Error: zero division is not allowed.");
                        return;
                    }
                    _stack.push_back(left_op / right_op);
                    break ;
            }
        }
    }
    if (_stack.size() != 1)
    {
        throw std::runtime_error("Error: incomplete operation.");
    }
    std::cout << _stack.back() << std::endl;
}