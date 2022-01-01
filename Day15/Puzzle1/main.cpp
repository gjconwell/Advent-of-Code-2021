#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>

//cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day15/Puzzle1
//g++ main.cpp -o main.exe -Wall
//./main.exe

typedef std::pair<int, std::pair<int, int>> PQElement;

int Retrace(std::map<std::pair<int, int>, std::pair<int, int>> &came_from, 
            std::vector<std::vector<int>> &map) {
  int risk = 0;
  std::map<std::pair<int, int>, std::pair<int, int>>::iterator it = came_from.find(std::make_pair(map.size() - 1,map.size() - 1));
  while (it->second.first != 0 || it->second.second != 0) {
    risk += map[it->first.first][it->first.second];
    it = came_from.find(std::make_pair(it->second.first,it->second.second));
  }
  risk += map[it->first.first][it->first.second];
  return risk;
}

void Neighbor(std::vector<std::vector<int>> &map, int x, int y, 
              std::pair<int, int> &current, std::priority_queue<PQElement, 
              std::vector<PQElement>, std::greater<PQElement>> &frontier, 
              std::map<std::pair<int, int>, std::pair<int, int>> &came_from,
              std::map<std::pair<int, int>, int> &cost_so_far) {
  bool bounds = false;
  if (x != 0 && current.first + x < (int) map.size() && current.first + x > 0) {
    bounds = true;
  } else if (y != 0 && current.second + y < (int) map.size() && current.second + y > 0) {
    bounds = true;
  }
  if (bounds) {
    std::map<std::pair<int, int>, int>::iterator it = cost_so_far.find(std::make_pair(current.first, current.second));
    int new_cost = it->second + map[current.first + x][current.second + y];
    it = cost_so_far.find(std::make_pair(current.first + x, current.second + y));
    if (it == cost_so_far.end()) {
      cost_so_far[std::make_pair(current.first + x,current.second + y)] = new_cost;
      frontier.push(std::make_pair(new_cost, 
                    std::make_pair(current.first + x, current.second + y)));
      came_from[std::make_pair(current.first + x, current.second + y)] = std::make_pair(current.first,current.second);
    }
  }
}

int Astar(std::vector<std::vector<int>> &map) { 
  std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> frontier;
  std::map<std::pair<int, int>, std::pair<int, int>> came_from;
  std::map<std::pair<int, int>, int> cost_so_far;
  frontier.push(std::make_pair(map[0][0], std::make_pair(0,0)));
  cost_so_far[std::make_pair(0,0)] = map[0][0];
  while (!frontier.empty()) {
    std::pair<int, int> current = frontier.top().second;
    frontier.pop();
    if (current.first == (int) map.size() - 1 && current.second == (int) map.size() - 1) {
      break;
    }
    Neighbor(map, 1, 0, current, frontier, came_from, cost_so_far);
    Neighbor(map, 0, 1, current, frontier, came_from, cost_so_far);
    Neighbor(map, -1, 0, current, frontier, came_from, cost_so_far);
    Neighbor(map, 0, -1, current, frontier, came_from, cost_so_far);
  }
  return Retrace(came_from, map);
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::vector<std::vector<int>> map;
  std::string info;
  while (istr >> info) {
    std::vector<int> temp;
    for (int i = 0; i < (signed) info.size(); i++) {
      temp.push_back(info[i] - '0');
    }
    map.push_back(temp);
  }
  std::cout << Astar(map) << '\n';
  return 0;
}
