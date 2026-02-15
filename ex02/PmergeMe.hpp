#pragma once

#include <string>
#include <vector>
#include <list>

class PmergeMe
{
	//	some helper functions.
	private:
		static unsigned long	stoul(std::string str);

	//	some internal methods.
	private:
		std::vector<unsigned long>	_intactContainer;
		std::vector<unsigned long>	_sortedContainer;
		std::vector<unsigned long>	_vectorContainer;
		std::list<unsigned long>		_listContainer;

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

//	todo list:
//	- [ ] make the stoul.
//	- [ ] parse the imput.
//	- [ ] set up some internal values.
//	- [ ] write the algorithm.
//	- [ ] time the algorithm.
//	- [ ] print all of this to terminal.

