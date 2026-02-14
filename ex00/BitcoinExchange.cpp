#include "BitcoinExchange.hpp"

#include <string>
#include <stdexcept>
#include <cerrno>
#include <climits>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cmath>

//	canonical orthodox form.
BitcoinExchange::BitcoinExchange(void)
{
//	std::cout << "BitcoinExchange default constructor." << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange & src)
{
//	std::cout << "BitcoinExchange copy constructor." << std::endl;
	*this = src;
}

BitcoinExchange & BitcoinExchange::operator = (const BitcoinExchange & src)
{
//	std::cout << "BitcoinExchange copy assigment." << std::endl;
	if (this != &src)
	{
		//	something.
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
//	std::cout << "BitcoinExchange default destructor." << std::endl;
}

//	constructor.


//	helper functions.

//on error will throw an exeption.
long	BitcoinExchange::stol(std::string str)
{
	const char	*c_str = str.c_str();
	char		*end_ptr;

	long	val = std::strtol(c_str, &end_ptr, 10);
	if (*end_ptr != '\0')
		throw (std::invalid_argument("not a number"));
	if (val == 0)
	{
		if(std::strpbrk(c_str, "0123456789") > end_ptr)
			throw (std::invalid_argument("not a number"));
	}
	if (val == LONG_MAX || val == LONG_MIN)
	{
		if (errno == ERANGE)
			throw (std::invalid_argument("not a number"));
	}
	return (val);
}

double	BitcoinExchange::stod(std::string str)
{
	const char	*c_str = str.c_str();
	char		*end_ptr;

	double	val = std::strtod(c_str, &end_ptr);
	if (*end_ptr != '\0')
		throw (std::invalid_argument("not a number"));
	if (val == 0.0)
	{
		if (!std::isdigit(end_ptr[-1]))
			throw (std::invalid_argument("not a number"));
	}
	if (val == HUGE_VAL)
	{
		if (errno == ERANGE)
			throw (std::invalid_argument("not a number"));
	}
	return (val);
}

//	methods.


