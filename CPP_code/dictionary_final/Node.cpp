#include "Node.h"

int Node::getVector(int number) {
  if (number <= this->key_num) {
    int offset = (number - 1) * 4 + 8;
    int vector = *(int *)(this->pointerNode + offset);
    return vector;
  } else {
    return -1;
  }
}

void Node::setLevelnum(int level_num) { this->level_num = level_num; }

int Node::getLevelnum() { return this->level_num; }

string Node::smallestKey() {
  string result = "";
  result = this->getKey(1);
  return result;
}

string Node::getKey(int number) {
  string result = "";
  if (number <= this->key_num) {
    int vector = this->getVector(number);
    result = (this->pointerNode + vector);
  }
  return result;
}

void Node::emptyNode() {
  this->key_num = 0;
  this->watch1 = 8;
  this->watch2 = nodesize - 1;
  //cout << "empty a node" << endl;
}


int Node::insertKeys(string key) {
  if (!key.empty()) {
    int i = 0;
    int key_len = key.length() + 1;
    watch1 += 4;
    watch2 -= key_len;
    int vector = watch2;
    if (watch1 > watch2) {
      return -1;
    } else {
      this->key_num++;
      this->insertKeynum(key_num);
      //cout << "the number of keys here: " << key_num
           //<< endl;  // test the insertion
      // add 1 to key number
      char *p = (char *)&vector;
      // insert the vector
      for (int j = watch1 - 4; j < watch1; j++) {
        pointerNode[j] = *((char *)p + j - watch1 + 4);
      }
      // insert the key
      for (i = watch2; i < watch2 + key_len; i++) {
        pointerNode[i] = key[i - watch2];
      }
      return 0;
    }

  } else {
    //cout << "The keypointer is NULL " << endl;
    return -1;
  }
}

int Node::getLeafnum() {
  int result = -1;
  if (pointerNode == NULL) {
    //cout << "initialize the index node first!" << endl;
    return result;
  } else {
    result = *(int *)pointerNode;
  }
  return result;
}

void Node::insertLeafnum(int leaf_num) {
  char *p = (char *)&leaf_num;
  this->pointerNode[0] = *((char *)p + 0);
  this->pointerNode[1] = *((char *)p + 1);
  this->pointerNode[2] = *((char *)p + 2);
  this->pointerNode[3] = *((char *)p + 3);
  // int temp = *(int*)pointerNode;
  // //cout<<temp<<" The insert leaf number is "<<endl;
}

int Node::getKeynum() {
  int result = 0;
  result = *(int *)(pointerNode + 4);
  return result;
}

void Node::insertKeynum(int keys_num) {
  pointerNode[7] = keys_num >> 24;
  pointerNode[6] = keys_num >> 16;
  pointerNode[5] = keys_num >> 8;
  pointerNode[4] = keys_num;
}

int Node::getNodesize() { return nodesize; }

void Node::setNodesize(int nodesize) { this->nodesize = nodesize; }

int Node::getLevel() { return this->level; }

void Node::setLevel(int level) { this->level = level; }

Node::Node(const Node &node_tmp) {
  this->level_num = node_tmp.level_num;
  this->level = node_tmp.level;
  this->key_num = node_tmp.key_num;
  this->watch1 = node_tmp.watch1;
  this->watch2 = node_tmp.watch2;
  this->next = node_tmp.next;
  this->nodesize = node_tmp.nodesize;
  this->pointerNode = new char[this->nodesize];
  for (int i = 0; i < this->nodesize; i++) {
    this->pointerNode[i] = node_tmp.pointerNode[i];
  }
  //cout << "Copy the node !" << endl;
}

Node::Node(int nodesize, Node *next) {
  this->nodesize = nodesize;
  this->key_num = 0;
  this->level_num = 0;
  this->level = 0;
  this->watch1 = 8;
  this->watch2 = nodesize - 1;
  this->pointerNode = NULL;
  this->pointerNode = new char[this->nodesize];
  this->next = next;
  //cout << "Create one node!" << endl;
}

Node::~Node() {
  delete[] pointerNode;
  //cout << "delete one node!" << endl;
}
