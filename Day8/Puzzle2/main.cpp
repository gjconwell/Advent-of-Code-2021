#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <cmath>

// cd /mnt/c/Users/conweg/Documents/Coding/Advent_of_Code_2021/Day8/Puzzle2
// g++ main.cpp -o main.exe -Wall
// ./main.exe

class Segments{
public:
  bool uR = false;
  bool uL = false;
  bool dR = false;
  bool dL = false;
  bool m = false;
  bool d = false;
  bool u = false;
};

void Assign(std::map<int, std::vector<std::string>> &input,
            std::map<char, std::string> &SegmentData) {
  std::vector<std::vector<char>> PossibleVec;
  std::vector<char> temp;
  for (int i = 0; i < 7; i++) {
    PossibleVec.push_back(temp);
  }
  std::map<int, std::vector<std::string>>::iterator pit = input.begin();
  int index = 0;
  while (pit != input.end()) {
    if (index == 0) {
      PossibleVec[0].push_back(pit->second[0][0]);
      PossibleVec[0].push_back(pit->second[0][1]);
      PossibleVec[2].push_back(pit->second[0][0]);
      PossibleVec[2].push_back(pit->second[0][1]);
    } else if (index == 1) {
      for (int j = 0; j < (signed) pit->second[0].size(); j++) {
        if (PossibleVec[0][0] != pit->second[0][j] && PossibleVec[0][1] != pit->second[0][j]) {
          SegmentData[pit->second[0][j]] = "u";
          PossibleVec[4].push_back(pit->second[0][j]);
        }
      }
    } else if (index == 2) {
      for (int j = 0; j < (signed) pit->second[0].size(); j++) {
        if (PossibleVec[0][0] != pit->second[0][j] && PossibleVec[0][1] != pit->second[0][j]) {
          PossibleVec[1].push_back(pit->second[0][j]);
          PossibleVec[5].push_back(pit->second[0][j]);
        }
      }
    } else if (index == 5) {
      for (int j = 0; j < (signed) pit->second[0].size(); j++) {
        if (PossibleVec[0][0] != pit->second[0][j] && PossibleVec[0][1] != pit->second[0][j] &&
            PossibleVec[1][0] != pit->second[0][j] && PossibleVec[1][1] != pit->second[0][j] &&
            PossibleVec[4][0] != pit->second[0][j]) {
          PossibleVec[3].push_back(pit->second[0][j]);
          PossibleVec[6].push_back(pit->second[0][j]);
        }
      }
      pit--;
      for (int k = 0; k < (signed) pit->second.size(); k++) {
        std::vector<char> temp;
        for (int j = 0; j < (signed) pit->second[k].size(); j++) {
          if (PossibleVec[0][0] == pit->second[k][j] || PossibleVec[0][1] == pit->second[k][j]) {
            temp.push_back(pit->second[k][j]);
          }
        }
        if ((signed) temp.size() == 2) {
          temp.clear();
          for (int j = 0; j < (signed) pit->second[k].size(); j++) {
            if (PossibleVec[1][0] == pit->second[k][j] || PossibleVec[1][1] == pit->second[k][j]) {
              temp.push_back(pit->second[k][j]);
            }
          }
          if ((signed) temp.size() == 2) {
            temp.clear();
            for (int j = 0; j < (signed) pit->second[k].size(); j++) {
              if (PossibleVec[3][0] == pit->second[k][j] || PossibleVec[3][1] == pit->second[k][j]) {
                temp.push_back(pit->second[k][j]);
              }
            }
            SegmentData[temp[0]] = "d";
            for (int i = 0; i < (signed) PossibleVec[1].size(); i++) {
              if (temp[0] != PossibleVec[3][i]) {
                SegmentData[PossibleVec[3][i]] = "dL";
              }
            }
          } else {
            SegmentData[temp[0]] = "uL";
            for (int i = 0; i < (signed) PossibleVec[1].size(); i++) {
              if (temp[0] != PossibleVec[1][i]) {
                SegmentData[PossibleVec[1][i]] = "m";
              }
            }
          }
        } else {
          SegmentData[temp[0]] = "dR";
          for (int i = 0; i < (signed) PossibleVec[0].size(); i++) {
            if (temp[0] != PossibleVec[0][i]) {
              SegmentData[PossibleVec[0][i]] = "uR";
            }
          }
        }
      }
      pit++;
    }
    index++;
    pit++;
  }
}


std::string Decode(std::string info, std::map<char, std::string> &SegmentData) {
  Segments sg;
  for (int i = 0; i < (signed) info.length(); i++) {
    std::map<char, std::string>::iterator it = SegmentData.find(info[i]);
    if (it->second == "uR") {
      sg.uR = true;
    } else if (it->second == "uL") {
      sg.uL = true;
    } else if (it->second == "dR") {
      sg.dR = true;
    } else if (it->second == "dL") {
      sg.dL = true;
    } else if (it->second == "m") {
      sg.m = true;
    } else if (it->second == "d") {
      sg.d = true;
    } else if (it->second == "u") {
      sg.u = true;
    } else {
      std::cout << "missed  " << it->second << '\n';
    }
  }
  if (sg.u && sg.uL && sg.dR && sg.d && sg.dL && sg.uR && !sg.m) {
    return "0"; 
  } else if (!sg.u && !sg.uL && !sg.m && sg.dR && !sg.d && !sg.dL && sg.uR) {
    return "1";
  } else if (sg.u && !sg.uL && sg.m && !sg.dR && sg.d && sg.dL && sg.uR) {
    return "2"; 
  } else if (sg.u && !sg.uL && sg.m && sg.dR && sg.d && !sg.dL && sg.uR) {
    return "3"; 
  } else if (!sg.u && sg.uL && sg.m && sg.dR && !sg.d && !sg.dL && sg.uR) {
    return "4";
  } else if (sg.u && sg.uL && sg.m && sg.dR && sg.d && !sg.dL && !sg.uR) {
    return "5"; 
  } else if (sg.u && sg.uL && sg.m && sg.dR && sg.d && sg.dL && !sg.uR) {
    return "6"; 
  } else if (sg.u && !sg.uL && !sg.m && sg.dR && !sg.d && !sg.dL && sg.uR) {
    return "7";
  } else if (sg.u && sg.uL && sg.m && sg.dR && sg.d && sg.dL && sg.uR) {
    return "8";
  } else {
    return "9";
  }
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  int count = 0;
  while (istr >> info){
    std::map<int, std::vector<std::string>> input;
    std::map<char, std::string> SegmentData;
    while (info != "|") {
      input[info.size()].push_back(info);
      istr >> info;
    }
    std::string num = "";
    Assign(input, SegmentData);
    for (size_t i = 0; i < 4; i++) {
      istr >> info;
      num += Decode(info, SegmentData);
    }
    count += std::stoi(num, nullptr, 10);
  }
  std::cout << count << '\n';
  return 0;
}
