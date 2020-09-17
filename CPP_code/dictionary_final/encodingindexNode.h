#ifndef _ENCODINGINDEXNODE_H_
#define _ENCODINGINDEXNODE_H_

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

class encodingindexNode {
 private:
  int level;
  int level_num;      // the number of nodes in this level
  int indexNodesize;  // the size of the node
 public:
  encodingindexNode(int indexNodesize = 32);
  encodingindexNode(const encodingindexNode &node_tmp);
  ~encodingindexNode();
  void insertNode(Node &node);
  char *indexpointer;
  void insertLevelnum(int level_num);
  void setLevelnum(int num);
  void setLevel(int level);
  void setIndexnodesize(int size);
  int getLevelnum(void);
  int getLevel(void);
  int getOffset(void);
  int getKeynum(void);
  int getIndexnodesize(void);
  string getKey(int number);
  int nodeSize(void);
  int getVector(int number);
};

class encodingIndex {
 private:
  int nodeNum;  // the number of index node in this index
 public:
  void insertIndexnode(int position, encodingindexNode &node);
  int getNodenum(void);
  encodingindexNode *index;
  encodingIndex(int nodeNum);
  ~encodingIndex();
};

#endif  //_ENCODINGINDEXNODE_H_
