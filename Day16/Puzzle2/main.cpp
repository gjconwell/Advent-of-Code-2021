#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <list>

//cd /mnt/c/Users/gjcon/github/Advent-of-Code-2021/Day16/Puzzle2
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

long int Three(std::string &bits, long int &index) {
  std::string t = "";
  for (long int i = index; i < index + 3; i++) {
    t += bits[i];
  }
  index += 3;
  return std::stol(t, nullptr, 2);
}

long int Four(std::string &bits, long int &index) {
  bool gate = true;
  std::string fullnum = "";
  while (gate) {
    std::string num = "";
    for (long int i = index + 1; i < index + 5; i++) {
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

long int ID(std::string &bits, long int &index, bool &id) {
  std::string num = "";
  if (bits[index] == '0') {
    index++;
    for (long int i = index; i < index + 15; i++) {
      num += bits[i];
    }
    index += 15;
    id = false;
    return std::stol(num, nullptr, 2);
  } else {
    index++;
    for (long int i = index; i < index + 11; i++) {
      num += bits[i];
    }
    index += 11;
    id = true;
    return std::stol(num, nullptr, 2);
  }
}

long int Recurse(std::string &bits, long int &index, long int &val) {
  Three(bits, index);
  long int t = Three(bits, index);
  bool id;
  if (t == 0) {
    long int idval = ID(bits, index, id);
    long int sum = 0;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        sum += Recurse(bits, index, val);
      }
      val = sum;
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        sum += Recurse(bits, index, val);
      }
      val = sum;
    }
  } else if (t == 1) { //sum
    long int idval = ID(bits, index, id);
    long int product = 1;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        product *= Recurse(bits, index, val);
      }
      val = product;
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        product *= Recurse(bits, index, val);
      }
      val = product;
    }
  } else if (t == 2) { //product
    long int idval = ID(bits, index, id);
    std::vector<long int> min;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        min.push_back(Recurse(bits, index, val));
      }
      long int minimum = min[0];
      for (long int i = 0; i < (long int) min.size(); i++) {
        if (min[i] < minimum) {
          minimum = min[i];
        }
      }
      val = minimum;
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        min.push_back(Recurse(bits, index, val));
      }
      long int minimum = min[0];
      for (long int i = 0; i < (long int) min.size(); i++) {
        if (min[i] < minimum) {
          minimum = min[i];
        }
      }
      val = minimum;
    }
  } else if (t == 3) { //maximum
    long int idval = ID(bits, index, id);
    std::vector<long int> max;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        max.push_back(Recurse(bits, index, val));
      }
      long int maximum = max[0];
      for (long int i = 0; i < (long int) max.size(); i++) {
        if (max[i] > maximum) {
          maximum = max[i];
        }
      }
      val = maximum;
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        max.push_back(Recurse(bits, index, val));
      }
      long int maximum = max[0];
      for (long int i = 0; i < (long int) max.size(); i++) {
        if (max[i] > maximum) {
          maximum = max[i];
        }
      }
      val = maximum;
    }
  } else if (t == 4) {
    val = Four(bits, index);
  } else if (t == 5) { //greater than
    long int idval = ID(bits, index, id);
    std::vector<long int> greater;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        greater.push_back(Recurse(bits, index, val));
      }
      if (greater[0] > greater[1]) {
        val = 1;
      } else {
        val = 0;
      }
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        greater.push_back(Recurse(bits, index, val));
      }
      if (greater[0] > greater[1]) {
        val = 1;
      } else {
        val = 0;
      }
    }
  } else if (t == 6) { //less than
    long int idval = ID(bits, index, id);
    std::vector<long int> less;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        less.push_back(Recurse(bits, index, val));
      }
      if (less[0] < less[1]) {
        val = 1;
      } else {
        val = 0;
      }
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        less.push_back(Recurse(bits, index, val));
      }
      if (less[0] < less[1]) {
        val = 1;
      } else {
        val = 0;
      }
    }
  } else if (t == 7) { //equal to
    long int idval = ID(bits, index, id);
    std::vector<long int> equalto;
    if (id) {
      for (long int i = 0; i < idval; i++) {
        equalto.push_back(Recurse(bits, index, val));
      }
      if (equalto[0] == equalto[1]) {
        val = 1;
      } else {
        val = 0;
      }
    } else {
      long int lengthsub = index + idval;
      while (index < lengthsub) {
        equalto.push_back(Recurse(bits, index, val));
      }
      if (equalto[0] == equalto[1]) {
        val = 1;
      } else {
        val = 0;
      }
    }
  }
  return val;
}

int main(int argc, char const *argv[]) {
  std::ifstream istr("input.txt");
  std::string info;
  std::string bits = "";
  while (istr >> info) {
    for (long int i = 0; i < (long int) info.size(); i++) {
      bits += HexToBi(info[i]);
    }
  }
  long int index = 0;
  long int val = 0;
  std::cout << Recurse(bits, index, val) << '\n';
  return 0;
}
