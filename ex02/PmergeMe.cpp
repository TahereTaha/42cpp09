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
		std::vector<size_t>(this->_unsortedContainer.begin(), this->_unsortedContainer.end());
	this->_listContainer = \
		std::list<size_t>(this->_unsortedContainer.begin(), this->_unsortedContainer.end());

//	std::cout << "my vector container:\t" << this->_vectorContainer << std::endl;
//	std::cout << "my list container:\t" << this->_listContainer << std::endl;
}

//	some debug and visualasing functions.

void	PmergeMe::printVectorContainer(void) const 
{
	std::cout << "The elements in the vector container are:" << std::endl;
	std::cout << "\t" << this->_vectorContainer << std::endl;
}

void	PmergeMe::printVectorContainerMainChainElementLean(size_t depth, size_t index) const
{
	std::cout << this->getVectorContainerMainChainElement(depth, index);
}

void	PmergeMe::printVectorContainerMainChainElement(size_t depth, size_t index) const 
{
	std::cout << "The element in the vector container at ";
	std::cout << "depth " << depth << " ";
	std::cout << "index " << index << " ";
	std::cout << "is:" << std::endl;

	std::cout << "\t" << this->getVectorContainerMainChainElement(depth, index) << std::endl;
}

void	PmergeMe::printVectorContainerMainChain(size_t depth) const 
{
	std::cout << "The element in the main chain at ";
	std::cout << "depth " << depth << " ";
	std::cout << "are:" << std::endl;
	size_t	i = 0;
	std::cout << "\t[";
	while (i < this->getVectorContainerChainSize(depth))
	{
		this->printVectorContainerMainChainElementLean(depth, i);
		i++;
		if (i < this->getVectorContainerChainSize(depth))
			std::cout << ", ";
	}
	std::cout << "]";
	std::cout << std::endl;
}

void	PmergeMe::printVectorContainerPendChain(size_t depth) const 
{
	std::cout << "The elements in the pend chain at ";
	std::cout << "depth " << depth << " ";
	std::cout << "are:" << std::endl;
	size_t	i = 0;
	if (depth == 0)
	{
		std::cout << "\tthere is no pend chain in this level." << std::endl;
		return ;
	}
	std::cout << "\t[";
	while (i < this->getVectorContainerChainSize(depth))
	{
		this->printVectorContainerMainChainElementLean(depth - 1, i * 2);
		i++;
		if (i < this->getVectorContainerChainSize(depth))
			std::cout << ", ";
	}
	std::cout << "]";
	std::cout << std::endl;
}

void	PmergeMe::printVectorContainerUnpairdElement(size_t depth) const 
{
	std::cout << "The unpaird element at ";
	std::cout << "depth " << depth << " ";
	std::cout << "is:" << std::endl;
	std::cout << "\t";
	if (depth == 0)
	{
		std::cout << "there is no unpaird element at depth 0." << std::endl;
		return ;
	}
	if (this->getVectorContainerChainSize(depth - 1) % 2 == 0)
	{
		std::cout << "there is no unpaird element here." << std::endl;
		return ;
	}
	std::cout << "[";
	size_t	index = this->getVectorContainerChainSize(depth - 1) - 1;
	this->printVectorContainerMainChainElementLean(depth - 1, index);
	std::cout << "]";
	std::cout << std::endl;
}

void	PmergeMe::printVectorContainerMainChainPairs(size_t depth) const 
{
	std::cout << "The elements in the vector container grouped in pairs at depth ";
	std::cout << depth << " are:" << std::endl;
	size_t	i = 0;
	std::cout << "\t";
	while (i < this->getVectorContainerChainSize(depth) / 2)
	{
		std::cout 
		<< "["
			<< this->getVectorContainerMainChainElement(depth, i * 2)
			<< ", "
			<< this->getVectorContainerMainChainElement(depth, i * 2 + 1)
		<< "]";
		i++;
	}
	if (i * 2 < this->getVectorContainerChainSize(depth))
	{
		std::cout << " ";
		this->printVectorContainerMainChainElementLean(depth, i * 2);
	}
	std::cout << std::endl;
}

//	some helper functions.

size_t	PmergeMe::stoul(std::string str)
{
	const char	*c_str = str.c_str();
	char		*end_ptr;

	size_t	val = std::strtoul(c_str, &end_ptr, 10);
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
size_t	PmergeMe::jacob_seq(size_t n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);

	size_t	second_preciding = 0;
	size_t	preciding = 1;
	size_t	current = preciding + 2 * second_preciding;
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

size_t	PmergeMe::getVectorContainerAbsoluteIndex(size_t depth, size_t relative_index) const 
{
	return ((relative_index + 1) * PmergeMe::pow(2, depth) - 1);
}

size_t	PmergeMe::getVectorContainerChainSize(size_t depth) const
{
	return (this->_vectorContainer.size() / (PmergeMe::pow(2, depth)));
}

size_t	&PmergeMe::getVectorContainerMainChainElement(size_t depth, size_t index)
{
	size_t	i = this->getVectorContainerAbsoluteIndex(depth, index);
	return (this->_vectorContainer[i]);
}

const size_t	&PmergeMe::getVectorContainerMainChainElement(size_t depth, size_t index) const 
{
	size_t	i = this->getVectorContainerAbsoluteIndex(depth, index);
	return (this->_vectorContainer[i]);
}

void	PmergeMe::swapVectorContainerMainChainElementsSimple(size_t depth, \
		size_t index1, \
		size_t index2)
{
	size_t	tmp1 = this->getVectorContainerMainChainElement(depth, index1);
	size_t	tmp2 = this->getVectorContainerMainChainElement(depth, index2);
	this->getVectorContainerMainChainElement(depth, index1) = tmp2;
	this->getVectorContainerMainChainElement(depth, index2) = tmp1;
}

void	PmergeMe::swapVectorContainerMainChainElements(size_t depth, size_t index1, size_t index2)
{
	swapVectorContainerMainChainElementsSimple(depth, index1, index2);
	if (depth > 0)
	{
		size_t	lesser_index1 = this->getVectorContainerAbsoluteIndex(1, index1) - 1;
		size_t	lesser_index2 = this->getVectorContainerAbsoluteIndex(1, index2) - 1;
		swapVectorContainerMainChainElements(depth - 1, lesser_index1, lesser_index2);
	}
	if (depth > 1)
	{
		size_t	lesser_index1 = this->getVectorContainerAbsoluteIndex(2, index1) - 1;
		size_t	lesser_index2 = this->getVectorContainerAbsoluteIndex(2, index2) - 1;
		swapVectorContainerMainChainElements(depth - 2, lesser_index1, lesser_index2);
	}
}

void	PmergeMe::sortVectorContainerMainChainPairs(size_t depth)
{
	size_t	i = 0;
	while (i < this->getVectorContainerChainSize(depth) / 2)
	{
		//	number comparison
		this->_comparisonCount++;
		if (this->getVectorContainerMainChainElement(depth, i * 2) \
			> this->getVectorContainerMainChainElement(depth, i * 2 + 1))
		{
			this->swapVectorContainerMainChainElements(depth, i * 2, i * 2 + 1);
		}
		i++;
	}
}

void	PmergeMe::insertVectorContainerElementToMainChain(size_t depth, size_t index)
{
	size_t	lower_jacob_num;
	size_t	uper_jacob_num;

	if (depth = 0 || index == 0)
		return ;

	//	get the jacob numbers above and below our target index.
	{
		size_t i = 1;
		uper_jacob_num = PmergeMe::jacob_seq(i);
		while (uper_jacob_num < index)
		{
			lower_jacob_num = uper_jacob_num;
			i++;
			uper_jacob_num = PmergeMe::jacob_seq(i);
		}
	}
	size_t	target_index;

	// find our target index.
	{
		size_t absolute_index = this->getVectorContainerAbsoluteIndex(1, index);
		
	}
}

//	internal methods.

void	PmergeMe::sortVectorContainer(void)
{
	std::cout << "\ndoing the shorting of the vector.\n" << std::endl;
	size_t i = 0;
	while (this->getVectorContainerChainSize(i))
	{
		this->sortVectorContainerMainChainPairs(i);
		i++;
	}
	i--;
	i--;
}

//	methods.


void	PmergeMe::run(void)
{
	std::cout << "\n//\truning the thing." << std::endl;

	this->sortVectorContainer();

	std::cout << "the correct one is:\t\t" << this->_sortedContainer << std::endl;
	std::cout << "the result of the vector is:\t" << this->_vectorContainer << std::endl;
}







