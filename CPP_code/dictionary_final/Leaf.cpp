#include "Leaf.h"

string generateKey(string str1, string str2) {
  string result = "";
  char *p1 = (char *)str1.c_str();
  char *p2 = (char *)str2.c_str();
  int l1 = str1.length();
  int l2 = str2.length();
  int l = min(l1, l2);
  //cout //<< "the length " //<< l //<< endl;
  char p[l];
  //int r = 0;
  int i = 0;
  for (i = 0; i < l; i++) {
    if (p1[i] == p2[i]) {
      p[i] = p1[i];
      //cout //<< "The char here " //<< p[i] //<< " " //<< i //<< endl;
    } else if (p1[i] < p2[i]) {
      p[i] = p2[i];
      //cout //<< i //<< endl;
      break;
    } else {
    }
    // //cout //<< " the i " //<< i //<< " " //<< p1[i] //<< " " //<< p2[i] //<< endl;
  }
  // //cout //<< "The number of result " //<< i //<< endl;
  p[i + 1] = '\0';
  result = p;

  return result;
}

bool mycomp(string a, string b) { return a < b; }

vector<string> read_csv(string filename) {
  vector<string> result;
  ifstream myFile(filename);
  // make sure the file is open
  if (!myFile.is_open()) {
    throw runtime_error("Could not open the file");
  }
  string line, colname;
  string val;

  // read the column name
  // if (myFile.good()) {
  // getline(myFile, line);

  // create a string stream from line
  // stringstream ss(line);

  // extract each column name
  // while (getline(ss, colname)) {
  // add the data into the result
  // result.push_back(colname);
  // //cout //<< "column name: " //<< colname //<< endl;
  //}
  //}

  // read the data, line by line
  while (getline(myFile, line)) {
    // Create a string stream of the current line
    // stringstream ss(line);
    result.push_back(line);
    // //cout //<< "line value: " //<< line //<< endl;
  }

  myFile.close();
  return result;
}

int sizeLength(char *value) {
  int i = 0;
  while (value[i]) {
    i++;
  }
  return i;
}

int Leaf::getValuenum() { return this->value_num; }

void Leaf::setValuenum(int num) { this->value_num = num; }

int Leaf::getStringnum() { return this->string_num; }

void Leaf::setStringnum(int num) { this->string_num = num; }

void Leaf::printStrings() {
  // in this method, I need to print all the strings
  vector<string> result;
  vector<int> coderesult;
  string string_tmp;
  // make sure the number of strings in this leaf is larger than the number of
  // range
  int num_left = this->string_num;
  //cout //<< " string num is " //<< string_num //<< endl;
  char offset_tmp[offsetSize];
  int i;
  for (i = 0; num_left - i >= 1; i++) {
    for (int j = 0; j < offsetSize; j++) {
      offset_tmp[j] = pointerLeaf[leafSize - 1 + j - offsetSize -
                                  i * (offsetSize + codeSize)];
    }
    //int test = num_left - i * decodeInterval;
    // //cout //<< " decodeInterval= " //<< decodeInterval //<< " test " //<< test //<<
    // endl;
    int offset_tmp1 = *(int *)offset_tmp;
    // push back the uncompressed value
    string_tmp = this->pointerLeaf + offset_tmp1;
    result.push_back(string_tmp);  // push the uncompresse value into the vector
    // then I need to loop all the compressed values in this range
    // the starting point of the first compressed value
    int offset_tmp2 = offset_tmp1 + string_tmp.length() +
                      1;  // the start of the compressed value part
    //cout //<< "the start of the compressed value is " //<< offset_tmp2 //<< endl;
    char prefix_tmp[prefixSize];
    for (int j = 0; j < prefixSize; j++) {
      prefix_tmp[j] = this->pointerLeaf[offset_tmp2 + j];
    }
    int prefix_tmp1 = *(int *)prefix_tmp;
    //cout //<< "prefix here is " //<< prefix_tmp1 //<< endl;
    //cout //<< "offset_tmp2 here is " //<< offset_tmp2 //<< endl;
    char code_tmp[codeSize];
    int code_tmp1;
    for (int n = 0; n < codeSize; n++) {
      code_tmp[n] = this->pointerLeaf[leafSize - 1 + n -
                                      (i + 1) * (offsetSize + codeSize)];
    }
    code_tmp1 = *(int *)code_tmp;
    coderesult.push_back(code_tmp1);  // push the code into the vector
    // //cout //<< " The uncompressed string value is " //<< string_tmp
    ////<< " the code value is " //<< code_tmp1 //<< endl;
    // //cout //<< "the offset of the uncompressed value is: " //<< offset_tmp1
    ////<< " the prefix of the compressed value is: " //<< prefix_tmp1 //<< endl;
    string sub = string_tmp.substr(0, prefix_tmp1);
    // //cout //<< "The sub string is " //<< sub //<< endl;
    for (int m = 0; (m < decodeInterval - 1) &&
                    (m < (this->value_num - i * decodeInterval) - 1);
         m++) {
      offset_tmp2 += prefixSize;
      // string string_tmp1 = "";
      string_tmp = this->pointerLeaf + offset_tmp2;
      // //cout //<< " The compressed string value is " //<< string_tmp //<< endl;
      string_tmp = sub + string_tmp;
      // //cout //<< " The compressed string value is " //<< string_tmp //<< " m " //<< m
      ////<< endl;
      result.push_back(string_tmp);
      // //cout //<< " the offset in compressed part is " //<< offset_tmp2 //<< endl;
      offset_tmp2 += string_tmp.length() + 1 - sub.length();
      for (int n = 0; n < codeSize; n++) {
        code_tmp[n] = this->pointerLeaf[offset_tmp2 + n];
      }
      code_tmp1 = *(int *)code_tmp;
      coderesult.push_back(code_tmp1);
      // //cout //<< " The compressed value code is " //<< code_tmp1 //<< endl;
      offset_tmp2 += codeSize;
    }
    // //cout //<< "------------------------------------" //<< endl;
  }
  // if the left num_left is less than the num_range
  // //cout //<< "num value is " //<< value_num //<< endl;
  /**
  int num_left1 = this->value_num - i * decodeInterval;
  ////cout //<< "num left is " //<< num_left1 //<< endl;
  // i++;
  ////cout //<< " the i here is " //<< i //<< endl;
  char offset_tmp3[offsetSize];
  for (int j = 0; j < offsetSize; j++) {
    offset_tmp3[j] = pointerLeaf[leafSize - 1 + j - offsetSize -
                                 i * (offsetSize + codeSize)];
  }
  int offset_tmp1 = *(int *)offset_tmp3;
  ////cout //<< "offset_tmp4 here is " //<< offset_tmp1 //<< endl;
  string_tmp = this->pointerLeaf + offset_tmp1;
  result.push_back(string_tmp);
  char code_tmp[codeSize];
  int code_tmp1;
  for (int n = 0; n < codeSize; n++) {
    code_tmp[n] =
        this->pointerLeaf[leafSize - 1 + n - (i + 1) * (offsetSize + codeSize)];
  }
  code_tmp1 = *(int *)code_tmp;
  coderesult.push_back(code_tmp1);
  ////cout //<< " The left uncompressed string and code are " //<< string_tmp //<< " "
       ////<< code_tmp1 //<< endl;

  ////cout //<< "-----------here------------" //<< endl;
  ////cout //<< "num left " //<< num_left1 //<< endl;
  if (num_left1 > 1) {
    int offset_tmp2 = offset_tmp1 + string_tmp.length() + 1;
    ////cout //<< " offfset_tmp2 " //<< offset_tmp2 //<< endl;
    char prefix_tmp[prefixSize];
    for (int j = 0; j < prefixSize; j++) {
      prefix_tmp[j] = this->pointerLeaf[offset_tmp2 + j];
    }
    int prefix_tmp1 = *(int *)prefix_tmp;
    string sub = string_tmp.substr(0, prefix_tmp1);
    //cout //<< " sub here is " //<< sub //<< " prefix length " //<< prefix_tmp1 //<< endl;
    for (int m = 0; m < num_left1 - 1; m++) {
      offset_tmp2 += prefixSize;
      string_tmp = this->pointerLeaf + offset_tmp2;
      ////cout //<< " The compressed string value is " //<< string_tmp //<< endl;
      string_tmp = sub + string_tmp;
      ////cout //<< " The compressed string value is " //<< string_tmp //<< endl;
      result.push_back(string_tmp);
      offset_tmp2 += string_tmp.length() + 1 - sub.length();
      for (int n = 0; n < codeSize; n++) {
        code_tmp[n] = this->pointerLeaf[offset_tmp2 + n];
      }
      code_tmp1 = *(int *)code_tmp;
      coderesult.push_back(code_tmp1);
      ////cout //<< " The compressed value code is " //<< code_tmp1 //<< endl;
      offset_tmp2 += codeSize;
    }
  }
**/
  // the results of strings and codes are in the vectors now!
  // print them all!
  //for (auto array : result) {
    //cout //<< array //<< endl;
//  }
  //for (auto code : coderesult) {
    //cout //<< code //<< endl;
//  }
}

int Leaf::smallestCode() {
  int result = -1;
  char code[codeSize];
  for (int i = 0; i < codeSize; i++) {
    code[i] = this->pointerLeaf[leafSize + i - 1 - offsetSize - codeSize];
  }
  result = *(int *)code;
  return result;
}

string Leaf::smallestValue() {
  string result = "";
  // find the first value, get the uncompressed value from the offset
  char offset_tmp[offsetSize];
  for (int i = 0; i < offsetSize; i++) {
    offset_tmp[i] = this->pointerLeaf[leafSize - i - 1];
  }
  //int offset_small = *(int *)offset_tmp;
  result = this->pointerLeaf;

  // //cout //<< result //<< " The smallest value is " //<< endl;

  return result;
}

string Leaf::largestValue() {
  string result = "";
  int offset_vec = offsetSize + codeSize;
  char offset_tmp[offsetSize];
  // int num_vec = (int)ceil((double)string_num / (double)decodeInterval);
  // //cout //<< "number of vectors: " //<< num_vec //<< endl;
  for (int i = 0; i < offsetSize; i++) {
    offset_tmp[i] = this->pointerLeaf[leafSize - 1 - offsetSize + i -
                                      offset_vec * (string_num - 1)];
  }
  int offset_large = *(int *)offset_tmp;
  string test = this->pointerLeaf + offset_large;
  if (this->pointerLeaf + string_num * decodeInterval + 1 == NULL) {
    result = this->pointerLeaf + offset_large;
  } else {
    // the beginning of the first compressed value, the location of the prefix
    // length
    int offset_prefix =
        sizeLength(this->pointerLeaf + offset_large) + 1 + offset_large;
    char prefix_len[prefixSize];
    for (int i = 0; i < prefixSize; i++) {
      prefix_len[i] = this->pointerLeaf[i + offset_prefix];
    }
    // there is a bug here, I need to fix it later, the char* to int.

    int prefix = (int)prefix_len[0];
    int offset_result = offset_prefix;
    int offset_result1 = offset_result;
    for (int i = 0; i < decodeInterval - 1; i++) {
      if (this->pointerLeaf + offset_result &&
          *(this->pointerLeaf + offset_result) != '\0') {
        offset_result1 = offset_result;
        offset_result +=
            codeSize + prefixSize +
            sizeLength(this->pointerLeaf + offset_result + prefixSize) + 1;
      }
    }
    string str1 = this->pointerLeaf + offset_large;
    string str2 = str1.substr(0, prefix);
    string str3 = this->pointerLeaf + offset_result1 + prefixSize;
    result = str2 + str3;
    // //cout //<< "the result is " //<< result //<< " " //<< str1 //<< " " //<< str2 //<< " "
    ////<< str3 //<< endl;
  }

  return result;
}
// use this constructor to copy an object and allocate the memeory for the
// pointers
Leaf::Leaf(const Leaf &leaf_tmp) {
  value_num = leaf_tmp.value_num;
  node_first = leaf_tmp.node_first;
  node_last = leaf_tmp.node_last;
  leafSize = leaf_tmp.leafSize;
  offsetSize = leaf_tmp.offsetSize;
  codeSize = leaf_tmp.codeSize;
  prefixSize = leaf_tmp.prefixSize;
  decodeInterval = leaf_tmp.decodeInterval;
  string_num = leaf_tmp.string_num;
  leaf_data = leaf_tmp.leaf_data;
  pointerLeaf = new char[leafSize];
  for (int i = 0; i < leafSize; i++) {
    pointerLeaf[i] = leaf_tmp.pointerLeaf[i];
  }
  next = leaf_tmp.next;
  //cout //<< "Copy the leaf !" //<< endl;
}

Leaf::Leaf(int Leaf_size, int Offset_size, int Code_size, int Prefix_size,
           int Decode_interval, int number, Leaf *Leaf_pointer) {
  leafSize = Leaf_size;
  offsetSize = Offset_size;
  codeSize = Code_size;
  prefixSize = Prefix_size;
  decodeInterval = Decode_interval;
  string_num = number;
  pointerLeaf = NULL;
  pointerLeaf = new char[leafSize];
  leaf_data = 0;
  this->next = Leaf_pointer;
  node_first = 0;
  node_last = 0;
  //cout //<< "create the Leaf class" //<< endl;
}

Leaf::~Leaf() {
  delete[] pointerLeaf;
  //cout //<< "delete the Leaf class" //<< endl;
}

bool Leaf::mycomp(string a, string b) { return a < b; }

vector<string> Leaf::alphabaticallySort(vector<string> a) {
  sort(a.begin(), a.end(), mycomp);
  return a;
}

int Leaf::bulkLoad_initialSuffix(char *leafpointer, char **str, int i,
                                 vector<int> codes) {
  char *value[2 * i];
  int test_code;
  this->value_num = i;
  unsigned int code[i];
  // then all the strings need to be sorted
  vector<string> strs;
  for (int j = 0; j < i; j++) {
    strs.push_back(&(*str[j]));
    // //cout //<< "vector string: " //<< strs[j] //<< endl;
  }
  // starting from here, I need to generate the code based on the code in the
  // first
  for (int j = 0; j < i; j++) {
    const char *cstr = strs[j].c_str();
    value[2 * j] = (char *)cstr;

    code[j] = codes[j];  // generate the code for the initial values,
                         // start from 10, add each by 10, leave some
                         // space for later inserted values
    value[2 * j + 1] = (char *)&code[j];
    //cout //<< "The sorted value is: " //<< value[2 * j] //<< endl;
    //cout //<< "The generated code is: " //<< *(unsigned int *)value[2 * j + 1]
         //<< endl;  // test if the code has been pointed by the char * pointer
  }

  this->node_last = code[i - 1];
  // calculate the offset vectors, and set the number of uncompressed data.
  int off_vector = ceil((double)i / (double)decodeInterval);
  string_num = off_vector;
  //cout //<< " string number is " //<< string_num //<< endl;
  // //cout //<< "The number of offset vectors: " //<< string_num //<< endl;
  int prefix_length[string_num];
  char *value1[string_num * 2];
  for (int j = 0; j < string_num; j++) {
    value1[2 * j] = value[decodeInterval * j * 2];
    value1[2 * j + 1] = value[decodeInterval * j * 2 + 1];
    //cout //<< "offset vector: " //<< value1[2 * j] //<< " "
         //<< *(unsigned int *)value1[2 * j + 1] //<< endl;
  }
  // now I have the offset vectors

  for (int j = 0; j < string_num; j++) {
    if (decodeInterval > 1) {
      prefix_length[j] =
          prefix_len(value1[2 * j], value[(decodeInterval * j + 1) * 2]);
      for (int t = 0; t < decodeInterval and (decodeInterval * j + t) < i;
           t++) {
        int prefix_length1 =
            prefix_len(value1[2 * j], value[(decodeInterval * j + t) * 2]);
        if (prefix_length1 < prefix_length[j]) {
          prefix_length[j] = prefix_length1;
        }
      }
      //cout //<< "prefix length is: " //<< prefix_length[j] //<< endl;
      if (prefix_length[j] >= 255) {
        prefix_length[j] = 255;
      }
    } else {
      prefix_length[j] = 0;
    }
  }
  // all the prefix length in each range

  for (int j = 0; j < string_num; j++) {
    for (int t = 1;
         t < decodeInterval && j * decodeInterval + t < this->value_num; t++) {
      value[(decodeInterval * j + t) * 2] =
          &value[(decodeInterval * j + t) * 2][prefix_length[j]];
      //cout //<< "The compressed value is: " //<< value[(decodeInterval * j + t) * 2]
           //<< endl;
    }
  }
  // all the compressed value

  int offset[string_num];
  offset[0] = 0;
  if (string_num > 0) {
    for (int j = 1; j < string_num; j++) {
      offset[j] = sizeLength(value1[2 * (j - 1)]) + 1;
      for (int t = 1; t < decodeInterval &&
                      (decodeInterval * (j - 1) + t) < this->value_num;
           t++) {
        offset[j] += sizeLength(value[(decodeInterval * (j - 1) + t) * 2]) + 1 +
                     codeSize + prefixSize;
        //cout //<< " t here is " //<< t //<< endl;
      }
      offset[j] += offset[j - 1];
      //cout //<< "offset  uncompressed value is " //<< j //<< " is: " //<< offset[j]
           //<< endl;
    }
  }

  // all the offsets of the uncompressed value

  // now I have the offset, code of uncompressed strings, prefix length, code
  // and compressed strings start inserting all the data into the leaf
  int leaf_off = 0;  // used to know the ending offset of the leaf data
  for (int j = 0; j < string_num; j++) {
    string tmp = value1[2 * j];
    strcpy(leafpointer + offset[j], tmp.c_str());
    //cout //<< "The inserted uncompressed value is: " //<< leafpointer + offset[j]
         //<< endl;
    leaf_off += sizeLength(value1[2 * j]) + 1;
    char *prefix_tmp;
    prefix_tmp = (char *)&prefix_length[j];
    for (int t = 1;
         (t < decodeInterval) && (decodeInterval * j + t < this->value_num);
         t++) {
      for (int m = 0; m < prefixSize; m++) {
        leafpointer[leaf_off] = prefix_tmp[m];
        leaf_off++;
      }
      char prefix_tmp[prefixSize];
      for (int j = 0; j < prefixSize; j++) {
        prefix_tmp[j] = leafpointer[leaf_off - prefixSize + j];
      }
      //int prefix_tmp1 = *(int *)prefix_tmp;
      //cout //<< " the offset here is " //<< leaf_off - prefixSize //<< endl;
      //cout //<< "prefix length of compressed value is " //<< prefix_tmp1 //<< endl;
      tmp = value[(decodeInterval * j + t) * 2];
      strcpy(leafpointer + leaf_off, tmp.c_str());
      //cout //<< " the compressed data is " //<< leafpointer + leaf_off //<< endl;
      leaf_off += sizeLength(value[(decodeInterval * j + t) * 2]) + 1;
      char *code_tmp;
      code_tmp = value[(decodeInterval * j + t) * 2 + 1];
      for (int m = 0; m < codeSize; m++) {
        leafpointer[leaf_off] = code_tmp[m];
        leaf_off++;
      }
      test_code = leaf_off - codeSize;
      //cout //<< "The code here is : "
           //<< *(unsigned int *)(leafpointer + test_code) //<< endl;
      //cout //<< "The code here is : "
           //<< *(unsigned int *)(leafpointer + leaf_off - codeSize) //<< endl;
    }
    //cout //<< "offset now is: " //<< leaf_off //<< " " //<< test_code //<< endl;
  }
  int leaf_off1 = leaf_off;
  leaf_data = leaf_off1;
  // insert the offset vectors at the end of the leaf
  leaf_off = leafSize - 1 - string_num * (offsetSize + codeSize);
  //cout //<< "the start of the offset vectors: " //<< leaf_off //<< endl;
  for (int j = 0; j < string_num; j++) {
    char *code_tmp;
    code_tmp = value1[2 * (string_num - 1 - j) + 1];
    //cout //<< "code_tmp " //<< *(unsigned int *)value1[2 * (string_num - 1 - j) + 1]
         //<< endl;
    //cout //<< "The code here is : " //<< *(unsigned int *)(leafpointer + test_code)
         //<< endl;
    for (int m = 0; m < codeSize; m++, leaf_off++) {
      leafpointer[leaf_off] = code_tmp[m];
    }
    //cout //<< "The code here is : " //<< *(unsigned int *)(leafpointer + test_code)
         //<< endl;
    char *offset_tmp = (char *)&offset[string_num - 1 - j];
    //cout //<< "offset here " //<< offset[string_num - 1 - j] //<< endl;
    for (int m = 0; m < offsetSize; m++, leaf_off++) {
      leafpointer[leaf_off] = offset_tmp[m];
    }
    //cout //<< "The code here is : " //<< *(unsigned int *)(leafpointer + test_code)
         //<< endl;
    //char offset_tmp9[offsetSize];
    for (int j = 0; j < offsetSize; j++) {
      offset_tmp[j] = leafpointer[leaf_off - offsetSize + j];
    }
    //cout //<< "The code here is : " //<< *(unsigned int *)(leafpointer + test_code)
         //<< endl;
    //int offset_tmp8 = *(int *)offset_tmp9;
    //cout //<< "offset vectors: "
         //<< *(unsigned int *)(leafpointer + leaf_off - offsetSize - codeSize)
         //<< " " //<< offset_tmp8 //<< endl;
  }
  // this->printStrings();
  //cout //<< "The code here is : " //<< *(unsigned int *)(leafpointer + test_code)
       //<< endl;
  return 0;
}

int Leaf::bulkload_initial(char *leafpointer, char **str, int i,
                           unsigned int code_start) {
  char *value[2 * i];
  this->value_num = i;
  unsigned int code[i];
  // then all the strings need to be sorted
  vector<string> strs;
  for (int j = 0; j < i; j++) {
    strs.push_back(&(*str[j]));
    // //cout //<< "vector string: " //<< strs[j] //<< endl;
  }
  strs = alphabaticallySort(strs);
  for (int j = 0; j < i; j++) {
    const char *cstr = strs[j].c_str();
    value[2 * j] = (char *)cstr;
    if (code_start == 0) {
      code_start = code_start - 1;
    }  // this is how I make the first code to become 0
    code[j] = j + code_start + 1;  // generate the code for the initial values,
                                   // start from 10, add each by 10, leave some
                                   // space for later inserted values
    value[2 * j + 1] = (char *)&code[j];
    //cout //<< "The sorted value is: " //<< value[2 * j] //<< endl;
    //cout //<< "The generated code is: " //<< *(unsigned int *)value[2 * j + 1]
         //<< endl;  // test if the code has been pointed by the char * pointer
  }
  this->node_last = code[i - 1];
  // calculate the offset vectors, and set the number of uncompressed data.
  int off_vector = ceil((double)i / (double)decodeInterval);
  string_num = off_vector;
  //cout //<< " string number is " //<< string_num //<< endl;
  // //cout //<< "The number of offset vectors: " //<< string_num //<< endl;
  int prefix_length[string_num];
  char *value1[string_num * 2];
  for (int j = 0; j < string_num; j++) {
    value1[2 * j] = value[decodeInterval * j * 2];
    value1[2 * j + 1] = value[decodeInterval * j * 2 + 1];
    //cout //<< "offset vector: " //<< value1[2 * j] //<< " "
         //<< *(unsigned int *)value1[2 * j + 1] //<< endl;
  }
  // now I have the offset vectors

  for (int j = 0; j < string_num; j++) {
    if (decodeInterval > 1) {
      prefix_length[j] =
          prefix_len(value1[2 * j], value[(decodeInterval * j + 1) * 2]);
      for (int t = 0; t < decodeInterval && (decodeInterval * j + t) < i; t++) {
        int prefix_length1 =
            prefix_len(value1[2 * j], value[(decodeInterval * j + t) * 2]);
        if (prefix_length1 < prefix_length[j]) {
          prefix_length[j] = prefix_length1;
        }
      }
      //cout //<< "prefix length is: " //<< prefix_length[j] //<< endl;
      if (prefix_length[j] >= 255) {
        prefix_length[j] = 255;
      }
    } else {
      prefix_length[j] = 0;
    }
  }
  // all the prefix length in each range

  for (int j = 0; j < string_num; j++) {
    for (int t = 1;
         t < decodeInterval && j * decodeInterval + t < this->value_num; t++) {
      value[(decodeInterval * j + t) * 2] =
          &value[(decodeInterval * j + t) * 2][prefix_length[j]];
      //cout //<< "The compressed value is: " //<< value[(decodeInterval * j + t) * 2]
           //<< endl;
    }
  }

  // all the compressed value

  int offset[string_num];
  offset[0] = 0;
  if (string_num > 0) {
    for (int j = 1; j < string_num; j++) {
      offset[j] = sizeLength(value1[2 * (j - 1)]) + 1;
      for (int t = 1; t < decodeInterval &&
                      (decodeInterval * (j - 1) + t) < this->value_num;
           t++) {
        offset[j] += sizeLength(value[(decodeInterval * (j - 1) + t) * 2]) + 1 +
                     codeSize + prefixSize;
        //cout //<< " t here is " //<< t //<< endl;
      }
      offset[j] += offset[j - 1];
      //cout //<< "offset  uncompressed value is " //<< j //<< " is: " //<< offset[j]
           //<< endl;
    }
  }
  // all the offsets of the uncompressed value

  // now I have the offset, code of uncompressed strings, prefix length, code
  // and compressed strings start inserting all the data into the leaf
  int leaf_off = 0;  // used to know the ending offset of the leaf data
  for (int j = 0; j < string_num; j++) {
    string tmp = value1[2 * j];
    strcpy(leafpointer + offset[j], tmp.c_str());
    //cout //<< "The inserted uncompressed value is: " //<< leafpointer + offset[j]
         //<< endl;
    leaf_off += sizeLength(value1[2 * j]) + 1;
    char *prefix_tmp;
    prefix_tmp = (char *)&prefix_length[j];
    for (int t = 1;
         (t < decodeInterval) && (decodeInterval * j + t < this->value_num);
         t++) {
      for (int m = 0; m < prefixSize; m++) {
        leafpointer[leaf_off] = prefix_tmp[m];
        leaf_off++;
      }
      char prefix_tmp[prefixSize];
      for (int j = 0; j < prefixSize; j++) {
        prefix_tmp[j] = leafpointer[leaf_off - prefixSize + j];
      }
      //int prefix_tmp1 = *(int *)prefix_tmp;
      //cout //<< " the offset here is " //<< leaf_off - prefixSize //<< endl;
      //cout //<< "prefix length of compressed value is " //<< prefix_tmp1 //<< endl;
      tmp = value[(decodeInterval * j + t) * 2];
      strcpy(leafpointer + leaf_off, tmp.c_str());
      //cout //<< " the compressed data is " //<< leafpointer + leaf_off //<< endl;
      leaf_off += sizeLength(value[(decodeInterval * j + t) * 2]) + 1;
      char *code_tmp;
      code_tmp = value[(decodeInterval * j + t) * 2 + 1];
      for (int m = 0; m < codeSize; m++) {
        leafpointer[leaf_off] = code_tmp[m];
        leaf_off++;
      }
      //cout //<< *(unsigned int *)(leafpointer + leaf_off - codeSize) //<< endl;
    }
    // //cout //<< "offset now is: " //<< leaf_off //<< endl;
  }
  int leaf_off1 = leaf_off;
  leaf_data = leaf_off1;
  // insert the offset vectors at the end of the leaf
  leaf_off = leafSize - 1 - string_num * (offsetSize + codeSize);
  for (int j = 0; j < string_num; j++) {
    char *code_tmp;
    code_tmp = value1[2 * (string_num - 1 - j) + 1];
    //cout //<< "code_tmp " //<< *(unsigned int *)value1[2 * (string_num - 1 - j) + 1]
         //<< endl;
    for (int m = 0; m < codeSize; m++) {
      leafpointer[leaf_off] = code_tmp[m];
      leaf_off++;
    }

    char *offset_tmp = (char *)&offset[string_num - 1 - j];
    //cout //<< "offset here " //<< offset[string_num - 1 - j] //<< endl;
    for (int m = 0; m < offsetSize; m++) {
      leafpointer[leaf_off] = offset_tmp[m];
      leaf_off++;
    }
  //  char offset_tmp9[offsetSize];
    for (int j = 0; j < offsetSize; j++) {
      offset_tmp[j] = leafpointer[leaf_off - offsetSize + j];
    }
    //int offset_tmp8 = *(int *)offset_tmp9;
    //cout //<< "offset vectors: "
         //<< *(unsigned int *)(leafpointer + leaf_off - offsetSize - codeSize)
         //<< " " //<< offset_tmp8 //<< endl;
  }

  return 0;
}

string Leaf::bulkLookup_code(char *leafpointer, int code) {
  int end_uncompressed = string_num - 1;
  int start_uncompressed = 0;
  int resultBinary = binarySearch_code(this->pointerLeaf, start_uncompressed,
                                       end_uncompressed, code);
  //cout //<< " the result of binary search is " //<< resultBinary //<< endl;
  if (resultBinary == -1) {
    // //cout //<< "Thevalue does not exist!" //<< endl;
    return "";
  } else {
    int offset_result = leafSize - 1 - (offsetSize + codeSize) * resultBinary;
    //cout //<< "herer " //<< endl;
    char offset_tmp[offsetSize];
    for (int m = 0; m < offsetSize; m++) {
      offset_tmp[m] = this->pointerLeaf[offset_result - offsetSize + m];
    }
    unsigned int offset = *(unsigned int *)(offset_tmp);

    //cout //<< "offset to the target interval is " //<< offset //<< endl;
    string resultValue = this->pointerLeaf + offset;
    char code_tmp[codeSize];
    for (int m = 0; m < codeSize; m++) {
      code_tmp[m] =
          this->pointerLeaf[offset_result - offsetSize - codeSize + m];
    }
    int code1 = *(int *)(code_tmp);
    //cout //<< "the code here is " //<< code1 //<< endl;
    if (code1 == code) {
      //cout //<< "The result is in the uncompressed part: " //<< resultValue //<< endl;
      return resultValue;
    } else {
      //cout //<< "Search the code in the compressed value part: " //<< endl;
      code =
          code - code1;  // use this to locate the compressed value in the range
      unsigned int offset1;
      if (resultBinary + 1 < string_num) {
        unsigned int offset_result1 =
            (offsetSize + codeSize) * (resultBinary + 1);
        unsigned int offset_temp1 = leafSize - 1 - offset_result1;
        char off_tmp[offsetSize];
        for (int m = 0; m < offsetSize; m++) {
          off_tmp[m] = this->pointerLeaf[offset_temp1 - offsetSize + m];
        }
        offset1 = *(unsigned int *)off_tmp;
      } else {
        offset1 = leaf_data;
      }

      this->printStrings();
      char tmp[prefixSize];
      for (int m = 0; m < prefixSize; m++) {
        tmp[m] = this->pointerLeaf[offset + resultValue.length() + 1 + m];
      }
      int test_tmp = *(int *)tmp;
      // //cout //<< "the test of the prefix here is " //<< test_tmp //<< endl;

      resultValue = sequentialSearch_code1(test_tmp, offset, offset1, code);
      // //cout //<< "result value is: " //<< resultValue //<< endl;
      return resultValue;
    }
  }

  return "";  // it seems wrong to return the NULL if no such code exists
}

vector<int> Leaf::bulkLookup_prefix(char *leafpointer, char *value) {
  vector<int> result;
  // this is the method to search the prefix in one leaf
  int end_uncompressed = string_num - 1;
  vector<int> result_prefix;

  int start_uncompressed = 0;
  //cout //<< "start is: " //<< start_uncompressed //<< endl;
  //cout //<< "end is: " //<< end_uncompressed //<< endl;
  int resultBinary =
      binarySearch_prefix(leafpointer, start_uncompressed, end_uncompressed,
                          value);  // the reuslt of binary search
  // for the prefix matching, the binary search will still be able to find the
  // start of the range
  //cout //<< resultBinary //<< " The result of the binary search is " //<< endl;

  if (resultBinary == -1) {
    //cout //<< "the value does not exist, based on binary search." //<< endl;
    return result;
  } else {
    unsigned int offset_result =
        (offsetSize + codeSize) *
        resultBinary;  // locate the offset vector of the result, in order to
                       // locate the offset of the result value later

    char tmp[offsetSize];
    for (int m = 0; m < offsetSize; m++) {
      tmp[m] = leafpointer[leafSize - 1 - offset_result - offsetSize + m];
    }
    unsigned int offset = *(unsigned int *)(tmp);
    char *resultValue = &leafpointer[offset];

    int result_tmp = -1;  // the code of the prefix matching result
    string resultValue_tmp = resultValue;
    //cout //<< "The result of the binary search is " //<< resultValue_tmp //<< endl;

    string value_prefix = value;
    if (resultValue_tmp.find(value_prefix) == 0) {
      //cout //<< "Find the uncompressed result value!" //<< endl;
      int off_temp = leafSize - 1 - offset_result - offsetSize - codeSize;
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off_temp + m];
      }
      result_tmp = *(int *)(code_tmp);
    }
    // the uncompressed value is one result, but we still need to do the
    // sequential search to check the strings in that range

    unsigned int offset1;
    if (resultBinary + 1 < string_num) {
      // meaning the resultBinary is the last interval
      unsigned int offset_result1 =
          (offsetSize + codeSize) * (resultBinary + 1);
      // locate the offset of the start of the uncompressed value
      unsigned int offset_temp1 = leafSize - 1 - offset_result1;
      char off_tmp[offsetSize];
      for (int m = 0; m < offsetSize; m++) {
        off_tmp[m] = leafpointer[offset_temp1 - offsetSize + m];
      }
      offset1 = *(unsigned int *)off_tmp;
    } else {
      offset1 = leaf_data;
    }
    //cout //<< "the start point and the end point of sequentialSearch " //<< offset
         //<< " " //<< offset1 //<< endl;
    result = sequentialSearch_prefix(leafpointer, offset, offset1, value);

    string value_next = &leafpointer[offset1];
    //cout //<< "The next uncompressed value is " //<< value_next //<< endl;
    // then we need to start the while loop, to test the rest ranges in this
    // leaf in order to make sure all the data is here.
    while (value_next.find(value_prefix) == 0) {
      //cout //<< "Find the uncompressed result value!" //<< endl;
      offset_result = offset_result + offsetSize + codeSize;
      int off_temp = leafSize - 1 - offset_result - offsetSize - codeSize;
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off_temp + m];
      }
      result.push_back(*(int *)(code_tmp));
      //cout //<< "the uncompressed result here is " //<< *(int *)(code_tmp) //<< endl;
      offset = offset1;
      resultBinary++;
      //cout //<< resultBinary //<< " the result binary is "
           //<< "leaf_data " //<< leaf_data //<< "the string num is " //<< string_num
           //<< endl;
      if (resultBinary + 1 < string_num) {
        unsigned int offset_result1 =
            (offsetSize + codeSize) * (resultBinary + 1);
        unsigned int offset_temp1 = leafSize - 1 - offset_result1;
        char off_tmp[offsetSize];
        for (int m = 0; m < offsetSize; m++) {
          off_tmp[m] = leafpointer[offset_temp1 - offsetSize + m];
        }
        offset1 = *(unsigned int *)off_tmp;
      } else {
        offset1 = leaf_data;
        // printLeaf(0, 1023);
        // //cout //<< "Leaf data is  iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii "
        ////<< leaf_data //<< endl;
      }
      string starting = &leafpointer[offset];
      //cout //<< "The string staring is " //<< starting //<< endl;
      vector<int> tmp =
          sequentialSearch_prefix(leafpointer, offset, offset1, value);
      for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] != -1) {
          result.push_back(tmp[i]);
        }
      }
      value_next = &leafpointer[offset1];
    }

    if (result_tmp != -1) {
      result.push_back(result_tmp);
    }
    return result;
  }
}

int Leaf::bulkLookup(char *leafpointer, char *value) {
  int end_uncompressed = string_num - 1;
  vector<int> result_prefix;

  int start_uncompressed = 0;
  // //cout //<< "start is: " //<< start_uncompressed //<< endl;
  // //cout //<< "end is: " //<< end_uncompressed //<< endl;
  int resultBinary =
      binarySearch_prefix(leafpointer, start_uncompressed, end_uncompressed,
                          value);  // the reuslt of binary search
  // for the prefix matching, the binary search will still be able to find the
  // start of the range
  //cout //<< "The binary search value is " //<< resultBinary //<< endl;
  if (resultBinary == -1) {
    //cout //<< "the value does not exist, based on binary search." //<< endl;
    return -1;
  }

  else {
    unsigned int offset_result =
        (offsetSize + codeSize) *
        resultBinary;  // locate the offset vector of the result, in order to
                       // locate the offset of the result value later

    char tmp[offsetSize];
    for (int m = 0; m < offsetSize; m++) {
      tmp[m] = leafpointer[leafSize - 1 - offset_result - offsetSize + m];
    }
    unsigned int offset = *(unsigned int *)(tmp);
    char *resultValue = &leafpointer[offset];
    // //cout //<< "result value is: " //<< resultValue
    ////<< endl;  // the testing result works fine
    int result;  // the final code to return
    if (strcmp(value, resultValue) == 0) {
      // //cout //<< "Find the uncompressed result value!" //<< endl;
      int off_temp = leafSize - 1 - offset_result - offsetSize - codeSize;
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off_temp + m];
      }
      result = *(int *)(code_tmp);
      result_prefix.push_back(result);
      // //cout //<< "The code of uncompressed result is: " //<< result //<< endl;
      return result;
    } else {
      //cout //<< "Search on the compressed value part!" //<< endl;
      unsigned int offset1;
      if (resultBinary + 1 < string_num) {
        unsigned int offset_result1 =
            (offsetSize + codeSize) * (resultBinary + 1);
        unsigned int offset_temp1 = leafSize - 1 - offset_result1;
        char off_tmp[offsetSize];
        for (int m = 0; m < offsetSize; m++) {
          off_tmp[m] = leafpointer[offset_temp1 - offsetSize + m];
        }
        offset1 = *(unsigned int *)off_tmp;
      } else {
        offset1 = leaf_data;
      }
       //cout //<< "The start offset of sequentialSearch is: " //<< offset //<<
       //endl; //cout //<< "The end offset of sequentialSearch is: " //<< offset1 //<<
       //endl;
      //string value_next = &leafpointer[offset1];
      ////cout //<< "The next uncompressed value is " //<< value_next //<< endl;
      result = sequentialSearch(leafpointer, offset, offset1, value);

      return result;
    }

    return -1;
  }
}

int Leaf::binarySearch_code(char *leafpointer, int start, int end, int code) {
  if (end >= start) {
    int mid = start + (end - start) / 2;
    //cout //<< "binary_code start: " //<< start //<< endl;
    //cout //<< "binary_code end: " //<< end //<< endl;
    //cout //<< "binary_code code: " //<< code //<< endl;
    //cout //<< "binary_code mid: " //<< mid //<< endl;
    int offset_1 = leafSize - 1 - offsetSize - (offsetSize + codeSize) * mid;
    char code_tmp[codeSize];
    for (int m = 0; m < codeSize; m++) {
      code_tmp[m] = leafpointer[offset_1 - codeSize + m];
    }
    int code1 = *(int *)(code_tmp);
    int code2 = 0;
    int offset_2 =
        leafSize - 1 - offsetSize - (offsetSize + codeSize) * (mid + 1);
    // test if offset_2 is still in the uncompressed data range
    if (offset_2 > leafSize - 1 - (offsetSize + codeSize) * (string_num)) {
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[offset_2 - codeSize + m];
      }
      code2 = *(int *)(code_tmp);
    }
    // if the offset_2 is not in the offset vector part, meaning this is the
    // search for the last interval, I need to calculate the code2 as the last
    // code in this leaf else{ code2 = code1 + value_num-mid*decodeInterval-1;
    //}
    //cout //<< "binary_code code1 is: " //<< code1 //<< endl;
    //cout //<< "bianry_code code2 is: " //<< code2 //<< endl;

    if (code1 < code) {
      if (code < code2) {
        return mid;
      } else if (offset_2 <
                 leafSize - 1 - (offsetSize + codeSize) * (string_num)) {
        return mid;
      }
      return binarySearch_code(pointerLeaf, mid + 1, end, code);
    }

    else if (code1 == code) {
      return mid;
    }

    else {
      return binarySearch_code(pointerLeaf, start, mid - 1, code);
    }
  }
  return -1;
}

int Leaf::binarySearch(char *leafpointer, int start_off, int end_off,
                       char *value) {
  if (end_off >= start_off) {
    int mid_off = start_off + (end_off - start_off) / 2;
    int offset_1 =
        (offsetSize + codeSize) * mid_off;  // locate the offset vector of the
                                            // middle uncompressed string
    int offset_2 = (offsetSize + codeSize) *
                   (mid_off + 1);  // locate the offset vector of the middle + 1
                                   // uncompressed data, for comparison later.

    char tmp[offsetSize];
    char tmp1[offsetSize];
    for (int m = 0; m < offsetSize; m++) {
      tmp[m] = leafpointer[leafSize - 1 - offset_1 - offsetSize + m];
      tmp1[m] = leafpointer[leafSize - 1 - offset_2 - offsetSize + m];
    }
    int offset1 = *(unsigned int *)(tmp);
    int offset2 = *(unsigned int *)(tmp1);
    char *value1 = &leafpointer[offset1];
    char *value2 = &leafpointer[offset2];
    //cout //<< "offset1: " //<< offset1 //<< " " //<< offset_1 //<< endl;
    //cout //<< "value1: " //<< value1 //<< endl;
    //cout //<< "value: " //<< value //<< endl;
    if (strcmp(value1, value) < 0) {
      if (strcmp(value, value2) <
          0)  // make sure value1<=value, and there is no value2 between them
      {
        return mid_off;
      }

      return binarySearch(leafpointer, mid_off + 1, end_off, value);
    } else if (strcmp(value1, value) == 0) {
      return mid_off;
    } else {
      return binarySearch(leafpointer, start_off, mid_off - 1, value);
    }
  }
  return -1;
}

int Leaf::binarySearch_prefix(char *leafpointer, int start_off, int end_off,
                              char *value) {
  if (end_off >= start_off) {
    int mid_off = start_off + (end_off - start_off) / 2;
    int offset_1 =
        (offsetSize + codeSize) * mid_off;  // locate the offset vector of the
                                            // middle uncompressed string
    int offset_2 = (offsetSize + codeSize) *
                   (mid_off + 1);  // locate the offset vector of the middle + 1
                                   // uncompressed data, for comparison later.

    char tmp[offsetSize];
    char tmp1[offsetSize];
    for (int m = 0; m < offsetSize; m++) {
      tmp[m] = leafpointer[leafSize - 1 - offset_1 - offsetSize + m];
      tmp1[m] = leafpointer[leafSize - 1 - offset_2 - offsetSize + m];
    }
    int offset1 = *(unsigned int *)(tmp);
    int offset2 = *(unsigned int *)(tmp1);
    char *value1 = &leafpointer[offset1];
    char *value2 = &leafpointer[offset2];
    //cout //<< "offset1: " //<< offset1 //<< " " //<< offset_1 //<< endl;
    //cout //<< "value1: " //<< value1 //<< " " //<< mid_off //<< endl;
    //cout //<< "value: " //<< value //<< endl;
    //cout //<< "here!!!!!!!!!!!!!!"
         //<< " " //<< mid_off //<< endl;
    if (strcmp(value1, value) < 0) {
      if (strcmp(value, value2) <
          0)  // make sure value1<=value, and there is no value2 between them
      {
        return mid_off;
      }
      //cout //<< "here!!!!!!!!!!!!!!"
           //<< " " //<< mid_off //<< endl;

      // if this comparation happened between the value and the uncompressed
      // value of the last interval, then I need to return the number of the
      // last interval.
      if (mid_off == this->string_num - 1) {
        //cout //<< "here is the place!!!" //<< endl;
        return mid_off;
      }

      return binarySearch_prefix(leafpointer, mid_off + 1, end_off, value);
    } else if (strcmp(value1, value) == 0) {
      return mid_off;
    } else if (strcmp(value, value1) < 0) {
      return start_off;

    } else {
      return binarySearch_prefix(leafpointer, start_off, mid_off - 1, value);
    }
  }
  return -1;
}

int Leaf::getString_num() { return string_num; }

void Leaf::setString_num(int number) { string_num = number; }

int Leaf::sizeLength(char *value) {
  int i = 0;
  while (value[i]) {
    i++;
  }
  return i;
}

int Leaf::prefix_len(char *value, char *value_curr) {
  int size_value;
  int size_value_curr;
  int length = 0;
  size_value = sizeLength(value);
  size_value_curr = sizeLength(value_curr);
  for (int i = 0, j = 0; i <= size_value - 1 && j <= size_value_curr - 1;
       i++, j++) {
    if (value[i] != value_curr[j]) {
      break;
    }
    length = i + 1;
  }
  return length;
}

int Leaf::compareValue(char *value_curr, char *value) {
  int compare = 0;
  compare = strcmp(value_curr, value);
  return compare;
}

string Leaf::sequentialSearch_code1(int prefix_len, int start, int end,
                                    int code) {
  // this function is used to do the sequential search based on the input code
  // the start is the location of uncompressd value, the end is the end of this
  // interval or the end of the compressed value part in this leaf.
  // the code is the one that I need to find in this leaf
  string result = "";
  string value_curr = this->pointerLeaf + start;
  int start1 = start + value_curr.length() + 1;
  string sub = value_curr.substr(0, prefix_len);
  //cout //<< "The prefix length here is " //<< prefix_len //<< endl;
  //cout //<< " the code here is " //<< code //<< endl;
  for (int m = 0; m < code; m++) {
    value_curr = this->pointerLeaf + start1 + prefixSize;
    //cout //<< value_curr //<< endl;
    start1 += prefixSize + codeSize + value_curr.length() + 1;
  }

  //cout //<< value_curr //<< endl;
  // the location of the compressed value
  result = sub + value_curr;

  return result;
}

string Leaf::sequentialSearch_code(char *leafpointer, int start, int end,
                                   int code) {
  char *value_curr = &leafpointer[start];           // the uncompressed value
  int start1 = start + sizeLength(value_curr) + 1;  // the prefix length
  char prefix_tmp[prefixSize];
  this->printStrings();
  for (int m = 0; m < prefixSize; m++) {
    prefix_tmp[m] = this->pointerLeaf[start1];
    start1++;
  }
  int curr_prefix_len = *(int *)prefix_tmp;
  //cout //<< " The prefix length here is " //<< curr_prefix_len //<< endl;
  char prefixStr[curr_prefix_len];
  strncpy(prefixStr, &leafpointer[start], curr_prefix_len);
  string str = prefixStr;  // the prefix part of the compressed string
  string str1;  // store the uncompressed part of the compressed string
  value_curr = &leafpointer[start1];  // the first compressed value
  start1 = start1 + sizeLength(value_curr) + 1;
  char tmp[codeSize];
  for (int m = 0; m < codeSize; m++) {
    tmp[m] = leafpointer[start1 + m];
  }
  int code1 = *(unsigned int *)(tmp);
  while (start1 <= end and code1 < code) {
    start1 = start1 + prefixSize + codeSize;
    value_curr = &leafpointer[start1];
    start1 = start1 + sizeLength(value_curr) + 1;
    for (int m = 0; m < codeSize; m++) {
      tmp[m] = leafpointer[start1 + m];
    }
    code1 = *(unsigned int *)(tmp);
    if (code1 > code) {
      return "";
    }
  }
  if (code == code1) {
    str1 = value_curr;
    str1 = str + str1;
    return str1;
  } else {
    return "";
  }
}

vector<int> Leaf::sequentialSearch_prefix(char *leafpointer, int start, int end,
                                          char *value) {
  vector<int> result;
  char *value_curr = &leafpointer[start];  // pointer to the value from the
                                           // start
  // the start point is the offset of this uncompressed value,
  // the end point is the next uncompressed value
  // I need to get the prefix value and rebuild the compressed value in this
  // range in order to do the prefix match first I extract the prefix from the
  // uncompressed value

  string prefix_value = value;
  int start1 = start + sizeLength(value_curr) +
               1;  // the start of the next compressed string
  //int prefix_length = prefix_len(value, value_curr);
  string value_un = value_curr;

  //cout //<< " the value here is " //<< prefix_value //<< endl;
  //cout //<< " The starting value is " //<< value_curr //<< endl;

  //int prefix_length1 = prefix_length;
  int curr_prefix_len;
  //char *value1 = &value[prefix_length];

  //cout //<< " the value apart from the prefix common part " //<< value1 //<< endl;
  // the value apart from the prefix common part
  // not reach the end and prefix length
  while (start1 < end) {
    // I need to search all the strings one by one, until I could not find the
    // value in this range as a prefix substring
    char prefix_tmp[prefixSize];
    for (int m = 0; m < prefixSize; m++) {
      prefix_tmp[m] = leafpointer[start1 + m];
      start1++;
    }
    curr_prefix_len = *(int *)prefix_tmp;
    string sub_str = value_un.substr(0, curr_prefix_len);
    //cout //<< " The substring here is " //<< sub_str //<< endl;

    //cout //<< "the curr_prefix_len is " //<< curr_prefix_len //<< endl;
    value_curr = &leafpointer[start1];  // point the uncompressed part
    start1 = start1 + sizeLength(value_curr) + 1;
    // the code of compressed
    // value
    string value_com = value_curr;
    //cout //<< "double check the value compressed here " //<< value_com //<< endl;
    sub_str.append(value_com);
    // get the uncompressed string
    //cout //<< "the sub string used to do the comparation is " //<< sub_str //<< endl;
    if (sub_str.find(prefix_value) == 0) {
      int off = start1;  // the start of the result code
      // off = off - codesize;//the end of the result code
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off + m];
      }
      int result_tmp1 = *(int *)(code_tmp);
      if (result_tmp1 != -1) {
        result.push_back(result_tmp1);
      }
    } else {
      // break;
    }
    start1 += codeSize;
    //cout //<< "start1 is " //<< start1 //<< endl;
    //cout //<< "end is " //<< end //<< endl;
  }

  if (result.size() == 0) {
    // result.push_back(-1);
    //cout //<< "no result in the place!" //<< endl;
  }

  return result;
}

int Leaf::sequentialSearch(char *leafpointer, int start, int end, char *value) {
  char *value_curr = &leafpointer[start];  // pointer to the value from the
                                           // start
  string target = value;
  int result=-1;
  int start1 = start + sizeLength(value_curr) +
               1;  // the start of the next compressed string
  int prefix_length = prefix_len(value, value_curr);
  int prefix_length1 = prefix_length;
  string value_un = value_curr;
  int curr_prefix_len;
  //char *value1 =
    //  &value[prefix_length];  // the value apart from the prefix common part
  while (start1 <= end &&
         prefix_length1 <
             target.size())  // not reach the end and prefix length
  {
    // start1++;
    char prefix_tmp[prefixSize];
    for (int m = 0; m < prefixSize; m++) {
      prefix_tmp[m] = leafpointer[start1 + m];
      start1++;
    }
    curr_prefix_len = *(int *)prefix_tmp;
    string sub_str = value_un.substr(0, curr_prefix_len);


    value_curr = &leafpointer[start1];  // point the uncompressed part

    start1 = start1 + sizeLength(value_curr) + 1;  // te code of compressed
                                                   // value
    string value_com = value_curr;
    sub_str.append(value_com);

    if(sub_str.compare(target)==0){
        int off = start1;  // the start of the result code
      // off = off - codesize;//the end of the result code
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off + m];
      }
      int result_tmp1 = *(int *)(code_tmp);
      if (result_tmp1 != -1) {
        result=result_tmp1;
      }
    } else {
      // break;
    }
    start1 += codeSize;
    //cout //<< "start1 is " //<< start1 //<< endl;
    //cout //<< "end is " //<< end //<< endl;
    }
    return result;
  }

void Leaf::printLeaf(int start, int end) {
  for (int i = start; i <= end; i++) {
    //cout //<< *(pointerLeaf + i) //<< endl;
  }
}

void Leaf::setLeaf_size(int Leaf_size) { leafSize = Leaf_size; }

int Leaf::getLeaf_size() { return leafSize; }

void Leaf::setOffset_size(int Offset_size) { offsetSize = Offset_size; }

int Leaf::getOffset_size() { return offsetSize; }

void Leaf::setCode_size(int Code_size) { codeSize = Code_size; }

int Leaf::getCode_size() { return codeSize; }

void Leaf::setPrefix_size(int Prefix_size) { prefixSize = Prefix_size; }

int Leaf::getPrefix_size() { return prefixSize; }

void Leaf::setDecode_interval(int Decode_interval) {
  decodeInterval = Decode_interval;
}

int Leaf::getDecode_interval() { return decodeInterval; }
