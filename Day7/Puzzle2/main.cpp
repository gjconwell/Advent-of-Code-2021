#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cmath>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day7/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

int BestFit(std::vector<int> &crabs, int value) {
  int min;
  for (int j = 0; j < value; j++) {
    int count = 0;
    for (int i = 0; i < (signed) crabs.size(); i++) {
      count += (std::abs(crabs[i] - j) * (std::abs(crabs[i] - j) + 1)) / 2;
    }
    if (j == 0) {
      min = count;
    }
    if (min > count) {
      min = count;
    }
  }
  return min;
}

int FindLarge(std::vector<int> &crabs){
  int max = 0;
  for (int i = 0; i < (signed) crabs.size(); i++) {
    if (max < crabs[i]) {
      max = crabs[i];
    }
  }
  return max;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  
  std::vector<int> crabs;
  
  std::string info;
  std::string num;
  istr >> info;
  for (int i = 0; i < (signed) info.length(); i++) {
    num += info[i];
    if (info[i] == ',') {
      crabs.push_back(std::stoi(num, nullptr, 10));
      num = "";
    }
  }
  crabs.push_back(std::stoi(num, nullptr, 10));
  std::cout << BestFit(crabs, FindLarge(crabs)) << '\n';
  return 0;
}
