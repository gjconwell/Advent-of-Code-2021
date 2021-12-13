#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day10/Puzzle2
//g++ main.cpp -o main.exe -Wall
//./main.exe

bool Corrupt(std::vector<char> &line) {
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
      return false;
    }
  }
  return true;
}

long int Score(std::vector<char> &line) {
  long int count = 0;
  for (int i = line.size() - 1; i > -1; i--) {
    count *= 5;
    if (line[i] == '{') {
      count += 3;
    } else if (line[i] == '[') {
      count += 2;
    } else if (line[i] == '<') {
      count += 4;
    } else if (line[i] == '(') {
      count += 1;
    }
  }
  return count;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::vector<long int> scores;
  while (istr >> info) {
    std::vector<char> line;
    for (int i = 0; i < (signed) info.size(); i++) {
      line.push_back(info[i]);
    }
    if (Corrupt(line)) {
      scores.push_back(Score(line));
    }
  }
  std::sort(scores.begin(), scores.end());
  std::cout << scores[scores.size()/2] << '\n';
  return 0;
}
