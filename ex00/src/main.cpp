/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:11:16 by abastos           #+#    #+#             */
/*   Updated: 2023/05/30 01:11:19 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
  if (argc != 2 || argv[1][0] == '\0') {
    std::cerr << FRED("Error: Usage: ./btc [path to file]") << std::endl;
    return 1;
  }

  BitcoinExchange exchange;

  std::string path(argv[1]);

  try {
    exchange.loadFile("data/data.csv");
    exchange.proccessData(path);
  } catch (std::exception &e) {
    std::cerr << FRED("Error: ") << e.what() << std::endl;
    return 1;
  }

  return 0;
}
