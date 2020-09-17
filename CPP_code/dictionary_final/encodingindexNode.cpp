#include "encodingindexNode.h"


void encodingindexNode::setLevel(int level) { this->level = level; }

void encodingindexNode::setLevelnum(int num) { this->level_num = num; }

void encodingindexNode::setIndexnodesize(int size) {
  this->indexNodesize = size;
}

int encodingindexNode::getIndexnodesize() { return this->indexNodesize; }

encodingindexNode::encodingindexNode(int indexNodesize) {
  this->level_num = 0;
  this->level = 0;
  this->indexNodesize = indexNodesize;
  this->indexpointer = NULL;
  this->indexpointer = new char[this->indexNodesize];
  //cout << "Create an index node!" << endl;
}

encodingindexNode::encodingindexNode(const encodingindexNode &node_tmp) {
  this->level_num = node_tmp.level_num;
  this->level = node_tmp.level;
  this->indexNodesize = node_tmp.indexNodesize;
  this->indexpointer = new char[this->indexNodesize];
  for (int i = 0; i < this->indexNodesize; i++) {
    this->indexpointer[i] = node_tmp.indexpointer[i];
  }
  //cout << "Copy the encoding index node!" << endl;
}

encodingindexNode::~encodingindexNode() {
  delete[] indexpointer;
  //cout << "Delete the encoding index node!" << endl;
}

int encodingindexNode::getLevel() { return this->level; }

int encodingindexNode::getLevelnum() { return this->level_num; }

void encodingindexNode::insertLevelnum(int level_num) {
  this->level_num = level_num;
}

void encodingindexNode::insertNode(Node &node) {
  Node *p = new Node(node);
  int nodesize = p->getNodesize();
  this->level_num = p->getLevelnum();
  this->level = p->getLevel();
  for (int i = 0; i < nodesize; i++) {
    this->indexpointer[i] = p->pointerNode[i];
  }
  //cout << "Insert the encoding index node based on Node object" << endl;
}

int encodingindexNode::getOffset() {
  int result = -1;
  if (indexpointer == NULL) {
    //cout << "Initialize the index node first!" << endl;
    return result;
  } else {
    result = *(int *)indexpointer;
  }
  return result;
}

int encodingindexNode::getKeynum() {
  int result = 0;
  if (indexpointer == NULL) {
    //cout << "Initialize the index node first!" << endl;
  } else {
    result = *(int *)(indexpointer + 4);
  }
  return result;
}

int encodingindexNode::getVector(int number) {
  if (number <= this->getKeynum()) {
    int offset = (number - 1) * 4 + 8;
    int vector = *(int *)(this->indexpointer + offset);
    return vector;
  } else {
    return -1;
  }
}

string encodingindexNode::getKey(int number) {
  string result = "";
  if (number <= this->getKeynum()) {
    int vector = this->getVector(number);
    result = (this->indexpointer + vector);
  }
  return result;
}

int encodingindexNode::nodeSize() { return this->indexNodesize; }

encodingIndex::encodingIndex(int nodeNum) {
  this->nodeNum = nodeNum;
  this->index = NULL;
  this->index = new encodingindexNode[this->nodeNum];
  //cout << "create a new index! " << endl;
}

encodingIndex::~encodingIndex() {
  delete[] index;
  //cout << "Delete the index!" << endl;
}

void encodingIndex::insertIndexnode(int position, encodingindexNode &node) {
  encodingindexNode *p1 = new encodingindexNode(node);
  encodingindexNode *p2 = this->index + position;
  int nodesize = p1->nodeSize();
  for (int i = 0; i < nodesize; i++) {
    p2->indexpointer[i] = p1->indexpointer[i];
  }
}

int encodingIndex::getNodenum() { return this->nodeNum; }
