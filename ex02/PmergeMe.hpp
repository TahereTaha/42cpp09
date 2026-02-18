#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>

class PmergeMe
{
	//	domain data.
	private:
		size_t				_comparisonCount;
		std::vector<size_t>	_unsortedContainer;
		std::vector<size_t>	_sortedContainer;
		std::vector<size_t>	_vectorContainer;
		std::list<size_t>	_listContainer;

	//	some debuging and visualasing functions.
	private:
		void	printVectorContainer(void) const ;
		
		void	printVectorContainerMainChainElementLean(size_t depth, size_t index) const ;
		void	printVectorContainerMainChainElement(size_t depth, size_t index) const ;
		
		void	printVectorContainerMainChain(size_t depth) const ;
		void	printVectorContainerPendChain(size_t depth) const ;
		void	printVectorContainerUnpairdElement(size_t depth) const ;
		
		void	printVectorContainerMainChainPairs(size_t depth) const ;

	//	some helper functions.
	private:
		static size_t	stoul(std::string str);
		static size_t	jacob_seq(size_t n);
		static size_t	pow(size_t base, size_t exponent);

	//	some methods for the implementation of the algorithm.
	private:
		size_t	getVectorContainerMainChainSize(size_t depth) const ;
		size_t	&getVectorContainerMainChainElement(size_t depth, size_t index);
		
		void	sortVectorContainerMainChainPairs(size_t depth);

	//	some internal methods.
	private:
		void	sortVectorContainer(void);
		void	sortListContainer(void);

		//	returns the time in microseconds.
		size_t	testVectorSort(void);
		size_t	testListSort(void);
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
//	- [ ] make some data manipulation functions for the vector.
//		- [ ] make the get main chain size.
//		- [ ] make the get main chain element.
//		- [ ] make the swap main chain elements.
//	- [ ] write up some debuging functions.
//	- [ ] write the algorithm for the vector.
//	- [ ] write the algorithm for the vector.
//	- [ ] write the algorithm for the list.
//	- [ ] time the algorithm.
//	- [ ] print all of this to terminal.

