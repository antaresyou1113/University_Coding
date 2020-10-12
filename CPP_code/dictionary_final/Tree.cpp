#include "Tree.h"

Tree::Tree() {
  head = tail = NULL;
  position = 0;
  //cout << "create a new tree!" << endl;
}

Tree::~Tree() {
  delete head;
  //cout << "delete a tree!" << endl;
}

Node *Tree::getNode(int position) {
  Node *p = head;
  if (p == NULL) {
    //cout << "There is no index" << endl;
  } else {
    int posi = 0;
    while (p != NULL && posi != position) {
      posi++;
      p = p->next;
    }
    if (p == NULL) {
      //cout << "There is no such index!" << endl;
      return NULL;
    } else {
      //cout << "The index has been found!" << endl;
      return p;
    }
  }
  return NULL;
}

void Tree::deleteNode(int position) {
  Node *p = head;
  Node *p1 = head;
  if (p == NULL) {
    //cout << "There is no index" << endl;
  } else {
    int posi = 1;
    while (p != NULL && posi != position) {
      posi++;
      p1 = p;
      p = p->next;
    }
    if (p == NULL) {
      //cout << "There is no such index!" << endl;
    } else {
      if (position == this->position) {
        // I need to delete the last one
        p1->next = NULL;
        p = NULL;
      } else {
        p1->next = p->next;
        p = NULL;
      }
      //cout << "Delete the node! " << position << endl;
    }
  }
}

int Tree::nodeNum() { return this->position; }

void Tree::Insert(Node &node) {
  if (head == NULL) {
    head = tail = new Node(node);
    head->next = NULL;
    tail->next = NULL;
    //cout << " The first index node inserted! " << endl;
  } else {
    Node *p = new Node(node);
    tail->next = p;
    tail = p;
    //cout << "Insert a new index node! " << endl;
    tail->next = NULL;
  }
  position++;
}

void Tree::setNode(int posi, Node &node) {
  Node *p = head;
  Node *p1 = head;
  if (p == NULL) {
    //cout << "The list is empty" << endl;
  } else {
    int posi1 = 1;
    while (p != NULL && posi1 != posi) {
      posi1++;
      p1 = p;
      p = p->next;
    }
    if (p == NULL) {
      //cout << "There is no such node in that position" << endl;
    } else {
      Node *q = new Node(node);
      p1->next = q;
      q->next = p->next;
      p = NULL;
    }
  }
}
