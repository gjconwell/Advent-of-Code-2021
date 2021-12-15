#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day14/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

long int Step(std::map<std::string, long int> &polymer, std::map<char,long int> &chars,
         std::vector<std::pair<std::string, char>> &instruct) {
  std::map<std::string, long int> temp;
  std::map<std::string, long int>::iterator it = polymer.begin();
  while (it != polymer.end()) {
    for (int i = 0; i < (int) instruct.size(); i++) {
      if (instruct[i].first == it->first) {
        std::string pair1 = "";
        pair1 += it->first[0];
        pair1 += instruct[i].second;
        std::string pair2 = "";
        pair2 += instruct[i].second;
        pair2 += it->first[1];
        temp[pair1] += it->second;
        temp[pair2] += it->second;
        chars[instruct[i].second] += it->second;
        break;
      }
    }
    it++;
  }
  polymer = temp;
  long int max = 0;
  std::map<char, long int>::iterator it2 = chars.begin();
  long int min = it2->second;
  while (it2 != chars.end()) {
    if (max < it2->second) {
      max = it2->second;
    }
    if (min > it2->second) {
      min = it2->second;
    }
    it2++;
  }
  return max - min;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::map<char,long int> chars;
  std::map<std::string, long int> polymer;
  std::vector<std::pair<std::string, char>> instruct;
  int iter = 0;
  while (istr >> info) {
    if (iter == 0) {
      for (int i = 0; i < (int) info.size() - 1; i++) {
        chars[info[i]]++;
        std::string num = "";
        num += info[i];
        num += info[i + 1];
        polymer[num]++;
      }
      chars[info[info.size() - 1]]++;
    } else {
      std::string temp = info;
      istr >> info;
      istr >> info;
      instruct.push_back(std::make_pair(temp, info[0]));
    }
    iter++;
  }
  long int output = 0;
  for (int i = 0; i < 40; i++) {
    output = Step(polymer, chars, instruct);
  }
  std::cout << output << '\n';
  return 0;
}
