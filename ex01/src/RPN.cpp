/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:11:25 by abastos           #+#    #+#             */
/*   Updated: 2023/06/27 17:49:12 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {
	if (VERBOSE)
		std::cout << FGRN("RPN default constructor called") << std::endl;
}

RPN::RPN(const std::string &operation) {
	if (VERBOSE)
		std::cout << FGRN("RPN constructor called") << std::endl;
	this->_parseOperation(operation);
}

RPN::RPN(const RPN &src) {
	if (VERBOSE)
		std::cout << "RPN copy constructor called" << std::endl;
	*this = src;
}

RPN::~RPN() {
	if (VERBOSE)
		std::cout << FRED("RPN destructor called") << std::endl;
}

RPN &RPN::operator=(const RPN &rhs) {
	if (VERBOSE)
		std::cout << "RPN assignation operator called" << std::endl;
	if (this != &rhs) {
		this->_stack = rhs._stack;
	}
	return *this;
}

double RPN::_calculate(char operand) {
	double a = this->_stack.top();	// new number pushed in the stack
	this->_stack.pop();
	double b = this->_stack.top();	// last result calculated
	this->_stack.pop();
	double result;
	switch (operand) {
		case '+':
			result = b + a;
			break;
		case '-':
			result = b - a;
			break;
		case '*':
			result = b * a;
			break;
		case '/': {
			if (a == 0)
				throw std::runtime_error("Division by zero");
			result = b / a;
			break;
		}
	}
	if (result > INT_MAX || result < INT_MIN)
		throw std::runtime_error("Result Overflow");
	return result;
}

void RPN::_parseOperation(const std::string &operation) {
	std::string validOperand = "+-*/";

	for (size_t i = 0; i != operation.length(); i++) {
		if (operation[i] == ' ')
			continue;
		if (std::isdigit(operation[i])) {
			if (std::isdigit(operation[i])) {
				this->_stack.push(operation[i] - '0');
			}
		} else if (validOperand.find(operation[i]) != std::string::npos) {
			if (this->_stack.size() <
				2)	// need at least 2 numbers to calculate
				throw std::runtime_error("Not enough numbers in the stack");
			this->_stack.push(this->_calculate(operation[i]));
		} else
			throw std::runtime_error("Invalid character " +
									std::string(1, operation[i]) + "");
	}
}

double RPN::getResult() const {
	if (this->_stack.size() != 1)
		throw std::runtime_error("Invalid operation");
	return this->_stack.top();
}
