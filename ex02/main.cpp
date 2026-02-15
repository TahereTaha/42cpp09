#include <iostream>
#include "PmergeMe.hpp"
#include <stdexcept>

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return (42);
	}

	try
	{
		PmergeMe	merge_insertion(ac, av);
		merge_insertion.run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

