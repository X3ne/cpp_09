/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:11:40 by abastos           #+#    #+#             */
/*   Updated: 2023/06/27 13:34:22 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << FRED("Error: Usage: ./PmergeMe [...integers]")
				  << std::endl;
		return 1;
	}

	int size = argc - 1;
	int *array = new int[size];

	for (int i = 0; i < size; i++) {
		double d = atof(argv[i + 1]);
		if (!std::isdigit(*argv[i + 1]) || std::floor(d) != d || d > INT_MAX) {
			std::cerr << FRED("Error: Usage: ./PmergeMe [...integers]")
					  << std::endl;
			return 1;
		}
		array[i] = atoi(argv[i + 1]);
	}

	PmergeMe pmergeMe(size, array);

	std::vector<int> outputVector;

	clock_t start, end;

	start = clock();

	outputVector = pmergeMe.sort(array, size);

	end = clock();

	std::cout << FYEL("Output vector: ") << std::endl;
	pmergeMe.printVector(outputVector);

	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	std::cout << "Time taken to sort : " << std::fixed << time_taken
			  << std::setprecision(5);
	std::cout << " sec " << std::endl;

	std::deque<int> outputdeque;

	start = clock();

	outputdeque = pmergeMe.sortDeque(array, size);

	end = clock();

	std::cout << FYEL("Output deque: ") << std::endl;
	pmergeMe.printDeque(outputdeque);

	time_taken = double(end - start) / double(CLOCKS_PER_SEC);

	std::cout << "Time taken to sort : " << std::fixed << time_taken
			  << std::setprecision(5);
	std::cout << " sec " << std::endl;

	delete[] array;

	return 0;
}
