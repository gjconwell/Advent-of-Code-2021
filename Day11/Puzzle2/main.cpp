#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day11/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe
void FlashControl(std::vector<std::vector<int>> &octopi, 
                  std::vector<std::pair<int, int>> &flashed, int i, int j);

void Flash(std::vector<std::vector<int>> &octopi, 
           std::vector<std::pair<int, int>> &flashed, int i, int j, int y, int x) {
  if (i + y < (int) octopi.size() && i + y >= 0 && j + x < (int) octopi[i].size() && j + x >= 0) {
    octopi[i + y][j + x]++;
    if (octopi[i + y][j + x] >= 9) {
      octopi[i + y][j + x] = 0;
      flashed.push_back(std::make_pair(i + y, j + x));
      FlashControl(octopi, flashed, i + y, j + x);
    }
  }
}

void FlashControl(std::vector<std::vector<int>> &octopi, 
                  std::vector<std::pair<int, int>> &flashed, int i, int j) {
  Flash(octopi, flashed, i, j, 1, -1); // bot left
  Flash(octopi, flashed, i, j, 1, 0); // bot
  Flash(octopi, flashed, i, j, 1, 1); // bot right
  Flash(octopi, flashed, i, j, 0, 1); // right
  Flash(octopi, flashed, i, j, -1, 1); // top right
  Flash(octopi, flashed, i, j, -1, 0); //top
  Flash(octopi, flashed, i, j, -1, -1); //top left
  Flash(octopi, flashed, i, j, 0, -1); // left
}

int Step(std::vector<std::vector<int>> &octopi) {
  int count = 0;
  std::vector<std::pair<int, int>> flashed;
  for (int i = 0; i < (signed) octopi.size(); i++) {
    for (int j = 0; j < (signed) octopi[i].size(); j++) {
      if (octopi[i][j] >= 9) {
        count++;
        flashed.push_back(std::make_pair(i, j));
        octopi[i][j] = 0;
        FlashControl(octopi, flashed, i, j);
      }
    }
  }
  for (int i = 0; i < (signed) octopi.size(); i++) {
    for (int j = 0; j < (signed) octopi[i].size(); j++) {
      octopi[i][j]++;
    }
  }
  for (int i = 0; i < (int) flashed.size(); i++) {
    octopi[flashed[i].first][flashed[i].second] = 0;
  }
  return flashed.size();
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::vector<std::vector<int>> octopi;
  std::string info;
  while (istr >> info) {
    std::vector<int> temp;
    for (int i = 0; i < (signed) info.size(); i++) {
      temp.push_back(info[i] - '0');
    }
    octopi.push_back(temp);
  }
  int runs = 0;
  bool running = true;
  while (running) {
    if (Step(octopi) == 100) {
      running = false;
    }
    runs++;
  }
  std::cout << runs << '\n';
  return 0;
}
