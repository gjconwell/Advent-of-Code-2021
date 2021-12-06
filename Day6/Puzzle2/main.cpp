#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day6/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe6

void DayPass (std::map<int, long long int> &fishy) {
  std::map<int, long long int>::iterator it = fishy.begin();
  long long int addFishy = 0;
  long long int reset = 0;
  while (it != fishy.end()) {
    if (it->first == 0) {
      addFishy = it->second;
      reset = it->second;
    } else {
      fishy[it->first - 1] = it->second;
    }
    it++;
  }
  fishy[8] = addFishy;
  fishy[6] += reset;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  
  std::map<int, long long int> fishy;
  for (int i = 0; i < 9; i++) {
    fishy[i] = 0;
  }
  std::string info;
  std::string num;
  istr >> info;
  for (int i = 0; i < (signed) info.length(); i++) {
    num += info[i];
    if (info[i] == ',') {
      fishy[std::stoi(num, nullptr, 10)]++;
      num = "";
    }
  }
  fishy[std::stoi(num, nullptr, 10)]++;
  
  for (int j = 0; j < 256; j++) {
    DayPass(fishy);
  }
  long long int pop = 0;
  std::map<int, long long int>::iterator pit = fishy.begin();
  while (pit != fishy.end()) {
    pop += pit->second;
    pit++;
  }
  std::cout << pop << '\n';
  return 0;
}
