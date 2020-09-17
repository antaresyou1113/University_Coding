#ifndef _LEAVES_H_
#define _LEAVES_H_

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
#include <thread>
#include "Leaf.h"
#include "Node.h"
#include "Tree.h"
#include "decodingindexNode.h"
#include "encodingindexNode.h"
using namespace std;

class Leaves {
 private:
  Leaf *head;
  Leaf *tail;
  int position;      // the number of leaves in the dictionary
  int position1;     // the number of leaves of the suffix dictionary
  int suffix_start;  // the starting point of the suffix dictionary
  vector<encodingindexNode> fullindex;
  vector<decodingindexNode> index_decode;
  vector<encodingindexNode> index_encode_suffix;
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
  thread concurrent_worker_encodeThread(vector<string> strings, int mode);
  void concurrent_worker_encode(vector<string> strings, int mode);
  void concurrent_task_encode(vector<string> strings, int mode);
  void serial_task_encode(vector<string> strings, int mode);
  vector<encodingindexNode> &Getfullindex();
  vector<decodingindexNode> &Getindex_decode();
  vector<encodingindexNode> &Getindex_suffix();

  encodingIndex *encodingpointer;  // the pointer to the encoding index
  int lookUp(char *value);
  vector<int> lookUpIndexSuffix(char *value);
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
  void readFile(string filename);
  // read the file and get the dictionary and indexes
  Leaf *getLeaf(int position);
  int getLeavesnum(void);
  int getsuffixLeavesnum(void);  // the number of leaves in the suffix
                                 // dictionary
  int getAllleaves(void);
  void Insert(Leaf &leaf);       // just insert a leaf into the leaves list
};

#endif  //_LEAVES_H_
