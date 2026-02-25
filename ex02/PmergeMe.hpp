#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>

//	a simple tuple class for only 2 elements.
template <typename T1, typename T2>
class Tuple_2
{
	public:
		//	values of the tuple.
		T1	_elem_1;
		T2	_elem_2;

		Tuple_2(void) {}
		Tuple_2(const Tuple_2<T1, T2> &src) 
		{
			this->_elem_1 = src._elem_1;
			this->_elem_2 = src._elem_2;
		}
		~Tuple_2(void) {}
		Tuple_2 & operator = (const Tuple_2<T1, T2> src) 
		{
			if (this != &src)
			{
				this->_elem_1 = src._elem_1;
				this->_elem_2 = src._elem_2;
			}
			return (*this);
		}
};

//	a simple tuple class for only 3 elements.
template <typename T1, typename T2, typename T3>
class Tuple_3
{
	public:
		//	values of the tuple.
		T1	_elem_1;
		T2	_elem_2;
		T3	_elem_3;

		Tuple_3(void) {}
		Tuple_3(const Tuple_3<T1, T2, T3> &src) 
		{
			this->_elem_1 = src._elem_1;
			this->_elem_2 = src._elem_2;
			this->_elem_3 = src._elem_3;
		}
		~Tuple_3(void) {}
		Tuple_3 & operator = (const Tuple_3<T1, T2, T3> src) 
		{
			if (this != &src)
			{
				this->_elem_1 = src._elem_1;
				this->_elem_2 = src._elem_2;
				this->_elem_3 = src._elem_3;
			}
			return (*this);
		}
};

typedef	Tuple_2<std::vector<long>, std::vector<long> > tuple2vec;
typedef	Tuple_3<std::vector<long>, std::vector<long>, std::vector<long> > tuple3vec;

class PmergeMe
{
	//	domain data.
	private:
		size_t				_vectorContainerComparisonCount;
		size_t				_listContainerComparisonCount;
		std::vector<long>	_unsortedContainer;
		std::vector<long>	_sortedContainer;
		std::vector<long>	_vectorContainer;
		std::list<long>	_listContainer;

	//	some helper functions.
	private:
		static long	stoul(std::string str);
		static size_t	jacob_seq(size_t n);
		static size_t	pow(size_t base, size_t exponent);

	//	some methods for the implementation of the algorithm.
	private:
		//	splits the bector into the main chain and the pend chain and return at the end the position changes of this action.
		tuple3vec	splitVector(std::vector<long>);
		//	it will append one change after the other.
		std::vector<long>	combineVectorChangeChains(std::vector<long> change_1, \
				std::vector<long> change_2);
		//	it will return the sorted pend chain with a change chain for both main and pend chains.
		tuple2vec	sortVectorPendChain(std::vector<long> pend_chain, std::vector<long> change);
		size_t		binarySearchVectorElementInChain(std::vector<long> chain, long element);
		//	it will return the sorted chain with the change.
		tuple2vec	insertVectorPendToMainChain(std::vector<long> main_chain, \
				std::vector<long> pend_chain);
		//	it returns the vector sorted and the change that each element has had.
		tuple2vec	sortVector(std::vector<long>);


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

