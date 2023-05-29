# Cpp 09

This repository is my work for cpp_09 module at 42 school

**⚠️ For 42 students, please do not copy the code**

### Exercises

**Ex00**

The aim of this exercise is to parse a csv db and a txt file with dates and values.
- Leap years and months with 30 or 31 days are taken into account and validated.
- We need to make a choice about the container we're using, and I've chosen to start with a `std::map<time_t, double>`. This allows me to link a value in the db to a key (the date in timestamp) and easily retrieve this value.
- Dates are converted to timestamps beforehand, so that I can easily modify them to search for values at a nearby date.

**Ex01**

The aim of this exercise is to parse a string of characters representing an [inverted Polish](https://en.wikipedia.org/wiki/Reverse_Polish_notation "Reverse Polish notation wikipedia") mathematical expression and calulate the result.
- Here I've used a `std::stack<int>` container to store my values.
- During execution, my stack fills up when a new digit is detected. When a valid operand is detected and the stack contains 2 digits, they are removed from the stack and the calculation is performed. The result is pushed into the stack and the program continues.

**Ex02**

**🚧 Still in work**

### Project Status
| **Status** | **Evaluation** |
| --- | --- |
| ❌ 0/100 | Uncorrected
