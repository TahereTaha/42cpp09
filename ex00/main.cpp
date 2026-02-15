#include <iostream>
#include "BitcoinExchange.hpp"
#include <stdexcept>

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		std::cout << "please provide only one input file." << std::endl;
	}

	try
	{
		BitcoinExchange	btc;
		std::cout	<< "the value is: " 
					<< btc.getValueOnDate(BitcoinExchange::stodate("2022-03-28")) 
					<< std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "error catched of: " << e.what() << std::endl;
	}
	return (0);
}

