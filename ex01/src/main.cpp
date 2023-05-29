#include "RPN.hpp"

int main(int argc, char **argv) {
  if (argc != 2 || argv[1][0] == '\0') {
    std::cerr
        << FRED("Error: Usage: ./RPN [inverted Polish mathematical expression]")
        << std::endl;
    return 1;
  }
  try {
    RPN rpn(argv[1]);

    int result = rpn.getResult();

    std::cout << FGRN("Result: ") << result << std::endl;
  } catch (std::exception &e) {
    std::cerr << FRED("Error: ") << e.what() << std::endl;
    return 1;
  }
  return 0;
}
