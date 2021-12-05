#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day5/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

void AddVec(std::vector<std::pair<int, int>> &pairvec, int x1, int x2, int y1, int y2) {
  if (x1 == x2 || y1 == y2) {
    if (x1 < x2) {
      for (int i = x1; i < x2 + 1; i++) {
        pairvec.push_back(std::make_pair(i, y1));
      }
    } else if (x1 > x2) {
      for (int i = x1; i > x2 -1; i--) {
        pairvec.push_back(std::make_pair(i, y1));
      }
    } else if (y1 < y2) {
      for (int i = y1; i < y2 + 1; i++) {
        pairvec.push_back(std::make_pair(x1, i));
      }
    } else if (y1 > y2) {
      for (int i = y1; i > y2 -1; i--) {
        pairvec.push_back(std::make_pair(x1, i));
      }
    } 
  }
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  
  std::vector<std::pair<int, int>> pairvec;
  std::map<std::pair<int, int>, int> heatmap;
  std::string info;
  while (istr >> info) {
    std::string num1;
    std::string num2;
    int x1;
    int y1;
    bool comma = false;
    for (int i = 0; i < (signed) info.length(); i++) {
      if (info[i] == ',') {
        comma = true;
      } else if (!comma){
        num1 += info[i];
      } else {
        num2 += info[i];
      }
    }
    x1 = std::stoi(num1, nullptr, 10);
    y1 = std::stoi(num2, nullptr, 10);
    istr >> info;
    istr >> info;
    num1 = "";
    num2 = "";
    int x2;
    int y2;
    comma = false;
    for (int i = 0; i < (signed) info.length(); i++) {
      if (info[i] == ',') {
        comma = true;
      } else if (!comma){
        num1 += info[i];
      } else {
        num2 += info[i];
      }
    }
    x2 = std::stoi(num1, nullptr, 10);
    y2 = std::stoi(num2, nullptr, 10);
    AddVec(pairvec, x1, x2, y1, y2);
  }
  for (int i = 0; i < (signed) pairvec.size(); i++) {
    heatmap[pairvec[i]]++;
  }
  int count = 0;
  std::map<std::pair<int, int>, int>::iterator it = heatmap.begin();
  while (it != heatmap.end()) {
    if (it->second > 1) {
      count++;
    }
    it++;
  }
  std::cout << count << '\n';
  return 0;
}
