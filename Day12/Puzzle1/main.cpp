#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <set>
#include <cctype>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day12/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

int Pathing(std::map<std::string, std::list<std::string>> &nodes,
            std::map<std::string, std::list<std::string>>::iterator &it,
            std::set<std::string> mem, int &count) {
  if (it->first == "end") {
    count++;
    return count;
  }
  mem.insert(it->first);
  std::list<std::string>::iterator it2 = it->second.begin();
  while (it2 != it->second.end()) {
    std::set<std::string>::iterator mit = mem.find(*it2);
    if (mit != mem.end()) {
      std::string temp = *mit;
      if (isupper(temp[0])) {
        std::map<std::string, std::list<std::string>>::iterator it3 = nodes.find(*it2);
        Pathing(nodes, it3, mem, count);
      } else {
      }
    } else {
      std::map<std::string, std::list<std::string>>::iterator it3 = nodes.find(*it2);
      Pathing(nodes, it3, mem, count);
    }
    it2++;
  }
  return count;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::map<std::string, std::list<std::string>> nodes;
  while (istr >> info) {
    std::string nodename1 = "";
    std::string nodename2 = "";
    bool flip = false;
    for (int i = 0; i < (signed) info.size(); i++) {
      if (info[i] == '-') {
        flip = true;
      } else if (!flip) {
        nodename1 += info[i];
      } else if (flip) {
        nodename2 += info[i];
      }
    }
    nodes[nodename1].push_back(nodename2);
    nodes[nodename2].push_back(nodename1);
  }
  int count = 0;
  std::set<std::string> mem;
  std::map<std::string, std::list<std::string>>::iterator it = nodes.find("start");
  std::cout << Pathing(nodes, it, mem, count) << '\n';
  return 0;
}
