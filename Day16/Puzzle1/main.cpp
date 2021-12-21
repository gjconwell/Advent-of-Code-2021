#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

//cd /mnt/c/Users/gjcon/github/Advent-of-Code-2021/Day16/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

std::string HexToBi(char c) {
  switch (c) {
    case '0': return "0000";
    case '1': return "0001";
    case '2': return "0010";
    case '3': return "0011";
    case '4': return "0100";
    case '5': return "0101";
    case '6': return "0110";
    case '7': return "0111";
    case '8': return "1000";
    case '9': return "1001";
    case 'A': return "1010";
    case 'B': return "1011";
    case 'C': return "1100";
    case 'D': return "1101";
    case 'E': return "1110";
    default: return "1111";
  }
}

int Three(std::string &bits, int &index) {
  std::string t = "";
  for (int i = index; i < index + 3; i++) {
    t += bits[i];
  }
  index += 3;
  return std::stol(t, nullptr, 2);
}

int Four(std::string &bits, int &index) {
  bool gate = true;
  std::string fullnum = "";
  while (gate) {
    std::string num = "";
    for (int i = index + 1; i < index + 5; i++) {
      num += bits[i];
    }
    if (bits[index] == '0') {
      gate = false;
    }
    index += 5;
    fullnum += num;
  }
  return std::stol(fullnum, nullptr, 2);
}

int ID(std::string &bits, int &index, bool &id) {
  std::string num = "";
  if (bits[index] == '0') {
    index++;
    for (int i = index; i < index + 15; i++) {
      num += bits[i];
    }
    index += 15;
    id = false;
    return std::stol(num, nullptr, 2);
  } else {
    index++;
    for (int i = index; i < index + 11; i++) {
      num += bits[i];
    }
    index += 11;
    id = true;
    return std::stol(num, nullptr, 2);
  }
}

int Recurse(std::string &bits, int &index, int &count) {
  count += Three(bits, index);
  int t = Three(bits, index);
  bool id;
  if (t == 4) {
    Four(bits, index);
  } else {
    int idval = ID(bits, index, id);
    if (id) {
      for (int i = 0; i < idval; i++) {
        Recurse(bits, index, count);
      }
    } else {
      int lengthsub = index + idval;
      while (index < lengthsub) {
        Recurse(bits, index, count);
      }
    }
  }
  return count;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::string bits = "";
  while (istr >> info) {
    for (int i = 0; i < (int) info.size(); i++) {
      bits += HexToBi(info[i]);
    }
  }
  int index = 0;
  int count = 0;
  std::cout << Recurse(bits, index, count) << '\n';
  return 0;
}
