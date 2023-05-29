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

int RPN::_calculate(char operand) {
  int a = this->_stack.top(); // new number pushed in the stack
  this->_stack.pop();
  int b = this->_stack.top(); // last result calculated
  this->_stack.pop();
  int result;
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
  return result;
}

void RPN::_parseOperation(const std::string &operation) {
  std::string validOperand = "+-*/";

  for (size_t i = 0; i != operation.length(); i++) {
    if (operation[i] == ' ')
      continue;
    if (isdigit(operation[i])) {
      std::string number(1, operation[i]);
      this->_stack.push(std::stoi(number));
    } else if (validOperand.find(operation[i]) != std::string::npos) {
      if (this->_stack.size() < 2) // need at least 2 numbers to calculate
        throw std::runtime_error("Not enough numbers in the stack");
      this->_stack.push(this->_calculate(operation[i]));
    } else
      throw std::runtime_error("Invalid character " +
                               std::string(1, operation[i]) + "");
  }
}

int RPN::getResult() const {
  if (this->_stack.size() != 1)
    throw std::runtime_error("Invalid operation");
  return this->_stack.top();
}
