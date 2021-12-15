#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day14/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

void Step(std::list<char> &polymer, std::map<char, int> &chars,
          std::vector<std::pair<std::string, char>> &instruct) {
  std::list<char>::iterator it = polymer.begin();
  std::list<char>::iterator itprev = polymer.begin();
  std::vector<std::pair<char, std::list<char>::iterator >> stage;
  it++;
  while (it != polymer.end()) {
    std::string ppair = "";
    ppair += *itprev;
    ppair += *it;
    for (int i = 0; i < (int) instruct.size(); i++) {
      if (instruct[i].first == ppair) {
        chars[instruct[i].second]++;
        stage.push_back(std::make_pair(instruct[i].second, it));
      }
    }
    itprev++;
    it++;
  }
  for (int i = 0; i < (int) stage.size(); i++) {
    polymer.insert(stage[i].second, stage[i].first);
  }
}


int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::map<char, int> chars;
  std::list<char> polymer;
  std::vector<std::pair<std::string, char>> instruct;
  int iter = 0;
  while (istr >> info) {
    if (iter == 0) {
      for (int i = 0; i < (int) info.size(); i++) {
        polymer.push_back(info[i]);
        chars[info[i]]++;
      }
    } else {
      std::string temp = info;
      istr >> info;
      istr >> info;
      instruct.push_back(std::make_pair(temp, info[0]));
    }
    iter++;
  }
  for (int i = 0; i < 10; i++) {
    Step(polymer, chars, instruct);
  }
  int max = 0;
  std::map<char, int>::iterator it = chars.begin();
  int min = it->second;
  while (it != chars.end()) {
    it->first;
    if (max < it->second) {
      max = it->second;
    }
    if (min > it->second) {
      min = it->second;
    }
    it++;
  }
  std::cout << max - min << '\n';
  return 0;
}
