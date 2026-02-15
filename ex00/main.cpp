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
		Time_t	my_time(BitcoinExchange::stodate("2021-9-23"));
		std::cout << "the number is: " << my_time  << std::endl;
		std::cout << "the number is: " << Time_t(BitcoinExchange::stodate("2021-9-23"))  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "error catched of: " << e.what() << std::endl;
	}
	return (0);
}

