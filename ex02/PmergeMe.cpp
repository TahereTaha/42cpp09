#include "PmergeMe.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

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

//	constructors.

PmergeMe::PmergeMe(int ac, char **av)
{
	std::cout << "seting up the merge insertion sort." << std::endl;
	(void) ac;
	(void) av;

}

//	methods.

void	PmergeMe::run(void)
{
	std::cout << "runing the thing." << std::endl;
}

