#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day15/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe
//695

int path(std::vector<std::vector<int>> &map,
         int i, int j, int risk, int &min){
  risk += map[i][j]; 
  if (risk >= min) {
    // std::cout << "terminate" << '\n';
    return min;
  }
  // mem.push_back(std::make_pair(i, j));
  if (j + 1 == (int) map.size() && i + 1 == (int) map.size()) {
    // for (int k = 0; k < (int) mem.size(); k++) {
    //   std::cout << mem[k].first << "," << mem[k].second << ' ';
    // }
    // std::cout << '\n';
    if (risk < min) {
      min = risk;
    }
    std::cout << "finished " << risk << '\n';
    return min;
  }
  if (i + 1 < (int) map.size() && j + 1 < (int) map[0].size()) {
    // std::cout << map[i + 1][j] << " " <<  map[i][j + 1] << '\n';
    path(map, i + 1, j, risk, min);
    path(map, i, j + 1, risk, min);
  } else if (j + 1 < (int) map[0].size()) {
    path(map, i, j + 1, risk, min);
  } else if (i + 1 < (int) map.size()) {
    path(map, i + 1, j, risk, min);
  }
  return min;
}

int borderline(std::vector<std::vector<int>> &map) { 
  int i = 0;
  int j = 0;
  int risk = -map[0][0];
  while (i + 1 < (int) map.size() || j + 1 < (int) map[0].size()) {
    risk += map[i][j];
    if (j + 1 < (int) map[0].size()) {
      j++;
    } else if (i + 1 < (int) map.size()) {
      i++;
    }
  }
  return risk;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::vector<std::vector<int>> map;
  std::string info;
  while (istr >> info) {
    std::vector<int> temp;
    for (int i = 0; i < (signed) info.size(); i++) {
      temp.push_back(info[i] - '0');
    }
    map.push_back(temp);
  }
  // std::vector<std::pair<int, int>> mem;
  int min = borderline(map);
  std::cout << min << '\n';
  
  std::cout << path(map, 0, 0, -map[0][0], min) - map[0][0]<< '\n';
  return 0;
}
