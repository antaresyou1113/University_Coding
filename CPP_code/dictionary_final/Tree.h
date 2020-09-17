#ifndef _TREE_H_
#define _TREE_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Node.h"
using namespace std;

class Tree {
 private:
  Node *head;
  Node *tail;
  int position;

 public:
  Tree();
  ~Tree();
  void deleteNode(int position);
  Node *getNode(int position);
  int nodeNum(void);
  void setNode(int posi, Node &node);
  void Insert(Node &node);
};
#endif// _TREE_H_
