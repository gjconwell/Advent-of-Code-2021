#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day10/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

int Corrupt(std::vector<char> &line) {
  for (int i = 0; i < (int) line.size() - 1; i++) {
    if (line[i] == '{' && line[i + 1] == '}') {
      line.erase(line.begin()+i, line.begin()+(i+2));
      i = -1;
    } else if (line[i] == '<' && line[i + 1] == '>') {
      line.erase(line.begin()+i, line.begin()+(i+2));
      i = -1;
    } else if (line[i] == '(' && line[i + 1] == ')') {
      line.erase(line.begin()+i, line.begin()+(i+2));
      i = -1;
    } else if (line[i] == '[' && line[i + 1] == ']') {
      line.erase(line.begin()+i, line.begin()+(i+2));
      i = -1;
    } else if ((line[i] == '[' || line[i] == '(' || line[i] == '<' || line[i] == '{') &&
               (line[i + 1] == '}' || line[i + 1] == '>' || line[i + 1] == ')' || line[i + 1] == ']')) {
      if (line[i + 1] == ')') {
        return 3;
      } else if (line[i + 1] == ']') {
        return 57;
      } else if (line[i + 1] == '}') {
        return 1197;
      } else if (line[i + 1] == '>') {
        return 25137;
      }
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  int count = 0;
  while (istr >> info) {
    std::vector<char> line;
    for (int i = 0; i < (signed) info.size(); i++) {
      line.push_back(info[i]);
    }
    count += Corrupt(line);
  }
  std::cout << count << '\n';
  return 0;
}
