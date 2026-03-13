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
#include <ctime>
#include <cmath>

//	canonical orthodox form.
PmergeMe::PmergeMe(void)
{
	this->_vectorContainerComparisonCount = 0;
	this->_listContainerComparisonCount = 0;
}

PmergeMe::PmergeMe(const PmergeMe & src)
{
	*this = src;
}

PmergeMe & PmergeMe::operator = (const PmergeMe & src)
{
	if (this != &src)
	{
		this->_vectorContainerComparisonCount = src._vectorContainerComparisonCount;
		this->_listContainerComparisonCount = src._listContainerComparisonCount;
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
	this->_vectorContainerComparisonCount = 0;
	this->_listContainerComparisonCount = 0;
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
		std::vector<long>(this->_unsortedContainer.begin(), this->_unsortedContainer.end());
	this->_listContainer = \
		std::list<long>(this->_unsortedContainer.begin(), this->_unsortedContainer.end());

//	std::cout << "my vector container:\t" << this->_vectorContainer << std::endl;
//	std::cout << "my list container:\t" << this->_listContainer << std::endl;
}


//	some helper functions.

long	PmergeMe::stoul(std::string str)
{
	const char	*c_str = str.c_str();
	char		*end_ptr;

	long	val = std::strtoul(c_str, &end_ptr, 10);
	if (*end_ptr != '\0')
		throw (std::invalid_argument("Error"));
	if (val == 0)
	{
		if(std::strpbrk(c_str, "0123456789") > end_ptr)
			throw (std::invalid_argument("Error"));
	}
	if (val == LONG_MAX)
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

tuple3vec	PmergeMe::splitVector(std::vector<long> chain)
{
	//	pair the elements of the vector 
	//and push the bigest to the main chain and the smolest to the pend chain.
	std::vector<long>	main_chain;
	std::vector<long>	pend_chain;
	std::vector<long>	change;
	size_t	i = 0;
	while (i < chain.size() / 2)
	{
		this->_vectorContainerComparisonCount++;
		if (chain[i * 2] < chain[i * 2  + 1])
		{
			pend_chain.push_back(chain[i * 2]);
			main_chain.push_back(chain[i * 2 + 1]);
			change.push_back(0);
			change.push_back(0);
		}
		else
		{
			pend_chain.push_back(chain[i * 2 + 1]);
			main_chain.push_back(chain[i * 2]);
			change.push_back(1);
			change.push_back(-1);
		}
		i++;
	}
	//	if there is a element left out of a pair it is apended to the pend chain at the end.
	if (chain.size() % 2)
	{
		pend_chain.push_back(chain[i * 2]);
		change.push_back(0);
	}

	tuple3vec return_val;
	return_val._elem_1 = main_chain;
	return_val._elem_2 = pend_chain;
	return_val._elem_3 = change;
	return (return_val);
}

std::vector<long>	PmergeMe::combineVectorChangeChains(std::vector<long> change_1, \
		std::vector<long> change_2)
{
	//	apply the second change to the first one.
	{
		std::vector<long> new_change_1;
		size_t	i = 0;
		while (i < change_1.size())
		{
			new_change_1.push_back(change_1[i + change_2[i]]);
			i++;
		}
		change_1 = new_change_1;
	}
	//	add together the changes.
	std::vector<long>	result;
	size_t	i = 0;
	while (i < change_1.size())
	{
		result.push_back(change_1[i] + change_2[i]);
		i++;
	}
	return (result);
}

tuple2vec	PmergeMe::sortVectorPendChain(std::vector<long> pend_chain, std::vector<long> change)
{
	std::vector<long>	new_change;
	std::vector<long>	new_pend_chain;
	size_t	i = 0;
	while (i < change.size())
	{
		new_pend_chain.push_back(pend_chain[i + change[i]]);
		new_change.push_back(change[i] * 2);
		new_change.push_back(change[i] * 2);
		i++;
	}
	//	adding the last unpaird element.
	if (pend_chain.size() > change.size())
	{
		new_pend_chain.push_back(pend_chain[i]);
		new_change.push_back(0);
	}

	tuple2vec return_val;
	return_val._elem_1 = new_pend_chain;
	return_val._elem_2 = new_change;
	return (return_val);
}

size_t		PmergeMe::binarySearchVectorElementInChain(std::vector<long> chain, long element)
{
	size_t	low = 0;
	size_t	high = chain.size();
	while (low != high)
	{
		size_t	span = high - low;
		size_t	index = low + (span / 2);
		this->_vectorContainerComparisonCount++;
		long	comparison = element - chain[index];
		if (comparison < 0)
		{
			high = index;
		}
		else if (comparison == 0)
		{
			return (index);
		}
		else
		{
			low = index + 1;
		}
	}
	return (low);
}

tuple2vec	PmergeMe::insertVectorPendToMainChain(std::vector<long> main_chain, \
		std::vector<long> pend_chain)
{
	std::vector<long>	result_chain;
	//	the index of the biger element on the end chain.
	std::vector<long>	pend_chain_order_index;

	std::vector<long>	change;

	//	populate the pend_chain_order_index.
	{
		size_t	i = 0;
		while (i < pend_chain.size())
		{
			pend_chain_order_index.push_back(i + 1);
			i++;
		}
	}
	//	populate the result_chain;
	{
		result_chain.push_back(pend_chain[0]);
		size_t	i = 0;
		while (i < main_chain.size())
		{
			result_chain.push_back(main_chain[i]);
			i++;
		}
	}
	//	populate the change chain.
	{
		size_t	i = 0;
		change.push_back(0);
		while (i < main_chain.size())
		{
			change.push_back((i * 2) + 1);
			i++;
		}
	}
	

	size_t	i = 2;
	size_t	jacob_num = this->jacob_seq(i);
	while (jacob_num < pend_chain.size())
	{
		i++;
		jacob_num = this->jacob_seq(i);
		size_t	inserted_elem_index = std::min(jacob_num, pend_chain.size()) - 1;
		while (inserted_elem_index >= this->jacob_seq(i - 1))
		{
			std::vector<long>	search_chain;
			//	fill the search chain.
			if (inserted_elem_index == pend_chain.size() - 1)
			{
				search_chain = result_chain;
			}
			else
			{
				long	i2 = 0;
				while (i2 < pend_chain_order_index[inserted_elem_index])
				{
					search_chain.push_back(result_chain[i2]);
					i2++;
				}
			}
			size_t	target_insertion_index = this->binarySearchVectorElementInChain(search_chain, pend_chain[inserted_elem_index]);
			//	insert the element on the result_chain.
			{
				std::vector<long>	new_result_chain;
				size_t	i2 = 0;
				while (i2 < target_insertion_index)
				{
					new_result_chain.push_back(result_chain[i2]);
					i2++;
				}
				new_result_chain.push_back(pend_chain[inserted_elem_index]);
				while (i2 < result_chain.size())
				{
					new_result_chain.push_back(result_chain[i2]);
					i2++;
				}
				result_chain = new_result_chain;
			}
			//	update the pend_chain_order_index
			{
				size_t	i2 = 0;
				while (i2 < pend_chain_order_index.size() && pend_chain_order_index[i2] < (long) target_insertion_index)
				{
					i2++;
				}
				while (i2 < pend_chain_order_index.size())
				{
					pend_chain_order_index[i2]++;
					i2++;
				}
			}
			//	update the change_chain.
			{
				std::vector<long>	new_change;
				size_t	i2 = 0;
				while (i2 < target_insertion_index &&  i2 < change.size())
				{
					new_change.push_back(change[i2]);
					i2++;
				}
				new_change.push_back(inserted_elem_index * 2);
				while (i2 < change.size())
				{
					new_change.push_back(change[i2]);
					i2++;
				}
				change = new_change;
			}
			inserted_elem_index--;
		}
	}
	//	transform change to the final form.
	{
		size_t	i = 0;
		while (i < change.size())
		{
			change[i] = change[i] - i;
			i++;
		}
	}
	tuple2vec	return_val;
	return_val._elem_1 = result_chain;
	return_val._elem_2 = change;
	return (return_val);
}

tuple2vec	PmergeMe::sortVector(std::vector<long> chain)
{
	std::vector<long>	change;
	std::vector<long>	main_chain;
	std::vector<long>	pend_chain;

	if (chain.size() == 1)
	{
		change.push_back(0);
		tuple2vec return_val;
		return_val._elem_1 = chain;
		return_val._elem_2 = change;
		return (return_val);
	}

	//	split both chains.
	{
		tuple3vec	return_val = this->splitVector(chain);
		main_chain = return_val._elem_1;
		pend_chain = return_val._elem_2;
		change = return_val._elem_3;
	}

	//	sort the main chain and adjust the pend chain.
	{
		std::vector<long>	sub_change;
		//	recurse untill main chain is sorted.
		{
			tuple2vec	return_val = this->sortVector(main_chain);
			main_chain = return_val._elem_1;
			sub_change = return_val._elem_2;
		}
		//	sort the pend chain and build the new change chain.
		{
			std::vector<long>	new_change;
			tuple2vec	return_val = this->sortVectorPendChain(pend_chain, sub_change);
			pend_chain = return_val._elem_1;
			new_change = return_val._elem_2;

			change = this->combineVectorChangeChains(change, new_change);
		}
	}

	//	insert from the pend chain to the main chain.
	{
		std::vector<long>	new_change;
		tuple2vec	return_val = this->insertVectorPendToMainChain(main_chain, pend_chain);
		chain = return_val._elem_1;
		new_change = return_val._elem_2;
		change = this->combineVectorChangeChains(change, new_change);
		//pend_chain = return_val._elem_1;
		//change = return_val._elem_2;
	}

	tuple2vec	return_val;
	return_val._elem_1 = chain;
	return_val._elem_2 = change;
	return (return_val);
}

//	internal methods.

//	returns 1 on correct and 0 on incorect.
static int	check_correct(const std::vector<long> &correct, const std::vector<long> &test)
{
	size_t	i = 0;
	while (i < correct.size())
	{
		if (correct[i] != test[i])
			return (0);
		i++;
	}
	return (1);
}

void	PmergeMe::sortVectorContainer(void)
{
	clock_t	start = clock();
	tuple2vec	result = sortVector(this->_vectorContainer);
	this->_vectorContainer = result._elem_1;
	if (!check_correct(this->_sortedContainer, this->_vectorContainer))
	{
		std::cout << "incorrect ordering." << std::endl;
		return ;
	}
	clock_t	end = clock();
	std::cout << "Time to process a range of " << this->_sortedContainer.size() << " elements with std::vector : " << ((float) (end - start)) / (CLOCKS_PER_SEC / 1000000) << " us" << std::endl;
}

//	methods.

void	PmergeMe::run(void)
{
//	std::cout << "before:\t" << this->_unsortedContainer << std::endl;
//	std::cout << "after:\t" << this->_sortedContainer << std::endl;
	
	this->sortVectorContainer();
//	this->sortListContainer();
}







