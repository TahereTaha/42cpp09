#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>

class PmergeMe
{
	//	domain data.
	private:
		size_t						_comparisonCount;
		std::vector<unsigned long>	_unsortedContainer;
		std::vector<unsigned long>	_sortedContainer;
		std::vector<unsigned long>	_vectorContainer;
		std::list<unsigned long>	_listContainer;

	//	some debuging and visualasing functions.
	private:
		void	printVectorContainer(void) const ;
		void	printVectorContainerPairs(size_t depth) const ;
		void	printVectorContainerMainChain(size_t depth) const ;
		void	printVectorContainerPendChain(size_t depth) const ;
		void	printVectorContainerUnpairdElement(size_t depth) const ;

	//	some helper functions.
	private:
		static unsigned long	stoul(std::string str);
		static unsigned long	jacob_seq(unsigned long n);
		static size_t			pow(size_t base, size_t exponent);

	//	some methods for the implementation of the algorithm.
	private:
		void	vectorSortPairs(void);

	//	some internal methods.
	private:
		void	sortVectorContainer(void);
		void	sortListContainer(void);

		//	returns the time in microseconds.
		unsigned long	testVectorSort(void);
		unsigned long	testListSort(void);
	public:

		PmergeMe(void);
		PmergeMe(const PmergeMe & src);
		~PmergeMe(void);
		PmergeMe & operator = (const PmergeMe & src);

		PmergeMe(int ac, char **av);

		void run(void);
};

//	stream insertion operator overloading for vector.
template <typename T>
std::ostream & operator << (std::ostream & out_s, const std::vector<T>& obj)
{
	size_t	i = 0;

	while (i < obj.size())
	{
		std::cout << obj[i];
		i++;
		if (i < obj.size())
			std::cout << " ";
	}

	return (out_s);
}

//	stream insertion operator overloading for list.
template <typename T>
std::ostream & operator << (std::ostream & out_s, const std::list<T>& obj)
{
	typename std::list<T>::const_iterator	iter = obj.begin();
	typename std::list<T>::const_iterator	end = obj.end();

	while (iter != end)
	{
		std::cout << *iter;
		iter++;
		if (iter != end)
			std::cout << " ";
	}

	return (out_s);
}



//	todo list:
//	- [x] make the stoul.
//	- [x] make the stream insertion operator for the vector and list.
//	- [x] parse the imput.
//	- [x] set up some internal values.
//	- [x] make a function that returns the Jacobsthal sequence.
//	- [ ] write the algorithm for the vector.
//	- [ ] write the algorithm for the list.
//	- [ ] time the algorithm.
//	- [ ] print all of this to terminal.

