#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day9/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

int Expand(int i, int j, std::vector<std::vector<int>> &heights, int &tally){
  if (heights[i][j] == 9 || heights[i][j] == -1) {
    return tally;
  } else {
    tally++;
    if (i - 1 >= 0) {
      heights[i][j] = -1;
      Expand(i - 1, j, heights, tally);
    }
    if (i + 1 < (signed) heights.size()) {
      heights[i][j] = -1;
      Expand(i + 1, j, heights, tally);
    }
    if (j - 1 >= 0) {
      heights[i][j] = -1;
      Expand(i, j - 1, heights, tally);
    } 
    if (j + 1 < (signed) heights[i].size()) {
      heights[i][j] = -1;
      Expand(i, j + 1, heights, tally);
    }
    return tally;
  }
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::vector<std::vector<int>> heights;
  std::string info;
  while (istr >> info) {
    std::vector<int> temp;
    for (int i = 0; i < (signed) info.size(); i++) {
      temp.push_back(info[i] - '0');
    }
    heights.push_back(temp);
  }
  std::vector<int> basin;
  for (int i = 0; i < (signed) heights.size(); i++) {
    for (int j = 0; j < (signed) heights[i].size(); j++) {
      if (heights[i][j] != 9 && heights[i][j] != -1) {
        int tally = 0;
        int basinSize = Expand(i, j, heights, tally);
        if (basinSize != 0) {
          basin.push_back(basinSize);
        }
      }
    }
  }
  int first = 0;
  int second = 0;
  int third = 0;
  int index = 0;
  for (int i = 0; i < (signed) basin.size(); i++) {
    if (first < basin[i]) {
      index = i;
      first = basin[i];
    } 
  }
  basin.erase(basin.begin() + index);
  for (int i = 0; i < (signed) basin.size(); i++) {
    if (second < basin[i]) {
      index = i;
      second = basin[i];
    } 
  }
  basin.erase(basin.begin() + index);
  for (int i = 0; i < (signed) basin.size(); i++) {
    if (third < basin[i]) {
      index = i;
      third = basin[i];
    } 
  }
  std::cout << first * second * third << '\n';
  return 0;
}
