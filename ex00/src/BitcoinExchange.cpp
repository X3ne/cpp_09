/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abastos <abastos@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:11:06 by abastos           #+#    #+#             */
/*   Updated: 2023/06/28 12:14:49 by abastos          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

double stringtod(const std::string &value) {
  std::stringstream ss;
  ss << value;

  double d=0.0;
  ss >> d;

  return d;
}

BitcoinExchange::BitcoinExchange() {
  if (VERBOSE)
    std::cout << FGRN("BitcoinExchange constructor called") << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
  if (VERBOSE)
    std::cout << "BitcoinExchange copy constructor called" << std::endl;
  *this = src;
}

BitcoinExchange::~BitcoinExchange() {
  if (VERBOSE)
    std::cout << FRED("BitcoinExchange destructor called") << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
  if (VERBOSE)
    std::cout << "BitcoinExchange assignation operator called" << std::endl;
  if (this != &rhs) {
    this->_data = rhs._data;
  }
  return *this;
}

time_t BitcoinExchange::_parseDate(const std::string &date) const {
  struct tm tm;
  std::memset(&tm, 0, sizeof(struct tm));
  int nDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (date.length() != 10 || !strptime(date.c_str(), "%Y-%m-%d", &tm))
    throw std::runtime_error("bad input => " + date);

  /**
   * If the year is a leap year -> check if the month is February and the day
   * not exceed 28 If the month is February -> check if the day is not exceed 28
   * Else -> check if the day is not exceed 30 or 31 depending on the month
   */
  int month = tm.tm_mon + 1;
  int year = tm.tm_year + 1900;
  if (month == 2 &&
      ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0)))) {
    if (tm.tm_mday > nDays[month - 1] + 1)
      throw std::runtime_error("Invalid date format");
  } else if (tm.tm_mday > nDays[month - 1])
    throw std::runtime_error("Invalid date format");

  return dateToTimestamp(tm);
}

void BitcoinExchange::loadFile(const std::string &path) {
  std::ifstream ifs;
  std::string line;

  if (VERBOSE)
    std::cout << FYEL("Load data from file: " + path + "") << std::endl;

  ifs.open(path.c_str(), std::ifstream::in);
  if (!ifs.is_open() || ifs.bad())
    throw std::runtime_error("Could not open file");

  std::getline(ifs, line);
  while (std::getline(ifs, line)) {
    std::string sDate = line.substr(0, line.find(','));
    try {
      time_t date = this->_parseDate(sDate);
      std::string price = line.substr(line.find(',') + 1);

      this->_data.insert(std::pair<time_t, double>(date, stringtod(price)));
    } catch (std::exception &e) {
      std::cerr << FRED("Error: ") << e.what() << std::endl;
      continue;
    }
  }
  if (VERBOSE)
    std::cout << FGRN("Data loaded") << std::endl;
  ifs.close();
}

const double &BitcoinExchange::getRate(const time_t &date) const {
  std::map<time_t, double>::const_iterator it = this->_data.find(date);

  if (date < this->_data.begin()->first)
    throw std::runtime_error("Date out of range");

  if (it == this->_data.end()) {
    it = this->_data.upper_bound(date);
    it--;
    if (it == this->_data.end())
      throw std::runtime_error("No data for this date");
  }
  return it->second;
}

void BitcoinExchange::proccessData(const std::string &path) const {
  std::ifstream ifs;
  std::string line;
  std::string allowed = "0123456789.-";

  if (VERBOSE)
    std::cout << FYEL("Process data from file: " + path + "") << std::endl;

  ifs.open(path.c_str(), std::ifstream::in);
  if (!ifs.is_open() || ifs.bad())
    throw std::runtime_error("Could not open file");

  std::getline(ifs, line);
  while (std::getline(ifs, line)) {
    try {
      std::string sDate = line.substr(0, line.find(" | "));
      time_t date = this->_parseDate(trim(sDate));
      std::string priceStr = line.substr(line.find(" | ") + 3);

      if (priceStr.find_first_not_of(allowed) != std::string::npos) {
        throw std::invalid_argument("not a number");
      }

      double price = stringtod(priceStr);

      if (price > 1000)
        throw std::invalid_argument("too large number");
      if (price < 0)
        throw std::invalid_argument("not a positive number");

      double dbPrice = this->getRate(date);
      std::cout << sDate << " => " << price << " = " << price * dbPrice << std::endl;
    } catch (std::exception &e) {
      std::cerr << FRED("Error: ") << e.what() << std::endl;
      continue;
    }
  }
  if (VERBOSE)
    std::cout << FGRN("Data processed") << std::endl;
  ifs.close();
}

const std::string &trim(std::string &s) {
  const char *t = " \t\n\r\f\v";
  s.erase(0, s.find_first_not_of(t));
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

time_t dateToTimestamp(struct tm &tm) {
  time_t time = std::mktime(&tm) - timezone;
  return time;
}
