#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day3/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::vector<std::string> power;
  while (istr >> info) {
    power.push_back(info);
  }
  
  std::string gamma;
  std::string epsilon;
  for (int i = 0; i < (signed) power[0].length(); i++) {
    int zeroes = 0;
    int ones = 0;
    for (int j = 0; j < (signed) power.size(); j++) {
      if (power[j][i] == '0') {
        zeroes++;
      } else {
        ones++;
      }
    }
    if (zeroes > ones) {
      gamma += "0";
      epsilon += "1";
    } else {
      gamma += "1";
      epsilon += "0";
    }
  }
  int gamma_b = std::stoi(gamma, nullptr, 2);
  int epsilon_b = std::stoi(epsilon, nullptr, 2);
  std::cout << gamma_b * epsilon_b << '\n';
  return 0;
}
