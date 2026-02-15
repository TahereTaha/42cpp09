#include "PmergeMe.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

#include <cctype>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cstring>

//	canonical orthodox form.
PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe & src)
{
	*this = src;
}

PmergeMe & PmergeMe::operator = (const PmergeMe & src)
{
	if (this != &src)
	{
		this->_intactContainer = src._intactContainer;
		this->_sortedContainer = src._sortedContainer;
		this->_vectorContainer = src._vectorContainer;
		this->_listContainer = src._listContainer;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
}

//	some helper functions.

unsigned long	PmergeMe::stoul(std::string str)
{
	const char	*c_str = str.c_str();
	char		*end_ptr;

	unsigned long	val = std::strtoul(c_str, &end_ptr, 10);
	if (*end_ptr != '\0')
		throw (std::invalid_argument("Error"));
	if (val == 0)
	{
		if(std::strpbrk(c_str, "0123456789") > end_ptr)
			throw (std::invalid_argument("Error"));
	}
	if (val == ULONG_MAX)
	{
		if (errno == ERANGE)
			throw (std::invalid_argument("Error"));
	}
	return (val);
}

//	constructors.

PmergeMe::PmergeMe(int ac, char **av)
{
	std::cout << "seting up the merge insertion sort." << std::endl;
	
	(void) ac;
	(void) av;

	size_t	i = 1;
	while (i < (size_t)ac)
	{
		(void) PmergeMe::stoul(av[i]);
		i++;
	}
}

//	internal methods.

//	methods.

void	PmergeMe::run(void)
{
	std::cout << "runing the thing." << std::endl;
}

