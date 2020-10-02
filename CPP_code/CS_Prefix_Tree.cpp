#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

class Node {
 private:
  int nodesize;  // the size of the node
 public:
  int getNodesize(void);
  void setNodesize(int nodesize);
  char *pointerNode;
  void insertLeafnum(int leaf_num);
  int getLeafnum(void);
  void insertKeynum(int keys_num);
  int getKeynum(void);
  void insertKeys(char *keypointer);
  // char *getKeys(void);

  // CS_Prefix_Tree *next;
  Node *next;  // pointer to the next node
  Node(const Node &node_tmp);
  Node(int nodesize = 32, Node *next = NULL);
  ~Node();
};

void Node::insertKeys(char *keypointer) {
  if (keypointer != NULL) {
    for (int i = 0; i < (this->nodesize - 8); i++) {
      pointerNode[i + 8] = keypointer[i];
    }
  } else {
    cout << "No insert value! " << endl;
  }
}

int Node::getLeafnum() {
  int result = -1;
  if (pointerNode == NULL) {
    cout << "initialize the index node first!" << endl;
    return result;
  } else {
    result = *(int *)pointerNode;
  }
  return result;
}

void Node::insertLeafnum(int leaf_num) {
  pointerNode[3] = leaf_num >> 24;
  pointerNode[2] = leaf_num >> 16;
  pointerNode[1] = leaf_num >> 8;
  pointerNode[0] = leaf_num;
  // int temp = *(int*)pointerNode;
  // cout<<temp<<" The insert leaf number is "<<endl;
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

Node::Node(const Node &node_tmp) {
  this->next = node_tmp.next;
  this->nodesize = node_tmp.nodesize;
  this->pointerNode = new char[this->nodesize];
  for (int i = 0; i < this->nodesize; i++) {
    this->pointerNode[i] = node_tmp.pointerNode[i];
  }
  cout << "Copy the node !" << endl;
}

Node::Node(int nodesize, Node *next) {
  this->nodesize = nodesize;
  this->pointerNode = NULL;
  this->pointerNode = new char[this->nodesize];
  this->next = next;
  cout << "Create one node!" << endl;
}

Node::~Node() {
  delete[] pointerNode;
  cout << "delete one node!" << endl;
}

class Tree {
 private:
  Node *head;
  Node *tail;
  int position;

 public:
  Tree();
  ~Tree();
  Node *getNode(int position);
  void Insert(Node &node);
};

Tree::Tree() {
  head = tail = NULL;
  position = 0;
}

Tree::~Tree() { delete head; }

Node *Tree::getNode(int position) {
  Node *p = head;
  if (p == NULL) {
    cout << "There is no index" << endl;
  } else {
    int posi = 0;
    while (p != NULL && posi != position) {
      posi++;
      p = p->next;
    }
    if (p == NULL) {
      cout << "There is no such index!" << endl;
      return NULL;
    } else {
      cout << "The index has been found!" << endl;
      return p;
    }
  }
  return NULL;
}

void Tree::Insert(Node &node) {
  if (head == NULL) {
    head = tail = new Node(node);
    head->next = NULL;
    tail->next = NULL;
    cout << " The first index node inserted! " << endl;
  } else {
    Node *p = new Node(node);
    tail->next = p;
    tail = p;
    cout << "Insert a new index node! " << endl;
    tail->next = NULL;
  }
}

int main() {
  Node node;
  node.insertLeafnum(1250);
  int first = node.getLeafnum();
  cout << "The number of the first child is " << first << endl;
  node.insertKeynum(3);
  int keys_num = node.getKeynum();
  cout << "The number of the keys in this index node is " << keys_num << endl;
  Tree tree1;
  tree1.Insert(node);
  tree1.Insert(node);
  tree1.getNode(1);
  tree1.getNode(3);

  cout << "Test!" << endl;
}
