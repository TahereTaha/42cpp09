#include "BitcoinExchange.hpp"

#include <string>
#include <stdexcept>
#include <iostream>
#include <fstream>

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
	this->initDB();
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
		this->_db = src._db;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
//	std::cout << "BitcoinExchange default destructor." << std::endl;
}

//	wraper of time_t.

Time_t::Time_t(void) {}

Time_t::Time_t(const Time_t & src) { *this = src; }

Time_t & Time_t::operator = (const Time_t & src)
{
	if (this != &src)
	{
		this->_val = src._val;
	}
	return (*this);
}

Time_t::~Time_t(void) {}

Time_t::Time_t(time_t val)
{
	this->_val = val;
}

//	internal methods.

void	BitcoinExchange::initDB(void)
{
	std::ifstream	db_file("data.csv");
	std::string		line;
	std::getline(db_file, line);
	if (line != "date,exchange_rate")
		throw (std::invalid_argument("malformed database"));
	size_t	i = 2;
	while (std::getline(db_file, line))
	{
		try
		{
			if (line.find(',') == std::string::npos)
				throw (std::invalid_argument("malformed record"));
			std::string	date_str = line.substr(0, line.find(','));
			line = line.substr(line.find(',') + 1);
			if (line.find(',') != std::string::npos)
				throw (std::invalid_argument("malformed record"));
			std::string	amount_str = line;
			time_t	date = BitcoinExchange::stodate(date_str);
			double	amount = BitcoinExchange::stod(amount_str);
			if (amount < 0)
				throw (std::invalid_argument("can't proses negative values."));
			this->_db[date] = amount;
		}
		catch (std::exception &e)
		{
			std::cout << "Record on line " << i << " disrigarded because: " << e.what() << std::endl;
		}
		i++;
	}
}

//	return the the exact one or the imidiate inferior to this one.
double	BitcoinExchange::getValueOnDate(time_t date)
{
	if (this->_db.begin()->first > date)
		throw (std::invalid_argument("no record for this time."));
	std::map<time_t, double>::iterator best_match = this->_db.begin();
	std::map<time_t, double>::iterator iter = this->_db.begin();
	std::map<time_t, double>::iterator end = this->_db.end();
	while (iter != end)
	{
		if (iter->first <= date)
			best_match = iter;
		iter++;
	}
	std::cout << "best match is: " << Time_t(best_match->first) << std::endl;
	return (best_match->second);
}

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
time_t	BitcoinExchange::stodate(std::string str)
{
	time_t	val;

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
	return (val);
}

//	stream insertion operator overloading for time_t.
std::ostream & operator << (std::ostream & out_s, const Time_t & obj)
{
	struct tm	*time_info;

	time_info = std::localtime(&(obj._val));

	std::cout	<< time_info->tm_year + 1900 << "-" 
				<< time_info->tm_mon + 1 << "-" 
				<< time_info->tm_mday;
	return (out_s);
}

//	methods.


