#include <vector>
#include <iostream>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day1/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  int info;
  std::vector<int> depths;
  while (istr >> info) {
    depths.push_back(info);
  }
  int count = 0;
  int temp = 0;
  for (int i = 0; i < (signed) depths.size()-2; i++) {
    int window = depths[i + 2] + depths[i + 1] + depths[i];
    if (i > 0) {
      if (window > temp) {
        count++;
      }
    }
    temp = window;
  }
  std::cout << count << '\n';
  return 0;
}
