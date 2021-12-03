#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day3/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

int rating(std::vector<std::string> power, int bit, char first, char second) {
  if (power.size() == 1) {
    return std::stoi(power[0], nullptr, 2);
  }
  int zeroes = 0;
  int ones = 0;
  for (int j = 0; j < (signed) power.size(); j++) {
    if (power[j][bit] == '0') {
      zeroes++;
    } else {
      ones++;
    }
  }
  if (zeroes > ones) {
    int j = 0;
    while (j != (signed) power.size()) {
      if (power[j][bit] == first) {
        if (j == 0) {
          power.erase(power.begin());
        } else {
          power.erase(power.begin() + j);
        }
      } else {
        j++;
      }
    }
  } else {
    int j = 0;
    while (j != (signed) power.size()) {
      if (power[j][bit] == second) {
        if (j == 0) {
          power.erase(power.begin());
        } else {
          power.erase(power.begin() + j);
        }
      } else {
        j++;
      }
    }
  }
  return rating(power, bit + 1, first, second);
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::vector<std::string> power;
  while (istr >> info) {
    power.push_back(info);
  }
  std::cout << rating(power, 0, '1', '0') * rating(power, 0, '0', '1') << '\n';
  return 0;
}
