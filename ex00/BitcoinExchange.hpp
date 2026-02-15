#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <map>

class BitcoinExchange
{
	private:
//		std::map<>	_db;

	public:		//	to be remobed after.

		//	some helper functions.
		static long		stol(std::string str);
		static double	stod(std::string str);
		static time_t	stodate(std::string str);

		//	some internal methods.
//		void	initDB(void);
	public:

		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange & src);
		~BitcoinExchange(void);
		BitcoinExchange & operator = (const BitcoinExchange & src);
};

//	thin wraper of the type of time_t
class Time_t
{
	public:
		time_t	_val;
		
		Time_t(void);
		Time_t(const Time_t & src);
		~Time_t(void);
		Time_t & operator = (const Time_t & src);
		
		Time_t(time_t	val);
};

std::ostream & operator << (std::ostream & out_s, const Time_t & obj);

//	things to do.
//	- [x] parse longs.
//	- [x] prase floats.
//	- [x] parse dates.
//	- [ ] print dates.
//	- [ ] parse and store the database.
//	- [ ] make some acces methods.
//	- [ ] go throug the data display it.

