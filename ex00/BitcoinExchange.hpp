#pragma once

#include <string>
#include <ctime>
#include <map>

class BitcoinExchange
{
	private:

	public:		//	to be remobed after.
		//	some helper functions.
		static long		stol(std::string str);
		static double	stod(std::string str);
//		static time_t	stodate(std::string str);
	public:

		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange & src);
		~BitcoinExchange(void);
		BitcoinExchange & operator = (const BitcoinExchange & src);
};

//	things to do.
//	- [ ] parse dates.
//	- [ ] prase floats.
//	- [ ] parse and store the database.
//	- [ ] make some acces methods.
//	- [ ] go throug the data display it.

