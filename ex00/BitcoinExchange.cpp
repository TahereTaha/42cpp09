#include "BitcoinExchange.hpp"

#include <string>
#include <stdexcept>
#include <iostream>

#include <cerrno>
#include <climits>
#include <cctype>
#include <ctime>
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

//on error will throw an exeption.
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

//on error will throw an exeption.
time_t	*BitcoinExchange::stodate(std::string str)
{
	static time_t	val;

	if (str.find('-') == std::string::npos)
		throw (std::invalid_argument("not a date"));
	std::string year_str = str.substr(0, str.find('-'));
	if (year_str.size() == 0)
		throw (std::invalid_argument("not a date"));
	str = str.substr(str.find('-') + 1);
	
	if (str.find('-') == std::string::npos)
		throw (std::invalid_argument("not a date"));
	std::string month_str = str.substr(0, str.find('-'));
	if (month_str.size() == 0)
		throw (std::invalid_argument("not a date"));
	str = str.substr(str.find('-') + 1);
	
	if (str.find('-') != std::string::npos)
		throw (std::invalid_argument("not a date"));
	std::string day_str = str;
	if (day_str.size() == 0)
		throw (std::invalid_argument("not a date"));

	std::time(&val);
	struct tm	*time_info;
	time_info = std::localtime(&val);
	time_info->tm_sec = 0;
	time_info->tm_min = 0;
	time_info->tm_hour = 0;
	try
	{
		time_info->tm_mday = BitcoinExchange::stol(day_str);
		time_info->tm_mon = BitcoinExchange::stol(month_str) - 1;
		time_info->tm_year = BitcoinExchange::stol(year_str) - 1900;
	}
	catch (std::exception &e)
	{
		(void)e;
		throw (std::invalid_argument("not a date"));
	}
	val = std::mktime(time_info);
	if (val == -1)
		throw (std::invalid_argument("not a date"));
	return (&val);
}



//	methods.


