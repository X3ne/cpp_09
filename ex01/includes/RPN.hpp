/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:01:16 by abastos           #+#    #+#             */
/*   Updated: 2023/06/28 12:20:04 by abastos          ###   ########lyon.fr   */
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

#include <exception>
#include <iostream>
#include <stack>
#include <string>
#include <climits>
#include<cstdlib>

class RPN {
public:
  RPN(const std::string &operation);
  RPN(const RPN &src);
  ~RPN();

  RPN &operator=(const RPN &rhs);

  double getResult() const;

private:
  RPN();
  void _parseOperation(const std::string &operation);
  double _calculate(char operand);

  std::stack<int> _stack;
};
