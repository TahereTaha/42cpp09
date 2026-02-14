#include "RPN.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

//	canonical orthodox form.
RPN::RPN(void)
{
//	std::cout << "RPN default constructor." << std::endl;
}

RPN::RPN(const RPN & src)
{
//	std::cout << "RPN copy constructor." << std::endl;
	*this = src;
}

RPN & RPN::operator = (const RPN & src)
{
//	std::cout << "RPN copy assigment." << std::endl;
	if (this != &src)
	{
		this->_expresion_storage = src._expresion_storage;
	}
	return (*this);
}

RPN::~RPN(void)
{
//	std::cout << "RPN default destructor." << std::endl;
}

//	constructors.
RPN::RPN(std::string expresion)
{
//	std::cout << "RPN constructor." << std::endl;
	std::stack<int>	tmp;	// temporal stack to store the values in reverse order.
	size_t	i = 0;
	while (i < expresion.size())
	{
		if (
			expresion[i] != ' ' && 
			std::string("1234567890+-*/").find(expresion[i]) == std::string::npos
		)
			throw (std::logic_error("Error"));
		if (std::string("1234567890+-*/").find(expresion[i]) != std::string::npos)
			tmp.push(expresion[i]);
		i++;
	}
	while (tmp.size() != 0)
	{
		this->_expresion_storage.push(tmp.top());
		tmp.pop();
	}
}

int	RPN::evaluate(void) const 
{
	std::stack<int> expresion = this->_expresion_storage;
	std::stack<int> eval;

	while (expresion.size())
	{
		int	item = expresion.top();
		expresion.pop();
		if (std::isdigit(item))
			eval.push(item - '0');
		else
		{
			if (eval.size() < 2)
				throw (std::logic_error("Error"));
			int	rhs = eval.top();
			eval.pop();
			int	lhs = eval.top();
			eval.pop();
			if (item == '+')
				eval.push(lhs + rhs);
			else if (item == '-')
				eval.push(lhs - rhs);
			else if (item == '*')
				eval.push(lhs * rhs);
			else if (item == '/')
			{
				if (rhs == 0)
					throw (std::logic_error("Error"));
				eval.push(lhs / rhs);
			}
		}
	}
	if (eval.size() != 1)
		throw (std::logic_error("Error"));
	return (eval.top());
}
