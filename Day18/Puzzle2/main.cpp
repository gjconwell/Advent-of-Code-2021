#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <cmath>

// cd /mnt/c/Users/gjcon/github/Advent-of-Code-2021/Day18/Puzzle2
// g++ main.cpp -o main.exe -Wall
// ./main.exe

class Node {
public:
  Node(int v) : data(v), left(NULL), right(NULL), parent(NULL) {}
  float data;
  Node* left;
  Node* right;
  Node* parent;
};

void Insert(Node* &root, bool left, std::vector<bool> path, int const idx,
            std::string const &info, int nextidx) {
  for (int i = 0; i < (int) path.size(); i++) {
    if (path[i]) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  if (left) {
    root->left = new Node(info[idx + nextidx] - '0');
    root->left->parent = root;
  } else {
    root->right = new Node(info[idx + nextidx] - '0');
    root->right->parent = root;
  }
  while (root->parent != NULL) {
    root = root->parent;
  }
}

void PairVal(Node* &root, std::vector<bool> lpath) {
  for (int i = 0; i < (int) lpath.size() - 1; i++) {
    if (lpath[i]) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  if (lpath[lpath.size() - 1]) {
    root->left = new Node(-1);
    root->left->parent = root;
  } else {
    root->right = new Node(-1);
    root->right->parent = root;
  }
  while (root->parent) {
    root = root->parent;
  }
}

void Parse(Node* &root, bool left, std::string const &info, int const idx,
           int nextidx, int ends, std::vector<bool> lpath) {
  if (isdigit(info[idx + nextidx])) {
    if (left) {
      Insert(root, true, lpath, idx, info, nextidx);
      Parse(root, false, info, idx, nextidx + 1, ends, lpath);
    } else {
      Insert(root, false, lpath, idx, info, nextidx);
      Parse(root, true, info, idx,   nextidx + 1, ends, lpath);
    }
  } else if (info[idx + nextidx] == ',') {
    Parse(root, false, info, idx, nextidx + 1, ends, lpath);
  } else if (info[idx + nextidx] == '[') {
    if (left) {
      lpath.push_back(true);
      PairVal(root, lpath);
      Parse(root, true, info, idx, nextidx + 1, ends + 1, lpath);
    } else {
      lpath.push_back(false);
      PairVal(root, lpath);
      Parse(root, true, info, idx, nextidx + 1, ends + 1, lpath);
    }
  } else if (info[idx + nextidx] == ']') {
    ends--;
    lpath.erase(lpath.end());
    if (ends != 0) {
      Parse(root, left, info, idx, nextidx + 1, ends, lpath);
    }
  }
}

void DetectExplode(Node* p, int level, bool &splode, std::vector<bool> temp,
                   std::vector<bool> &xpath) {
  if (level > 4 ) {
    splode = true;
    xpath = temp;
  }
  if (p->left && !splode) {
    temp.push_back(true);
    DetectExplode(p->left, level + 1, splode, temp, xpath);
  }
  temp.erase(temp.end());
  if (p->right && !splode) {
    temp.push_back(false);
    DetectExplode(p->right, level + 1, splode, temp, xpath);
  }
}

void Explode(Node* &root, std::vector<bool> const &xpath) {
  for (int i = 0; i < (int) xpath.size() - 1; i++) {
    if (xpath[i]) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  Node* tmp = root;
  Node* tmp2 = root;
  while (root->parent) {
    root = root->parent;
    if (root->right != tmp) {
      root = root->right;
      while (root->left) {
        root = root->left;
      }
      root->data += tmp2->right->data;
      break;
    }
    tmp = tmp->parent;
  }
  root = tmp2;
  while (root->parent) {
    root = root->parent;
    if (root->left != tmp) {
      root = root->left;
      while (root->right) {
        root = root->right;
      }
      root->data += tmp2->left->data;
      break;
    }
    tmp = tmp->parent;
  }
  root = tmp2;
  root->data = 0;
  root->right = NULL;
  root->left = NULL;
  while (root->parent) {
    root = root->parent;
  }
}

void DetectSplit(Node* p, bool &splt, std::vector<bool> temp, std::vector<bool> &spath) {
  if (p->data > 9) {
    splt = true;
    spath = temp;
  }
  if (p->left && !splt) {
    temp.push_back(true);
    DetectSplit(p->left, splt, temp, spath);
  }
  temp.erase(temp.end());
  if (p->right && !splt) {
    temp.push_back(false);
    DetectSplit(p->right, splt, temp, spath);
  }
}

void Split(Node* &root, std::vector<bool> const &spath) {
  for (int i = 0; i < (int) spath.size(); i++) {
    if (spath[i]) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  int lnum = floor(root->data/2);
  int rnum = ceil(root->data/2);
  root->left = new Node(lnum);
  root->right = new Node(rnum);
  root->left->parent = root;
  root->right->parent = root;
  root->data = -1;
  while (root->parent) {
    root = root->parent;
  }
}

void Magnitude(Node* p, int value, int &total) {
  if (p->left) {
    if (!p->left->right && !p->left->left) {
      total += p->left->data * value * 3;
    } else {
      Magnitude(p->left, value * 3, total);
    }
  }
  if (p->right) {
    if (!p->right->right && !p->right->left) {
      total += p->right->data * value * 2;
    } else {
      Magnitude(p->right, value * 2, total);
    }
  }
}

int main(int argc, char const *argv[]) {
  std::vector<Node*> lines;
  std::ifstream istr("input.txt");
  std::string info;
  int max = 0;
  while (istr >> info) {
    std::ifstream istr("input.txt");
    std::string info2;
    while (istr >> info2) {
      if (info != info2) {
        Node* tree1 = new Node(-1);
        std::vector<bool> temp;
        Parse(tree1, true, info, 0, 1, 1, temp);
        Node* tree2 = new Node(-1);
        std::vector<bool> temp1;
        Parse(tree2, true, info2, 0, 1, 1, temp1);
        Node* tmptree = new Node(-1);
        tmptree->left = tree1;
        tree1->parent = tmptree;
        tmptree->right = tree2;
        tree2->parent = tmptree;
        std::vector<bool> temp2;
        bool edit = true;
        while (edit) {
          std::vector<bool> xpath;
          bool splode = false;
          DetectExplode(tmptree, 0, splode, temp2, xpath);
          std::vector<bool> spath;
          bool splt = false;
          DetectSplit(tmptree, splt, temp2, spath);
          if (splode) {
            Explode(tmptree, xpath);
          } else if (splt) {
            Split(tmptree, spath);
          }
          if (!splt && !splode) {
            edit = false;
          }
        }
        int mag = 0;
        Magnitude(tmptree, 1, mag);
        if (mag > max) {
          max = mag;
        }
      }
    }
  }
  std::cout << max << '\n';
  return 0;
}
