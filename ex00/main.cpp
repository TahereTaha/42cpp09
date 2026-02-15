#include <iostream>
#include "BitcoinExchange.hpp"
#include <stdexcept>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "please provide only one input file." << std::endl;
	}

	try
	{
		BitcoinExchange	btc(av[1]);
	}
	catch (std::exception &e)
	{
		std::cout << "error catched of: " << e.what() << std::endl;
	}
	return (0);
}

