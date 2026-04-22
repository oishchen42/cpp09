#include "Rpn.hpp"

void Rpn::calculate(const std::string& input)
{
    std::stack<int> _stack;
    std::istringstream pure_input(input);
    char sign;
    while(pure_input >> sign)
    {
        if (std::isdigit(sign))
            _stack.push(sign - '0');
        else if (_stack.size() >= 2 && (sign == '-' || sign == '/' || sign == '+' || sign == '*'))
        {
            int right_op = _stack.top();
            _stack.pop();
            int left_op = _stack.top();
            _stack.pop();
            switch (sign)
            {
                case '+':
                    _stack.push(left_op + right_op);
                    break;
                case '-':
                    _stack.push(left_op - right_op);
                    break;
                case '*':
                    _stack.push(left_op * right_op);
                    break;
                case '/':
                    if (right_op == 0)
                    {
                        throw std::runtime_error("Error: zero division is not allowed.");
                        return;
                    }
                    _stack.push(left_op / right_op);
                    break ;
            }
        }
    }
    if (_stack.size() != 1)
    {
        throw std::runtime_error("Error: incomplete operation.");
    }
    std::cout << _stack.top() << std::endl;
}