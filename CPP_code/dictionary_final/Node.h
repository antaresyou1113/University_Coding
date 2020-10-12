#ifndef _NODE_H_
#define _NODE_H_
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
using namespace std;

class Node {
 private:
  int nodesize;  // the size of the node
  int watch1;
  int watch2;  // for the insertion method
  int key_num;
  int level;
  int level_num;

 public:
  void setLevelnum(int level_num);
  int getLevelnum(void);
  void setLevel(int level);
  int getLevel(void);
  string smallestKey(void);
  void emptyNode(void);
  int getNodesize(void);
  void setNodesize(int nodesize);
  char *pointerNode;
  void insertLeafnum(int leaf_num);
  int getLeafnum(void);
  void insertKeynum(int keys_num);
  int getKeynum(void);
  int insertKeys(string key);
  string getKey(int number);
  int getVector(int number);
  Node *next;  // pointer to the next node
  Node(const Node &node_tmp);
  Node(int nodesize = 32, Node *next = NULL);
  ~Node();
};
#endif  //_NODE_H_
