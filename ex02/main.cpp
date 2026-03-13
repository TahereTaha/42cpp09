#include <iostream>
#include "PmergeMe.hpp"
#include <stdexcept>

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error a" << std::endl;
		return (42);
	}
	std::cout << "hola " << ac << " hola" << std::endl;
	try
	{
		PmergeMe	merge_insertion(ac, av);
		merge_insertion.run();
		std::cout << "the algorithm finished." << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}

