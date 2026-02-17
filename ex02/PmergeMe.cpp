#include "PmergeMe.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

#include <cctype>
#include <cstdlib>
#include <climits>
#include <cerrno>
#include <cstring>

//	canonical orthodox form.
PmergeMe::PmergeMe(void)
{
	this->_comparisonCount = 0;
}

PmergeMe::PmergeMe(const PmergeMe & src)
{
	*this = src;
}

PmergeMe & PmergeMe::operator = (const PmergeMe & src)
{
	if (this != &src)
	{
		this->_comparisonCount = src._comparisonCount;
		this->_unsortedContainer = src._unsortedContainer;
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
	this->_comparisonCount = 0;
	size_t	i = 1;
	while (i < (size_t)ac)
	{
		this->_unsortedContainer.push_back(PmergeMe::stoul(av[i]));
		i++;
	}
	this->_sortedContainer = this->_unsortedContainer;
	std::sort(this->_sortedContainer.begin(), this->_sortedContainer.end());

	std::cout << "Before:\t" << this->_unsortedContainer << std::endl;
	std::cout << "After:\t" << this->_sortedContainer << std::endl;

	this->_vectorContainer = \
		std::vector<unsigned long>(this->_unsortedContainer.begin(), this->_unsortedContainer.end());
	this->_listContainer = \
		std::list<unsigned long>(this->_unsortedContainer.begin(), this->_unsortedContainer.end());

//	std::cout << "my vector container:\t" << this->_vectorContainer << std::endl;
//	std::cout << "my list container:\t" << this->_listContainer << std::endl;
}

//	some debug and visualasing functions.

void	PmergeMe::printVectorContainer(void) const 
{
	std::cout << "The elements in the vector container are:" << std::endl;
	std::cout << "\t" << this->_vectorContainer << std::endl;
}

void	PmergeMe::printVectorContainerPairs(size_t depth) const 
{
	std::cout << "The elements in the vector container grouped in pairs at depth ";
	std::cout << depth << " are:" << std::endl;
	size_t	i = 0;
	std::cout << "\t";
	while (i < this->_vectorContainer.size() / (PmergeMe::pow(2, depth + 1)))
	{
		std::cout 
		<< "[" 
			<< this->_vectorContainer[i * PmergeMe::pow(2, depth + 1) + PmergeMe::pow(2, depth) - 1] 
			<< ", " 
			<< this->_vectorContainer[(i + 1) * PmergeMe::pow(2, depth + 1) - 1] 
		<< "]";
		i++;
	}
	if (i < this->_vectorContainer.size() / (PmergeMe::pow(2, depth + 1)))
		std::cout << " " << this->_vectorContainer[i];
	std::cout << std::endl;
}

void	PmergeMe::printVectorContainerMainChain(size_t depth) const 
{
	std::cout << "The element in the main chain at depth " << depth << " are:" << std::endl;
	size_t	i = 0;
	std::cout << "\t[";
	while (i < this->_vectorContainer.size() / 2)
	{
		std::cout << this->_vectorContainer[i * 2 + 1];
		i++;
		if (i < this->_vectorContainer.size() / 2)
			std::cout << ", ";
	}
	std::cout << "]";
	std::cout << std::endl;
}

void	PmergeMe::printVectorContainerPendChain(size_t depth) const 
{
	std::cout << "The elements in the pend chain at depth " << depth << " are:" << std::endl;
	size_t	i = 0;
	std::cout << "\t[";
	while (i < this->_vectorContainer.size() / (2 * (depth + 1)))
	{
		std::cout << this->_vectorContainer[i * 2];
		i++;
		if (i < this->_vectorContainer.size() / 2)
			std::cout << ", ";
	}
	std::cout << "]";
	std::cout << std::endl;
}

void	PmergeMe::printVectorContainerUnpairdElement(size_t depth) const 
{
	std::cout << "The unpaird element at depth " << depth << " is:" << std::endl;
	if (this->_vectorContainer.size() / (depth + 1) % 2)
	{
		std::cout << "\t";
		std::cout << this->_vectorContainer[this->_vectorContainer.size() / (depth + 1) - 1];
	   	std::cout << std::endl;
		return ;
	}
	std::cout << "\tthere is no unpaird element here." << std::endl;
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
	if (str.find('-') != std::string::npos)
		throw (std::invalid_argument("Error"));
	return (val);
}

//	succession is: preciding + 2 * second_preciding
unsigned long	PmergeMe::jacob_seq(unsigned long n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);

	unsigned long	second_preciding = 0;
	unsigned long	preciding = 1;
	unsigned long	current = preciding + 2 * second_preciding;
	n -= 2;
	while (n != 0)
	{
		second_preciding = preciding;
		preciding = current;
		current = preciding + 2 * second_preciding;
		n--;
	}
	return (current);
}

size_t	PmergeMe::pow(size_t base, size_t exponent)
{
	if (exponent == 0)
		return (1);
	size_t	result = base;
	size_t	i = 0;
	while (i < exponent - 1)
	{
		result *= base;
		i++;
	}
	return (result);
}

//	some methods for the implementation of the algorithm.

void	PmergeMe::vectorSortPairs(void)
{
	size_t	i = 0;
	while (i < this->_vectorContainer.size() / 2)
	{
		//	number comparison
		this->_comparisonCount++;
		if (this->_vectorContainer[i * 2] > this->_vectorContainer[i * 2 + 1])
		{
			unsigned long	temp = this->_vectorContainer[i * 2];
			this->_vectorContainer[i * 2] = this->_vectorContainer[i * 2 + 1];
			this->_vectorContainer[i * 2 + 1] = temp;
		}
		i++;
	}
}


//	internal methods.

void	PmergeMe::sortVectorContainer(void)
{
	std::cout << "\ndoing the shorting of the vector.\n" << std::endl;
	this->vectorSortPairs();
}

//	methods.


void	PmergeMe::run(void)
{
	std::cout << "\n//\truning the thing." << std::endl;

	this->sortVectorContainer();

	std::cout << "the correct one is:\t\t" << this->_sortedContainer << std::endl;
	std::cout << "the result of the vector is:\t" << this->_vectorContainer << std::endl;
}







