#include <iostream>
#include <string>

int main(int, char **)
{
  string line;
  while (getline(std::cin, line) && line != "end")
    std::cout << line << std::endl;
}
