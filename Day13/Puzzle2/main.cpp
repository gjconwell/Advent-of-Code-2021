#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day13/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

void Fold(std::map<std::pair<int, int>, int> &paper, int index, bool yaxe) {
  std::map<std::pair<int, int>, int>::iterator it = paper.begin();
  while (it != paper.end()) {
    if (it->first.second > index && yaxe) {
      if (it->first.second == index) {
        int temp1 = it->first.first;
        int temp2 = it->first.second;
        it++;
        paper.erase(std::make_pair(temp1, temp2));
      } else {
        paper[std::make_pair(it->first.first, index*2 - it->first.second)]++;
        int temp1 = it->first.first;
        int temp2 = it->first.second;
        it++;
        paper.erase(std::make_pair(temp1, temp2));
      }
    } else if (yaxe) {
      it++;
    }
    if (it->first.first >= index && !yaxe) {
      if (it->first.first == index) {
        int temp1 = it->first.first;
        int temp2 = it->first.second;
        it++;
        paper.erase(std::make_pair(temp1, temp2));
      } else {
        paper[std::make_pair(index*2 - it->first.first, it->first.second)]++;
        int temp1 = it->first.first;
        int temp2 = it->first.second;
        it++;
        paper.erase(std::make_pair(temp1, temp2));
      }
    } else if (!yaxe) {
      it++;
    }
  }
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::map<std::pair<int, int>, int> paper;
  std::vector<std::pair<char, int>> fold;
  while (istr >> info) {
    std::string num1 = "";
    std::string num2 = "";
    bool flip = false;
    if (info == "fold") {
      istr >> info;
      istr >> info;
      std::string foldnum = "";
      for (int j = 2; j < (int) info.size(); j++) {
        foldnum += info[j];
      }
      fold.push_back(std::make_pair(info[0], std::stoi(foldnum, nullptr)));
    } else {
      for (int i = 0; i < (signed) info.size(); i++) {
        if (info[i] == ',') {
          flip = true;
        } else if (!flip) {
          num1 += info[i];
        } else if (flip) {
          num2 += info[i];
        }
      }
      paper[std::make_pair(std::stoi(num1, nullptr), std::stoi(num2, nullptr))]++;
    }
  }
  for (int i = 0; i <(int) fold.size(); i++) {
    if (fold[i].first == 'y') {
      Fold(paper, fold[i].second, true);
    }
    if (fold[i].first == 'x') {
      Fold(paper, fold[i].second, false);
    }
  }
  std::map<std::pair<int, int>, int>::iterator print = paper.end();
  print--;
  int maxx = print->first.second; 
  int maxy = print->first.first;
  std::vector<std::vector<char>> printout;
  for (int i = 0; i < maxx + 1; i++) {
    std::vector<char> temp;
    for (int j = 0; j < maxy + 1; j++) {
      temp.push_back(' ');
    }
    printout.push_back(temp);
  }
  print = paper.end();
  while (print != paper.begin()) {
    print--;
    printout[print->first.second][print->first.first] = '#';
  }
  for (int i = 0; i < (int) printout.size(); i++) {
    for (int j = 0; j < (int) printout[i].size(); j++) {
      std::cout << printout[i][j];
    }
    std::cout << '\n';
  }
  return 0;
}
