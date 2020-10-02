#ifndef _LEAF2_H_
#define _LEAF2_H_
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>
using namespace std;

int sizeLength(char *value);

vector<string> read_csv(string filename);

string generateKey(string str1, string str2);

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
  Node(int nodesize = 128, Node *next = NULL);
  ~Node();
};

class decodingindexNode {
 private:
  int level;
  int level_num;
  int indexNodesize;

 public:
  decodingindexNode(int indexNodesize = 128);
  decodingindexNode(const decodingindexNode &node_tmp);
  ~decodingindexNode();
  // void insertNode(Node &node);
  void setLevelnum(int level_num);
  void setLevel(int level);
  void setNodesize(int nodesize);
  void setOffset(int offset);
  void insertKey(int key);
  char *indexpointer;
  int getLevelnum(void);
  int getLevel(void);
  int getOffset(void);
  int getKeynum(void);
  int getKey(int number);
  int nodeSize(void);
  int smallestKey(void);
};

class encodingindexNode {
 private:
  int level;
  int level_num;      // the number of nodes in this level
  int indexNodesize;  // the size of the node
 public:
  encodingindexNode(int indexNodesize = 128);
  encodingindexNode(const encodingindexNode &node_tmp);
  ~encodingindexNode();
  void insertNode(Node &node);
  char *indexpointer;
  void insertLevelnum(int level_num);
  int getLevelnum(void);
  int getLevel(void);
  int getOffset(void);
  int getKeynum(void);
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

class Leaf {
 private:
  int leafSize;    // the memory size in bytes allocated for a leaf
  int offsetSize;  // the number of bytes used as offset inside the leaf
  int codeSize;    // the number of bytes used to represent the integer codeword
  int prefixSize;  // the number of bytes used to encode the length of the
                   // common prefix
  int decodeInterval;  // the interval used to store uncompressed strings
  int value_num;  // the number of values in this leaf, include the uncompressed
                  // and compressed strings
  int string_num;  // the current number of uncompressed strings in the leaf,
                   // not all the strings in the leaf data int leaf_data; //
                   // where the leaf data ends
 public:
  // the method is used to print all the strings in this leaf
  void printStrings(void);
  int bulkLoad_initialSuffix(char *leafpointer, char **str, int i);
  // i is the number of strings that are ready to be inserted
  int bulkload_initial(
      char *leafpointer, char **str, int i,
      unsigned int code_start);  // the second pointer point to an array of
                                 // pointers that point to a string.
                                 // the first pointer is un-needed, fixed later
                                 // the last parameter is the number of values
                                 // ready to be inserted
  int leaf_data;
  unsigned int node_first;
  // the number of the first code in this leaf, it is used to
  // generate the code for the value in this leaf. If it is not
  // the fisrt leaf, the number will be extracted from the last
  // node if the last leaf.
  unsigned int node_last;  // the number of the last code in this leaf, pass it
                           // to the next leaf as the begin of the code.
  char *pointerLeaf;
  int smallestCode(void);
  string smallestValue(void);
  string largestValue(void);
  string largestValue1(void);
  vector<int> bulkLookup_prefix(char *leafpointer, char *value);
  int bulkLookup(char *leafpointer, char *value);
  string bulkLookup_code(char *leafpointer, int code);
  int binarySearch_prefix(char *leafpointer, int start_off, int end_off,
                          char *value);
  int binarySearch(char *leafpointer, int start_off, int end_off, char *value);
  int binarySearch_code(char *leafpointer, int start, int end, int code);
  int sizeLength(char *value);
  int prefix_len(char *value, char *value_curr);
  int compareValue(char *value_curr, char *value);
  void printLeaf(int start, int end);
  vector<int> sequentialSearch_prefix(char *leafpointer, int start, int end,
                                      char *value);
  int sequentialSearch(char *leafpointer, int start, int end, char *value);
  string sequentialSearch_code(char *leafpointer, int start, int end, int code);
  string sequentialSearch_code1(int prefix_len, int start, int end, int code);
  void setLeaf_size(int Leaf_size);
  int getLeaf_size(void);
  void setOffset_size(int Offset_size);
  int getOffset_size(void);
  void setCode_size(int Code_size);
  int getCode_size(void);
  void setPrefix_size(int Prefix_size);
  int getPrefix_size(void);
  void setDecode_interval(int Decode_interval);
  int getDecode_interval(void);
  void setString_num(int number);
  int getString_num(void);
  static bool mycomp(string a, string b);
  vector<string> alphabaticallySort(vector<string> a);
  Leaf *
      next;  // point to the next leaf. All the leaves will be built into a list
  Leaf(const Leaf &leaf_tmp);
  Leaf(int Leaf_size = 1024, int Offset_size = 3, int Code_size = 4,
       int Prefix_size = 1, int Decode_interval = 16, int string_num = 0,
       Leaf *Leaf_pointer = NULL);  // constructor
  ~Leaf();
};

class Leaves {
 private:
  Leaf *head;
  Leaf *tail;
  int position;
  vector<encodingindexNode> fullindex;
  vector<decodingindexNode> index_decode;
  vector<string> decode_result;
  vector<int> encode_result;
  mutex exclusive;

 public:
  Leaves();
  ~Leaves();
  thread concurrent_worker_decodeThread(vector<int> codes);
  void concurrent_worker_decode(vector<int> codes);
  void concurrent_task_decode(vector<int> codes);
  void serial_task_decode(vector<int> codes);
  thread concurrent_worker_encodeThread(vector<string> strings);
  void concurrent_worker_encode(vector<string> strings);
  void concurrent_task_encode(vector<string> strings);
  void serial_task_encode(vector<string> strings);
  vector<encodingindexNode> &Getfullindex();
  vector<decodingindexNode> &Getindex_decode();
  encodingIndex *encodingpointer;  // the pointer to the encoding index
  int lookUp(char *value);
  vector<int> lookUpIndex(char *value, int prefix_flag);
  string lookupCode(int code);
  string lookupCode_index(int code);
  int bulkLoad(vector<string> strs);
  // build a new dictionary for the suffix matching
  int bulkLoadSuffix(vector<string> strs);
  int encodingIndexcreation();
  // create the index based on the suffix dictionary
  int encodingIndexcreationSuffix();
  int decodingIndexcreation();
  void generateFile(string filename);  // generate the file to store the
                                       // dictionary and indexes
  void readFile(
      string filename);  // read the file and get the dictionary and indexes
  Leaf *getLeaf(int position);
  int getLeavesnum(void);
  void Insert(Leaf &leaf);  // just insert a leaf into the leaves list
};

#endif  //_LEAF_H1_
