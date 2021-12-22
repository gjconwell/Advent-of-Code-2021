#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <set>

//cd /mnt/c/Users/gjcon/github/Advent-of-Code-2021/Day22/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

void Reboot(std::set<std::pair<int, std::pair<int, int>>> &cuboid, bool toggle,
            std::string sx1, std::string sy1, std::string sx2,
            std::string sy2, std::string sz1, std::string sz2) {
  int x1 = std::stoi(sx1, nullptr);
  int x2 = std::stoi(sx2, nullptr);
  int y1 = std::stoi(sy1, nullptr);
  int y2 = std::stoi(sy2, nullptr);
  int z1 = std::stoi(sz1, nullptr);
  int z2 = std::stoi(sz2, nullptr);
  if (x1 < -50 || x2 > 50 || y1 < -50 || y2 > 50 || z1 < -50 || z2 > 50) {
    return;
  }
  for (int i = x1; i <= x2; i++) {
    for (int j = y1; j <= y2; j++) {
      for (int k = z1; k <= z2; k++) {
        std::pair<int,int> yz (j,k);
        std::pair<int, std::pair<int,int>> xyz (i, yz);
        if (toggle) {
          cuboid.insert(xyz);
        } else {
          cuboid.erase(xyz);
        }
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::set<std::pair<int, std::pair<int, int>>> cuboid;
  bool toggle = false;
  while (istr >> info) {
    if (info == "on") {
      toggle = true;
    } else if (info == "off") {
      toggle = false;
    } else {
      std::string sx1, sy1, sx2, sy2, sz1, sz2;
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
          while (info[j] != ',') {
            sy2 += info[j];
            j++;
          }
        }
        if (info[i] == 'z') {
          int j = i + 2;
          while (info[j] != '.') {
            sz1 += info[j];
            j++;
          }
          j += 2;
          while (j < (int) info.size()) {
            sz2 += info[j];
            j++;
          }
        }
        i++;
      }
      Reboot(cuboid, toggle, sx1, sy1, sx2, sy2, sz1, sz2);
    }
  }
  std::cout << cuboid.size() << '\n';
  return 0;
}
