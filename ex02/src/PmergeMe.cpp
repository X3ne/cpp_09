/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:11:42 by abastos           #+#    #+#             */
/*   Updated: 2023/06/28 13:07:08 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::printVector(std::vector<int> &vc) {
	for (std::vector<int>::iterator it = vc.begin(); it != vc.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void print2dVector(std::vector<std::pair<int, int> > &vector) {
	std::cout << "2D Vector: [";
	for (std::vector<std::pair<int, int> >::iterator it = vector.begin();
		 it != vector.end(); it++) {
		std::cout << "[" << it->first << ", " << it->second << "]";
		if (it + 1 != vector.end()) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

/**
 * Needed because std::swap is a c++11 function
 */
void swapPair(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void sortPairs(std::vector<std::pair<int, int> > &vc) {
	for (std::vector<std::pair<int, int> >::iterator it = vc.begin();
		 it != vc.end(); it++) {
		if (it->first > it->second) {
			swapPair(it->first, it->second);
		}
	}
}

std::vector<std::pair<int, int> > createPairs(std::vector<int> &input) {
	std::vector<std::pair<int, int> > splitedVector;
	std::pair<int, int> pair;
	std::vector<int>::iterator it = input.begin();

	while (it != input.end()) {
		pair = std::make_pair(*it, *(it + 1));
		it += 2;
		splitedVector.push_back(pair);
	}

	sortPairs(splitedVector);

	return splitedVector;
}

void insert(std::vector<std::pair<int, int> > &vc, std::pair<int, int> el,
			int n) {
	if (n < 0) {
		vc[0] = el;
		if (VERBOSE) {
			std::cout << "vc: inserted [" << el.first << ", " << el.second << "] to vc[" << 0 << "]" << std::endl;
		}
		return;
	}

	if (el.second < vc[n].second) {
		vc[n + 1] = vc[n];
		if (VERBOSE) {
			std::cout << "vc: n = " << n << " " << el.second << " < "  << vc[n].second << " -> moved [" << vc[n].first << ", " << vc[n].second << "] to " << "vc[" << n + 1 << "]" << std::endl;
		}
		insert(vc, el, n - 1);
	} else {
		vc[n + 1] = el;
		if (VERBOSE) {
			std::cout << "vc: inserted [" << el.first << ", " << el.second << "] to " << "vc[" << n + 1 << "]" << std::endl;
		}
	}
}

void insertionSortPairs(std::vector<std::pair<int, int> > &vc, int n) {
	if (n <= 0) {
		return;
	}
	insertionSortPairs(vc, n - 1);
	insert(vc, vc[n], n - 1);
}

void sortByLargerValue(std::vector<std::pair<int, int> > &vc) {
	size_t len = vc.size();

	insertionSortPairs(vc, len - 1);
}

std::vector<int> PmergeMe::merge(std::vector<std::pair<int, int> > &vc, bool hasStraggler,
					   int straggler) {
	std::vector<int> output;
	std::vector<int> pend;

	for (std::vector<std::pair<int, int> >::iterator it = vc.begin();
		 it != vc.end(); it++) {
		output.push_back(it->second);
		pend.push_back(it->first);
	}

	if (VERBOSE) {
		std::cout << "Pend: ";
		this->printVector(pend);
		std::cout << "Output: ";
		this->printVector(output);
	}

	// insert the smallest element of the pend vector in the output vector
	output.insert(output.begin(), pend[0]);
	// pop the smallest element of the pend vector
	pend.erase(pend.begin());

	size_t i = 0;

	while (i < pend.size()) {
		std::vector<int>::iterator insertionPoint =
			std::lower_bound(output.begin(), output.end(), pend[i]);

		output.insert(insertionPoint, pend[i]);

		i += 1;
	}

	if (hasStraggler) {
		std::vector<int>::iterator insertionPoint =
			std::lower_bound(output.begin(), output.end(), straggler);

		output.insert(insertionPoint, straggler);
	}

	return output;
}

void PmergeMe::printDeque(std::deque<int> &deque) {
	for (std::deque<int>::iterator it = deque.begin(); it != deque.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void print2ddeque(std::deque<std::pair<int, int> > &deque) {
	std::cout << "2D deque: [";
	for (std::deque<std::pair<int, int> >::iterator it = deque.begin();
		 it != deque.end(); it++) {
		std::cout << "[" << it->first << ", " << it->second << "]";
		if (it + 1 != deque.end()) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

void sortPairs(std::deque<std::pair<int, int> > &dq) {
	for (std::deque<std::pair<int, int> >::iterator it = dq.begin();
		 it != dq.end(); it++) {
		if (it->first > it->second) {
			swapPair(it->first, it->second);
		}
	}
}

std::deque<std::pair<int, int> > createPairs(std::deque<int> &input) {
	std::deque<std::pair<int, int> > splitedDeque;
	std::pair<int, int> pair;
	std::deque<int>::iterator it = input.begin();

	while (it != input.end()) {
		pair = std::make_pair(*it, *(it + 1));
		it += 2;
		splitedDeque.push_back(pair);
	}

	sortPairs(splitedDeque);

	return splitedDeque;
}

void insert(std::deque<std::pair<int, int> > &dq, std::pair<int, int> el,
			int n) {
	if (n < 0) {
		dq[0] = el;
		if (VERBOSE) {
			std::cout << "dq: inserted [" << el.first << ", " << el.second << "] to dq[" << 0 << "]" << std::endl;
		}
		return;
	}

	if (el.second < dq[n].second) {
		dq[n + 1] = dq[n];
		if (VERBOSE) {
			std::cout << "dq: n = " << n << " " << el.second << " < "  << dq[n].second << " -> moved [" << dq[n].first << ", " << dq[n].second << "] to " << "dq[" << n + 1 << "]" << std::endl;
		}
		insert(dq, el, n - 1);
	} else {
		if (VERBOSE) {
			std::cout << "dq: inserted [" << el.first << ", " << el.second << "] to " << "dq[" << n + 1 << "]" << std::endl;
		}
		dq[n + 1] = el;
	}
}

void insertionSortPairs(std::deque<std::pair<int, int> > &dq, int n) {
	if (n == 0) {
		return;
	}
	insertionSortPairs(dq, n - 1);
	insert(dq, dq[n], n - 1);
}

void sortByLargerValue(std::deque<std::pair<int, int> > &dq) {
	size_t len = dq.size();

	insertionSortPairs(dq, len - 1);
}

std::deque<int> PmergeMe::merge(std::deque<std::pair<int, int> > &dq, bool hasStraggler,
					  int straggler) {
	std::deque<int> output;
	std::deque<int> pend;

	for (std::deque<std::pair<int, int> >::iterator it = dq.begin();
		 it != dq.end(); it++) {
		output.push_back(it->second);
		pend.push_back(it->first);
	}

	if (VERBOSE) {
		std::cout << "Pend: ";
		this->printDeque(pend);
		std::cout << "Output: ";
		this->printDeque(output);
	}

	// insert the smallest element of the pend deque in the output deque
	output.insert(output.begin(), pend[0]);
	// pop the smallest element of the pend deque
	pend.erase(pend.begin());

	size_t i = 0;

	while (i < pend.size()) {
		std::deque<int>::iterator insertionPoint =
			std::lower_bound(output.begin(), output.end(), pend[i]);

		output.insert(insertionPoint, pend[i]);

		i += 1;
	}

	if (hasStraggler) {
		std::deque<int>::iterator insertionPoint =
			std::lower_bound(output.begin(), output.end(), straggler);

		output.insert(insertionPoint, straggler);
	}

	return output;
}

const std::deque<int> PmergeMe::sortDeque(int *array, const int &size) {
	std::deque<int> input = std::deque<int>(array, array + size);

	/**
	 * for the algorithm to work, we need to have an even number of elements
	 * so we check if the input has an odd number of elements
	 * if it does, we save the last element in a variable
	 */
	bool hasStraggler = input.size() % 2 == 0 ? false : true;
	int straggler = 0;

	if (hasStraggler) {
		if (input.size() == 1) {
			return input;
		}
		straggler = input.back();
		input.pop_back();
	}

	if (VERBOSE) {
		std::cout << FYEL("hasStraggler: ") << (hasStraggler ? "true" : "false")
				  << std::endl;
		std::cout << FYEL("Straggler value: ") << straggler << std::endl;
	}

	/**
	 * we create a deque of pairs from the input deque
	 * so we can sort the pairs instead of the elements
	 */
	std::deque<std::pair<int, int> > spliteddeque = createPairs(input);

	if (VERBOSE) {
		std::cout << FYEL("Splited deque (pairs unsorted): ") << std::endl;
		print2ddeque(spliteddeque);
	}

	sortByLargerValue(spliteddeque);

	if (VERBOSE) {
		std::cout << FYEL("Splited deque (pairs sorted): ") << std::endl;
		print2ddeque(spliteddeque);
	}

	std::deque<int> output = merge(spliteddeque, hasStraggler, straggler);

	return output;
}

PmergeMe::PmergeMe() {
	if (VERBOSE)
		std::cout << FGRN("PmergeMe default constructor called") << std::endl;
}

PmergeMe::PmergeMe(const int &size, int *array) {
	if (VERBOSE)
		std::cout << FGRN("PmergeMe constructor called") << std::endl;
	for (int i = 0; i < size; i++) {
		this->_inputVector.push_back(array[i]);
		this->_inputList.push_back(array[i]);
	}
}

PmergeMe::PmergeMe(const PmergeMe &src) {
	if (VERBOSE)
		std::cout << "PmergeMe copy constructor called" << std::endl;
	*this = src;
}

PmergeMe::~PmergeMe() {
	if (VERBOSE)
		std::cout << FRED("PmergeMe destructor called") << std::endl;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
	if (VERBOSE)
		std::cout << "PmergeMe assignation operator called" << std::endl;
	if (this != &rhs) {
	}
	return *this;
}

const std::vector<int> PmergeMe::sort(int *array, const int &size) {
	std::vector<int> input = std::vector<int>(array, array + size);

	/**
	 * for the algorithm to work, we need to have an even number of elements
	 * so we check if the input has an odd number of elements
	 * if it does, we save the last element in a variable
	 */
	bool hasStraggler = input.size() % 2 == 0 ? false : true;
	int straggler = 0;

	if (hasStraggler) {
		if (input.size() == 1) {
			return input;
		}
		straggler = input.back();
		input.pop_back();
	}

	if (VERBOSE) {
		std::cout << FYEL("hasStraggler: ") << (hasStraggler ? "true" : "false")
				  << std::endl;
		std::cout << FYEL("Straggler value: ") << straggler << std::endl;
	}

	/**
	 * we create a vector of pairs from the input vector
	 * so we can sort the pairs instead of the elements
	 */
	std::vector<std::pair<int, int> > splitedVector = createPairs(input);

	if (VERBOSE) {
		std::cout << FYEL("Splited vector (pairs unsorted): ") << std::endl;
		print2dVector(splitedVector);
	}

	sortByLargerValue(splitedVector);

	if (VERBOSE) {
		std::cout << FYEL("Splited vector (pairs sorted): ") << std::endl;
		print2dVector(splitedVector);
	}

	std::vector<int> output = merge(splitedVector, hasStraggler, straggler);

	return output;
}
