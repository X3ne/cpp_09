/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:01:16 by abastos           #+#    #+#             */
/*   Updated: 2023/06/28 13:07:22 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// Term syntaxe
#define RST "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#define VERBOSE 0

#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <iomanip>
#include <climits>

class PmergeMe {
	public:
		PmergeMe(const int &size, int *array);
		PmergeMe(const PmergeMe &src);
		~PmergeMe();

		PmergeMe &operator=(const PmergeMe &rhs);

		std::vector<int> &getInputVector() const;
		std::deque<int> &getInputList() const;

		void printVector(std::vector<int> &vc);
		void printDeque(std::deque<int> &deque);

		const std::vector<int> sort(int *array, const int &size);
		std::vector<int> merge(std::vector<std::pair<int, int> > &vc, bool hasStraggler, int straggler);

		const std::deque<int> sortDeque(int *array, const int &size);
		std::deque<int> merge(std::deque<std::pair<int, int> > &vc, bool hasStraggler, int straggler);

	private:
		PmergeMe();
		std::vector<int> _inputVector;
		std::deque<int> _inputList;
};
