#include "decodingindexNode.h"

decodingindexNode::decodingindexNode(int indexNodesize) {
  this->level_num = 0;
  this->level = 0;
  this->indexNodesize = indexNodesize;
  this->indexpointer = NULL;
  this->indexpointer = new char[this->indexNodesize];
  //cout << "Create a decoding index node!" << endl;
}

decodingindexNode::decodingindexNode(const decodingindexNode &node_tmp) {
  this->level_num = node_tmp.level_num;
  this->level = node_tmp.level;
  this->indexNodesize = node_tmp.indexNodesize;
  this->indexpointer = new char[this->indexNodesize];
  for (int i = 0; i < this->indexNodesize; i++) {
    this->indexpointer[i] = node_tmp.indexpointer[i];
  }
  //cout << "Copy the decoding index node!" << endl;
}

decodingindexNode::~decodingindexNode() {
  delete[] indexpointer;
  //cout << "Delete the decoding index node!" << endl;
}

int decodingindexNode::getIndexnodesize() { return this->indexNodesize; }

void decodingindexNode::setLevelnum(int level_num) {
  this->level_num = level_num;
}

void decodingindexNode::setLevel(int level) { this->level = level; }

void decodingindexNode::setIndexnodesize(int size) {
  this->indexNodesize = size;
}

void decodingindexNode::setNodesize(int nodesize) {
  char *p = (char *)&nodesize;
  this->indexpointer[4] = *((char *)p + 0);
  this->indexpointer[5] = *((char *)p + 1);
  this->indexpointer[6] = *((char *)p + 2);
  this->indexpointer[7] = *((char *)p + 3);
}

void decodingindexNode::setOffset(int offset) {
  char *p = (char *)&offset;
  this->indexpointer[0] = *((char *)p + 0);
  this->indexpointer[1] = *((char *)p + 1);
  this->indexpointer[2] = *((char *)p + 2);
  this->indexpointer[3] = *((char *)p + 3);
}

void decodingindexNode::insertKey(int key) {
  int key_num = this->getKeynum();
  if (key_num < (this->indexNodesize - 8) / 4) {
    int start = 8 + 4 * key_num;
    char *p = (char *)&key;
    this->indexpointer[start] = *((char *)p + 0);
    this->indexpointer[start + 1] = *((char *)p + 1);
    this->indexpointer[start + 2] = *((char *)p + 2);
    this->indexpointer[start + 3] = *((char *)p + 3);
    key_num++;
    this->setNodesize(key_num);
  }
}
int decodingindexNode::smallestKey() {
  int result = -1;
  result = this->getKey(1);
  return result;
}

int decodingindexNode::getLevelnum() { return this->level_num; }

int decodingindexNode::getLevel() { return this->level; }

int decodingindexNode::getOffset() {
  int result = -1;
  if (this->indexpointer == NULL) {
    //cout << "initialze the decoding index node first!" << endl;
    return result;
  }

  else {
    result = *(int *)indexpointer;
  }
  return result;
}

int decodingindexNode::getKeynum() {
  int result = 0;
  result = *(int *)(this->indexpointer + 4);
  return result;
}

int decodingindexNode::getKey(int number) {
  // the number here is starting from 1
  int result = -1;
  result = *(int *)(this->indexpointer + 4 + 4 * number);
  return result;
}

int decodingindexNode::nodeSize() { return this->indexNodesize; }
