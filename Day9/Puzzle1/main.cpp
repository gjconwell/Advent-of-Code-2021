#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day9/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

int Low(int i, int j, std::vector<std::vector<int>> &heights){
  int focus = heights[i][j];
  if (i == 0) {
    if (j == 0) {
      if (heights[i + 1][j] > focus && heights[i][j + 1] > focus) {
        return focus + 1;
      }
    } else if (j == (signed) heights[i].size() - 1) {
      if (heights[i + 1][j] > focus && heights[i][j - 1] > focus) {
        return focus + 1;
      }
    } else {
      if (heights[i + 1][j] > focus && heights[i][j - 1] > focus && heights[i][j + 1] > focus) {
        return focus + 1;
      }
    }
  } else if (i == (signed) heights.size() - 1) {
    if (j == 0) {
      if (heights[i - 1][j] > focus && heights[i][j + 1] > focus) {
        return focus + 1;
      }
    } else if (j == (signed) heights[i].size() - 1) {
      if (heights[i - 1][j] > focus && heights[i][j - 1] > focus) {
        return focus + 1;
      }
    } else {
      if (heights[i - 1][j] > focus && heights[i][j - 1] > focus && heights[i][j + 1] > focus) {
        return focus + 1;
      }
    }
  } else {
    if (j == 0) {
      if (heights[i - 1][j] > focus && heights[i + 1][j] > focus && heights[i][j + 1] > focus) {
        return focus + 1;
      }
    } else if (j == (signed) heights[i].size() - 1) {
      if (heights[i - 1][j] > focus && heights[i + 1][j] > focus && heights[i][j - 1] > focus) {
        return focus + 1;
      }
    } else {
      if (heights[i - 1][j] > focus && heights[i + 1][j] > focus && heights[i][j - 1] > focus && heights[i][j + 1] > focus) {
        return focus + 1;
      }
    }
  }
  return 0;
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
  int count = 0;
  for (int i = 0; i < (signed) heights.size(); i++) {
    for (int j = 0; j < (signed) heights[i].size(); j++) {
      count += Low(i, j, heights);
    }
  }
  std::cout << count << '\n';
  return 0;
}
