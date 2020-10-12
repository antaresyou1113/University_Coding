#ifndef _DECODINGINDEXNODE_H_
#define _DECODINGINDEXNODE_H_

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

class decodingindexNode {
 private:
  int level;
  int level_num;
  int indexNodesize;

 public:
  decodingindexNode(int indexNodesize = 32);
  decodingindexNode(const decodingindexNode &node_tmp);
  ~decodingindexNode();
  // void insertNode(Node &node);
  void setLevelnum(int level_num);
  void setLevel(int level);
  void setIndexnodesize(int size);
  void setNodesize(int nodesize);
  void setOffset(int offset);
  void insertKey(int key);
  char *indexpointer;
  int getLevelnum(void);
  int getLevel(void);
  int getOffset(void);
  int getKeynum(void);
  int getIndexnodesize(void);
  int getKey(int number);
  int nodeSize(void);
  int smallestKey(void);
};
#endif  //_DECODINGINDEXNODE_H_
