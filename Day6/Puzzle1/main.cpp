#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day6/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe6

void DayPass (std::vector<int> &fishy) {
  int sizeToday = fishy.size();
  for (int i = 0; i < sizeToday; i++) {
    if (fishy[i] > 0) {
      fishy[i] -= 1;
    } else {
      fishy[i] = 6;
      fishy.push_back(8);
    }
  }
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  
  std::vector<int> fishy;
  
  std::string info;
  std::string num;
  istr >> info;
  for (int i = 0; i < (signed) info.length(); i++) {
    num += info[i];
    if (info[i] == ',') {
      fishy.push_back(std::stoi(num, nullptr, 10));
      num = "";
    }
  }
  fishy.push_back(std::stoi(num, nullptr, 10));
  for (int j = 0; j < 80; j++) {
    DayPass(fishy);
  }
  return 0;
}
