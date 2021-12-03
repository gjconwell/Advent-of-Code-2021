#include <iostream>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day2/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  int value;
  int position = 0;
  int depth = 0;
  int aim = 0;
  while (istr >> info) {
    if (info == "forward") {
      istr >> value;
      position += value;
      depth += aim * value;
    } else if (info == "down") {
      istr >> value;
      aim += value;
    } else if (info == "up") {
      istr >> value;
      aim -= value;
    }
  }
  std::cout << position * depth << '\n';
  return 0;
}
