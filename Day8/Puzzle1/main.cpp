#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cmath>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day8/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

bool Unique(std::string info) {
  if (info.length() == 2) {
    return true;
  } else if (info.length() == 3) {
    return true;
  } else if (info.length() == 4) {
    return true;
  } else if (info.length() == 7) {
    return true;
  }
  return false;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  
  std::string info;
  int count = 0;
  while (istr >> info) {
    if (info == "|") {
      for (int i = 0; i < 4; i++) {
        istr >> info;
        if (Unique(info)) {
          count++;
        }
      }
    }
  }
  std::cout << count << '\n';
  return 0;
}
