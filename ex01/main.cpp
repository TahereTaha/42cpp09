#include <iostream>
#include "RPN.hpp"
#include <stdexcept>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return (42);
	}

	try
	{
		RPN	expresion(av[1]);
		try
		{
			std::cout << expresion.evaluate() << std::endl;;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}

