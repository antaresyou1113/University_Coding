#ifndef _LEAF_H_
#define _LEAF_H_

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
using namespace std;

int sizeLength(char *value);

vector<string> read_csv(string filename);

string generateKey(string str1, string str2);


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
  int getValuenum(void);
  void setValuenum(int);
  int getStringnum(void);
  void setStringnum(int);
  void printStrings(void);
  int bulkLoad_initialSuffix(char *leafpointer, char **str, int i,
                             vector<int> codes);
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

#endif  //_LEAF_H_
