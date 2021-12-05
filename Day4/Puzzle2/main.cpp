#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day4/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe
//29346

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

int Horizontal(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards, bool final) {
  int removal = 0;
  for (int i = 0; i < (signed) boards.size(); i++) {
    for (int j = 0; j < (signed) boards[i].size(); j++) {
      int count = 0;
      for (int k = 0; k < (signed) boards[i][j].size(); k++) {
        if (boards[i][j][k].second == true) {
          count++;
        }
      }
      if (count == 5) {
        if (!final) {
          boards[i].clear();
        }
        count = 0;
        removal++;
      }
    }
  }
  return removal;
}

int Vertical(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards, bool final) {
  int removal = 0;
  for (int i = 0; i < (signed) boards.size(); i++) {
    for (int j = 0; j < (signed) boards[i].size(); j++) {
      int count = 0;
      for (int k = 0; k < (signed) boards[i][j].size(); k++) {
        if (boards[i][k][j].second == true) {
          count++;
        }
      }
      if (count == 5) {
        if (!final) {
          boards[i].clear();
        }
        count = 0;
        removal++;
      }
    }
  }
  return removal;
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

int FindLastBoard(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards) {
  int index;
  for (int i = boards.size() - 1; i > -1 ; i--) {
    if (boards[i].size() > 0) {
      index = i;
      break;
    }
  }
  return index;
}

void LastBoard(std::vector<std::vector<std::vector<std::pair<int, bool>>>> &boards, 
       int index, std::vector<int> &bingonumbers) {
  for (int i = index;  i < (signed) bingonumbers.size(); i++) {
    Flip(boards, bingonumbers[i]);
    if (Horizontal(boards, true) != 0) {
      std::cout << Score(boards, FindLastBoard(boards), bingonumbers[i]) << '\n';
      break;
    }
    if (Vertical(boards, true) != 0) {
      std::cout << Score(boards, FindLastBoard(boards), bingonumbers[i]) << '\n';
      break;
    }
  }
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
  
  int numBoards = boards.size();
  for (int i = 0;  i < (signed) bingonumbers.size(); i++) {
    Flip(boards, bingonumbers[i]);
    if (i > 3) {
      if (numBoards == 1) {
        LastBoard(boards, i, bingonumbers);
        break;
      }
      int temp1 = Horizontal(boards, false);
      if (temp1 != 0) {
        numBoards -= temp1;
      } 
      int temp2 = Vertical(boards, false);
      if (temp2 != 0) {
        numBoards -= temp2;
      } 
    }
  }
  return 0;
}
