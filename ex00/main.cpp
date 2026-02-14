#include <iostream>
#include "BitcoinExchange.hpp"
#include <stdexcept>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	BitcoinExchange	btc;

	try
	{
		std::cout << "the number is: " << BitcoinExchange::stod("  42.3E2") << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "error catched of: " << e.what() << std::endl;
	}
	return (0);
}

