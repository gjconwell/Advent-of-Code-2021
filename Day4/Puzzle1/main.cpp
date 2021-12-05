#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day4/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

void Flip(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards, 
          int value) {
  for (int i = 0; i < (signed) boards.size(); i++) {
    for (int j = 0; j < (signed) boards[i].size(); j++) {
      for (int k = 0; k < (signed) boards[i][j].size(); k++) {
        if (boards[i][j][k].first == value) {
          boards[i][j][k].second = true;
        }
      }
    }
  }
}

int Horizontal(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards) {
  int output = -1;
  for (int i = 0; i < (signed) boards.size(); i++) {
    for (int j = 0; j < (signed) boards[i].size(); j++) {
      int count = 0;
      for (int k = 0; k < (signed) boards[i][j].size(); k++) {
        if (boards[i][j][k].second == true) {
          count++;
        }
      }
      if (count == 5) {
        output = i;
        break;
      }
    }
  }
  return output;
}

int Vertical(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards) {
  int output = -1;
  for (int i = 0; i < (signed) boards.size(); i++) {
    for (int j = 0; j < (signed) boards[i].size(); j++) {
      int count = 0;
      for (int k = 0; k < (signed) boards[i][j].size(); k++) {
        if (boards[i][k][j].second == true) {
          count++;
        }
      }
      if (count == 5) {
        output = i;
        break;
      }
    }
  }
  return output;
}

int Score(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards, 
          int board, int value) {
  int sum = 0;
  for (int j = 0; j < (signed) boards[board].size(); j++) {
    for (int k = 0; k < (signed) boards[board][j].size(); k++) {
      if (boards[board][j][k].second != true) {
        sum += boards[board][j][k].first;
      }
    }
  }
  return sum * value;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  
  std::string info;
  int intinfo;
  std::vector<int> bingonumbers;
  istr >> info;
  std::string num;
  for (int i = 0; i < (signed) info.length(); i++) {
    if (info[i] == ',') {
      bingonumbers.push_back(std::stoi(num, nullptr, 10));
      num = "";
    } else {
      num += info[i];
    }
  }
  
  int row = 0;
  int column = 0;
  std::vector<std::pair<int, bool>> tempRow;
  std::vector<std::vector<std::pair<int, bool>>> tempColumn;
  std::vector<std::vector<std::vector<std::pair<int, bool>>>> boards;
  while (istr >> intinfo) {
    tempRow.push_back(std::make_pair(intinfo, false));
    row++;
    if (row == 5) {
      tempColumn.push_back(tempRow);
      tempRow.clear();
      row = 0;
      column++;
    }
    if (column == 5) {
      boards.push_back(tempColumn);
      tempColumn.clear();
      column = 0;
    }
  }
  int winner = 0;
  for (int i = 0;  i < (signed) bingonumbers.size(); i++) {
    std::cout << "runs" << '\n';
    Flip(boards, bingonumbers[i]);
    if (i > 3) {
      if (Horizontal(boards) != -1) {
        winner = Horizontal(boards);
        std::cout << Score(boards, winner, bingonumbers[i]) << '\n';
        break;
      } else if (Vertical(boards) != -1){
        winner = Vertical(boards);
        std::cout << Score(boards, winner, bingonumbers[i]) << '\n';
        break;
      }
    }
  }
  return 0;
}
