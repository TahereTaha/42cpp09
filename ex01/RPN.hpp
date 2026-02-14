#pragma once

#include <string>
#include <stack>

class RPN
{
	private:
		std::stack<int>	_expresion_storage;

	public:

		RPN(void);
		RPN(const RPN & src);
		~RPN(void);
		RPN & operator = (const RPN & src);

		RPN(std::string expresion);

		int	evaluate(void) const ;
};

