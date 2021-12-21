#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day17/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

bool Probe(int x1, int x2, int y1, int y2, int xvel, int yvel) {
  int x = xvel;
  int y = yvel;
  bool trenched = false;
  while (y >= y1 && x <= x2) {
    if (y <= y2 && y >= y1 && x <= x2 && x >= x1) {
      trenched = true;
    }
    if (xvel > 0) {
      xvel--;
    } else if (xvel < 0) {
      xvel++;
    }
    yvel--;
    x += xvel;
    y += yvel;
  }
  return trenched;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::string sx1, sy1, sx2, sy2;
  while (istr >> info) {
    int i = 0;
    while (i < (int) info.size()) {
      if (info[i] == 'x') {
        int j = i + 2;
        while (info[j] != '.') {
          sx1 += info[j];
          j++;
        }
        j += 2;
        while (info[j] != ',') {
          sx2 += info[j];
          j++;
        }
      }
      if (info[i] == 'y') {
        int j = i + 2;
        while (info[j] != '.') {
          sy1 += info[j];
          j++;
        }
        j += 2;
        while (j < (int) info.size()) {
          sy2 += info[j];
          j++;
        }
      }
      i++;
    }
  }
  int x1 = std::stoi(sx1, nullptr);
  int x2 = std::stoi(sx2, nullptr);
  int y1 = std::stoi(sy1, nullptr);
  int y2 = std::stoi(sy2, nullptr);
  int count = 0;
  for (int i = -500; i < 500; i++) {
    for (int j = -500; j < 500; j++) {
      if (Probe(x1, x2, y1, y2, i, j)) {
        count++;
      }
    }
  }
  std::cout << count << '\n';
  return 0;
}
