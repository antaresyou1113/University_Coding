#include "Leaf2.h"

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
  // cout << "empty a node" << endl;
}

string generateKey(string str1, string str2) {
  string result = "";
  char *p1 = (char *)str1.c_str();
  char *p2 = (char *)str2.c_str();
  int l1 = str1.length();
  int l2 = str2.length();
  int l = min(l1, l2);
  // cout << "the length " << l << endl;
  char p[l];
  int r = 0;
  int i = 0;
  for (i = 0; i < l; i++) {
    if (p1[i] == p2[i]) {
      p[i] = p1[i];
      // cout << "The char here " << p[i] << " " << i << endl;
    } else if (p1[i] < p2[i]) {
      p[i] = p2[i];
      // cout << i << endl;
      break;
    } else {
    }
    // cout << " the i " << i << " " << p1[i] << " " << p2[i] << endl;
  }
  // cout << "The number of result " << i << endl;
  p[i + 1] = '\0';
  result = p;

  return result;
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
      // cout << "the number of keys here: " << key_num
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
    // cout << "The keypointer is NULL " << endl;
    return -1;
  }
}

int Node::getLeafnum() {
  int result = -1;
  if (pointerNode == NULL) {
    // cout << "initialize the index node first!" << endl;
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
  // cout << "Copy the node !" << endl;
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
  // cout << "Create one node!" << endl;
}

Node::~Node() {
  delete[] pointerNode;
  // cout << "delete one node!" << endl;
}

decodingindexNode::decodingindexNode(int indexNodesize) {
  this->level_num = 0;
  this->level = 0;
  this->indexNodesize = indexNodesize;
  this->indexpointer = NULL;
  this->indexpointer = new char[this->indexNodesize];
  // cout << "Create a decoding index node!" << endl;
}

decodingindexNode::decodingindexNode(const decodingindexNode &node_tmp) {
  this->level_num = node_tmp.level_num;
  this->level = node_tmp.level;
  this->indexNodesize = node_tmp.indexNodesize;
  this->indexpointer = new char[this->indexNodesize];
  for (int i = 0; i < this->indexNodesize; i++) {
    this->indexpointer[i] = node_tmp.indexpointer[i];
  }
  // cout << "Copy the decoding index node!" << endl;
}

decodingindexNode::~decodingindexNode() {
  delete[] indexpointer;
  // cout << "Delete the decoding index node!" << endl;
}

void decodingindexNode::setLevelnum(int level_num) {
  this->level_num = level_num;
}

void decodingindexNode::setLevel(int level) { this->level = level; }

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
    // cout << "initialze the decoding index node first!" << endl;
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

encodingindexNode::encodingindexNode(int indexNodesize) {
  this->level_num = 0;
  this->level = 0;
  this->indexNodesize = indexNodesize;
  this->indexpointer = NULL;
  this->indexpointer = new char[this->indexNodesize];
  // cout << "Create an index node!" << endl;
}

encodingindexNode::encodingindexNode(const encodingindexNode &node_tmp) {
  this->level_num = node_tmp.level_num;
  this->level = node_tmp.level;
  this->indexNodesize = node_tmp.indexNodesize;
  this->indexpointer = new char[this->indexNodesize];
  for (int i = 0; i < this->indexNodesize; i++) {
    this->indexpointer[i] = node_tmp.indexpointer[i];
  }
  // cout << "Copy the encoding index node!" << endl;
}

encodingindexNode::~encodingindexNode() {
  delete[] indexpointer;
  // cout << "Delete the encoding index node!" << endl;
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
  // cout << "Insert the encoding index node based on Node object" << endl;
}

int encodingindexNode::getOffset() {
  int result = -1;
  if (indexpointer == NULL) {
    // cout << "Initialize the index node first!" << endl;
    return result;
  } else {
    result = *(int *)indexpointer;
  }
  return result;
}

int encodingindexNode::getKeynum() {
  int result = 0;
  if (indexpointer == NULL) {
    // cout << "Initialize the index node first!" << endl;
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
  // cout << "create a new index! " << endl;
}

encodingIndex::~encodingIndex() {
  delete[] index;
  // cout << "Delete the index!" << endl;
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

Tree::Tree() {
  head = tail = NULL;
  position = 0;
  // cout << "create a new tree!" << endl;
}

Tree::~Tree() {
  delete head;
  // cout << "delete a tree!" << endl;
}

Node *Tree::getNode(int position) {
  Node *p = head;
  if (p == NULL) {
    // cout << "There is no index" << endl;
  } else {
    int posi = 0;
    while (p != NULL && posi != position) {
      posi++;
      p = p->next;
    }
    if (p == NULL) {
      // cout << "There is no such index!" << endl;
      return NULL;
    } else {
      // cout << "The index has been found!" << endl;
      return p;
    }
  }
  return NULL;
}

void Tree::deleteNode(int position) {
  Node *p = head;
  Node *p1 = head;
  if (p == NULL) {
    // cout << "There is no index" << endl;
  } else {
    int posi = 1;
    while (p != NULL && posi != position) {
      posi++;
      p1 = p;
      p = p->next;
    }
    if (p == NULL) {
      // cout << "There is no such index!" << endl;
    } else {
      if (position == this->position) {
        // I need to delete the last one
        p1->next = NULL;
        p = NULL;
      } else {
        p1->next = p->next;
        p = NULL;
      }
      // cout << "Delete the node! " << position << endl;
    }
  }
}

int Tree::nodeNum() { return this->position; }

void Tree::Insert(Node &node) {
  if (head == NULL) {
    head = tail = new Node(node);
    head->next = NULL;
    tail->next = NULL;
    // cout << " The first index node inserted! " << endl;
  } else {
    Node *p = new Node(node);
    tail->next = p;
    tail = p;
    // cout << "Insert a new index node! " << endl;
    tail->next = NULL;
  }
  position++;
}

void Tree::setNode(int posi, Node &node) {
  Node *p = head;
  Node *p1 = head;
  if (p == NULL) {
    // cout << "The list is empty" << endl;
  } else {
    int posi1 = 1;
    while (p != NULL && posi1 != posi) {
      posi1++;
      p1 = p;
      p = p->next;
    }
    if (p == NULL) {
      // cout << "There is no such node in that position" << endl;
    } else {
      Node *q = new Node(node);
      p1->next = q;
      q->next = p->next;
      p = NULL;
    }
  }
}

void Leaf::printStrings() {
  // in this method, I need to print all the strings
  vector<string> result;
  vector<int> coderesult;
  string string_tmp;
  // make sure the number of strings in this leaf is larger than the number of
  // range
  int num_left = this->string_num;
  // cout << " string num is " << string_num << endl;
  char offset_tmp[offsetSize];
  int i;
  for (i = 0; num_left - i >= 1; i++) {
    for (int j = 0; j < offsetSize; j++) {
      offset_tmp[j] = pointerLeaf[leafSize - 1 + j - offsetSize -
                                  i * (offsetSize + codeSize)];
    }
    int test = num_left - i * decodeInterval;
    // cout << " decodeInterval= " << decodeInterval << " test " << test <<
    // endl;
    int offset_tmp1 = *(int *)offset_tmp;
    // push back the uncompressed value
    string_tmp = this->pointerLeaf + offset_tmp1;
    result.push_back(string_tmp);  // push the uncompresse value into the vector
    // then I need to loop all the compressed values in this range
    // the starting point of the first compressed value
    int offset_tmp2 = offset_tmp1 + string_tmp.length() +
                      1;  // the start of the compressed value part
    // cout << "the start of the compressed value is " << offset_tmp2 << endl;
    char prefix_tmp[prefixSize];
    for (int j = 0; j < prefixSize; j++) {
      prefix_tmp[j] = this->pointerLeaf[offset_tmp2 + j];
    }
    int prefix_tmp1 = *(int *)prefix_tmp;
    // cout << "prefix here is " << prefix_tmp1 << endl;
    // cout << "offset_tmp2 here is " << offset_tmp2 << endl;
    char code_tmp[codeSize];
    int code_tmp1;
    for (int n = 0; n < codeSize; n++) {
      code_tmp[n] = this->pointerLeaf[leafSize - 1 + n -
                                      (i + 1) * (offsetSize + codeSize)];
    }
    code_tmp1 = *(int *)code_tmp;
    coderesult.push_back(code_tmp1);  // push the code into the vector
    // cout << " The uncompressed string value is " << string_tmp
    //<< " the code value is " << code_tmp1 << endl;
    // cout << "the offset of the uncompressed value is: " << offset_tmp1
    //<< " the prefix of the compressed value is: " << prefix_tmp1 << endl;
    string sub = string_tmp.substr(0, prefix_tmp1);
    // cout << "The sub string is " << sub << endl;
    for (int m = 0; (m < decodeInterval - 1) &&
                    (m < (this->value_num - i * decodeInterval) - 1);
         m++) {
      offset_tmp2 += prefixSize;
      // string string_tmp1 = "";
      string_tmp = this->pointerLeaf + offset_tmp2;
      // cout << " The compressed string value is " << string_tmp << endl;
      string_tmp = sub + string_tmp;
      // cout << " The compressed string value is " << string_tmp << " m " << m
      //<< endl;
      result.push_back(string_tmp);
      // cout << " the offset in compressed part is " << offset_tmp2 << endl;
      offset_tmp2 += string_tmp.length() + 1 - sub.length();
      for (int n = 0; n < codeSize; n++) {
        code_tmp[n] = this->pointerLeaf[offset_tmp2 + n];
      }
      code_tmp1 = *(int *)code_tmp;
      coderesult.push_back(code_tmp1);
      // cout << " The compressed value code is " << code_tmp1 << endl;
      offset_tmp2 += codeSize;
    }
    // cout << "------------------------------------" << endl;
  }
  // if the left num_left is less than the num_range
  // cout << "num value is " << value_num << endl;
  /**
  int num_left1 = this->value_num - i * decodeInterval;
  //cout << "num left is " << num_left1 << endl;
  // i++;
  //cout << " the i here is " << i << endl;
  char offset_tmp3[offsetSize];
  for (int j = 0; j < offsetSize; j++) {
    offset_tmp3[j] = pointerLeaf[leafSize - 1 + j - offsetSize -
                                 i * (offsetSize + codeSize)];
  }
  int offset_tmp1 = *(int *)offset_tmp3;
  //cout << "offset_tmp4 here is " << offset_tmp1 << endl;
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
  //cout << " The left uncompressed string and code are " << string_tmp << " "
       //<< code_tmp1 << endl;

  //cout << "-----------here------------" << endl;
  //cout << "num left " << num_left1 << endl;
  if (num_left1 > 1) {
    int offset_tmp2 = offset_tmp1 + string_tmp.length() + 1;
    //cout << " offfset_tmp2 " << offset_tmp2 << endl;
    char prefix_tmp[prefixSize];
    for (int j = 0; j < prefixSize; j++) {
      prefix_tmp[j] = this->pointerLeaf[offset_tmp2 + j];
    }
    int prefix_tmp1 = *(int *)prefix_tmp;
    string sub = string_tmp.substr(0, prefix_tmp1);
    cout << " sub here is " << sub << " prefix length " << prefix_tmp1 << endl;
    for (int m = 0; m < num_left1 - 1; m++) {
      offset_tmp2 += prefixSize;
      string_tmp = this->pointerLeaf + offset_tmp2;
      //cout << " The compressed string value is " << string_tmp << endl;
      string_tmp = sub + string_tmp;
      //cout << " The compressed string value is " << string_tmp << endl;
      result.push_back(string_tmp);
      offset_tmp2 += string_tmp.length() + 1 - sub.length();
      for (int n = 0; n < codeSize; n++) {
        code_tmp[n] = this->pointerLeaf[offset_tmp2 + n];
      }
      code_tmp1 = *(int *)code_tmp;
      coderesult.push_back(code_tmp1);
      //cout << " The compressed value code is " << code_tmp1 << endl;
      offset_tmp2 += codeSize;
    }
  }
**/
  // the results of strings and codes are in the vectors now!
  // print them all!
  for (auto array : result) {
    // cout << array << endl;
  }
  for (auto code : coderesult) {
    // cout << code << endl;
  }
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
  int offset_small = *(int *)offset_tmp;
  result = this->pointerLeaf;

  // cout << result << " The smallest value is " << endl;

  return result;
}

string Leaf::largestValue() {
  string result = "";
  int offset_vec = offsetSize + codeSize;
  char offset_tmp[offsetSize];
  // int num_vec = (int)ceil((double)string_num / (double)decodeInterval);
  // cout << "number of vectors: " << num_vec << endl;
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
    // cout << "the result is " << result << " " << str1 << " " << str2 << " "
    //<< str3 << endl;
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
  // cout << "Copy the leaf !" << endl;
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
  // cout << "create the Leaf class" << endl;
}

Leaf::~Leaf() {
  delete[] pointerLeaf;
  // cout << "delete the Leaf class" << endl;
}

int Leaves::getLeavesnum() { return this->position; }

int Leaves::decodingIndexcreation() {
  if (this->head != NULL && this->position > 0) {
    vector<int> level_tmp;
    vector<decodingindexNode> index_tmp;
    int leaf_num = this->position;
    // cout << "leaf number is " << leaf_num << endl;
    decodingindexNode decode_node;
    int key_num = (decode_node.nodeSize() - 2 * 4) / 4;
    cout << "key num" << key_num << endl;
    // int key_num = 2;
    // leaf_num--;
    int decode_num = 0;  // the number of nodes used for decoding index building
    for (int i = 0; leaf_num > 1; i++) {
      leaf_num = (int)ceil((double)(leaf_num - 1) / (double)(key_num));
      level_tmp.push_back(leaf_num);
      // cout << "leaf number is " << leaf_num << endl;
      decode_num += leaf_num;
    }
    // cout << "the size of the level " << level_tmp.size()
    //<< " The nodes in the index " << decode_num << endl;
    // start to build the index from the bottom
    // I have already know the nodes in each level and the number of level
    // I need to get the first code of the value in each leaf and use them as
    // the key when I build the level above, I need to extract the first key,
    // starting from the second child in the lower level.
    leaf_num = 1;
    for (int i = 0; i < level_tmp[0]; i++) {
      decode_node.setOffset(leaf_num - 1);
      decode_node.setLevel(0);
      decode_node.setLevelnum(level_tmp[0]);
      decode_node.setNodesize(0);

      for (int j = 0; j < key_num; j++) {
        int code_tmp = this->getLeaf(leaf_num)->smallestCode();
        decode_node.insertKey(code_tmp);
        // cout << "the code inserted " << code_tmp << endl;
        leaf_num++;
        if (leaf_num == this->position) {
          break;
        }
      }
      // if (leaf_num == this->position) {
      // break;
      //}
      index_tmp.push_back(decode_node);
      // cout << "the code here is " << decode_node.smallestKey() << endl;
      // cout << "the level is " << decode_node.getLevel() << endl;
      // cout << " the offset here is " << decode_node.getOffset() << endl;
    }
    // the lowest level is finished, then I need to build the levels above
    leaf_num = 1;
    for (int i = 1; i < level_tmp.size(); i++) {
      int leaf_num1 = 1;
      for (int j = 0; j < level_tmp[i]; j++) {
        decode_node.setOffset(leaf_num1 - 1 + level_tmp[i]);
        decode_node.setLevel(i);
        decode_node.setLevelnum(level_tmp[i]);
        decode_node.setNodesize(0);
        for (int m = 0; m < key_num; m++) {
          int code_tmp = index_tmp[leaf_num].smallestKey();
          // cout << "HERE " << code_tmp << endl;
          decode_node.insertKey(code_tmp);
          leaf_num++;
          leaf_num1++;
          // cout << "Leaf number " << leaf_num << endl;
          if (leaf_num == level_tmp[i - 1]) {
            break;
          }
        }

        index_tmp.push_back(decode_node);
        // cout << "the code here is " << decode_node.smallestKey() << endl;
        // cout << "the level is " << decode_node.getLevel() << endl;
        // cout << " the offset here is " << decode_node.getOffset() << endl;
      }
      leaf_num++;
      // cout << "Herere" << endl;
    }
    // now all the nodes are ready, I need to put them into the decode_index in
    // the right order
    int count = 0;
    for (int i = level_tmp.size() - 1; i >= 0; i--) {
      count += level_tmp[i];

      for (int j = 0; j < level_tmp[i]; j++) {
        leaf_num = decode_num - count + j;
        this->index_decode.push_back(index_tmp[leaf_num]);
      }
    }

    // do some tests to see the result, it can pass

    for (int i = 0; i < this->index_decode.size(); i++) {
      for (int j = 0; j < this->index_decode[i].getKeynum(); j++) {
        int code_tmp = this->index_decode[i].getKey(j + 1);
        int offset = this->index_decode[i].getOffset();
        // cout << "The code here is " << code_tmp << " The offset here is "
        //<< offset << endl;
      }
    }
    // the index has been built successfully

    return 0;
  }
  return -1;
}

int Leaves::encodingIndexcreation() {
  if (this->head != NULL && this->position > 0) {
    Tree *tree1 = new Tree;
    int offset = 0;
    int keys_num = 0;
    int test = 0;       // used to see whether the node is full
    int level_num = 0;  // the number of nodes in one level
    int level = 0;      // the level of the nodes, starting from 0.
    Node *node_tmp = new Node;
    for (int i = 0, j = 1; j < position; i++, j++) {
      Leaf *leaf1 = new Leaf;
      Leaf *leaf2 = new Leaf;
      leaf1 = this->getLeaf(i);
      leaf2 = this->getLeaf(j);
      // get the largest value in the lower leaf and the smallest in the larger
      // leaf
      string smaller = leaf1->largestValue();
      string larger = leaf2->smallestValue();
      string key = generateKey(smaller, larger);
      // cout << "ssssssssssssssssssssssssssssssssss key " << key << endl;
      // cout << "smaller " << smaller << " larger " << larger << endl;
      // now the key has been generated, create a node in order to store the key
      // value
      node_tmp->insertLeafnum(offset);
      test = node_tmp->insertKeys(key);
      node_tmp->setLevel(level);
      if (test == -1) {
        level_num++;
        node_tmp->setLevelnum(level_num);
        tree1->Insert(*node_tmp);
        // cout << "        ddddddddddd         nodes number" <<
        // tree1->nodeNum()
        //<< endl;
        offset += node_tmp->getKeynum();
        node_tmp->emptyNode();
        node_tmp->insertLeafnum(offset);
        test = node_tmp->insertKeys(key);
        if (test == -1) {
          // cout << "The node is too small for the key! " << endl;
          return -1;
        }
        if (j == position - 1) {
          level_num++;
          node_tmp->setLevelnum(level_num);
          tree1->Insert(*node_tmp);
        }
      } else if (j == position - 1) {
        level_num++;
        node_tmp->setLevelnum(level_num);
        tree1->Insert(*node_tmp);
        // cout << "                 nodes number" << tree1->nodeNum() << endl;
      }
    }
    // node_tmp = tree1->getNode(i);
    // The part above is finished and it good. now I need to think abot how to
    // implement the levels on top of it.
    Node *node_tmp1 = new Node;
    // Node node_tmp2;
    // node_tmp->emptyNode();
    int offset1 = 0;
    // cout << level_num << " The level number " << endl;
    int level_num1 =
        level_num;  // used to remember the number of nodes in one deeper level
    // cout << " The number of nodes in the former level  " << level_num1 <<
    // endl;
    int num_nodes = tree1->nodeNum();
    int num_nodes1 = num_nodes;
    // cout << " current last level number is in level_num1 " << level_num1
    //<< " current node number " << num_nodes << endl;
    // test
    //
    for (int i = num_nodes - level_num1 + 1; i < num_nodes; i++) {
      // cout << "                The i here is " << i << " " << num_nodes << "
      // "
      //<< level_num1 << endl;
      node_tmp1 = tree1->getNode(i);
      string key = node_tmp1->smallestKey();
      // cout << " The key here is " << key
      //<< tree1->getNode(num_nodes - 1)->smallestKey() << endl;
    }

    while (level_num > 1) {
      // I need to create the levels above
      Node node_tmp2;
      level++;
      level_num = 0;  // the number of nodes in this level
      offset1 = 0;    // used to recalculate the offset for nodes in this level
      offset = 0;  // used to calculate the offset for the nodes in this level
      for (int i = num_nodes - level_num1 + 1; i < num_nodes; i++) {
        // cout << "                The i here is " << i << " " << num_nodes <<
        // " "
        //<< level_num1 << endl;
        node_tmp1 = tree1->getNode(i);
        string key = node_tmp1->smallestKey();
        // cout << " The key here is kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << key <<
        // " "
        //<< tree1->getNode(num_nodes - 1)->smallestKey() << endl;
        node_tmp2.insertLeafnum(offset);
        node_tmp2.setLevel(level);
        test = node_tmp2.insertKeys(
            tree1->getNode(i)->smallestKey());  // try to insert the key into
                                                // the node

        if (test == -1) {
          // if the node is full, insert the current node and insert the key in
          // a new nodei

          level_num++;  // this node has been inserted, so there is one more
                        // node in this level
          // cout << "level number here is " << level_num << endl;
          node_tmp2.setLevelnum(level_num);
          tree1->Insert(node_tmp2);
          // cout<<" the number of nodes here "<<tree1->nodeNum()<<endl;
          offset += node_tmp2.getKeynum();  // offset calculation for the next
                                            // node in the same level
          node_tmp2.insertKeynum(0);
          node_tmp2.emptyNode();
          node_tmp2.insertLeafnum(offset);
          test =
              node_tmp2.insertKeys(key);  // insert the key into this new node
          if (test == -1) {
            // cout << " The key is too small! " << key << endl;
          } else if (i == num_nodes - 1) {
            level_num++;
            node_tmp2.setLevel(level);
            node_tmp2.setLevelnum(level_num);
            tree1->Insert(node_tmp2);
          }

        } else if (i == num_nodes - 1) {
          // if i reaches the last key in this level,
          // we need to push it into a node anyway
          level_num++;  // one more node in this level
          // cout << "             The position of node here is " << level_num +
          // i
          //<< endl;
          if (level_num == 1) {
            offset = 0;
            node_tmp2.insertLeafnum(offset);
          }
          node_tmp2.setLevelnum(level_num);
          tree1->Insert(node_tmp2);
          // cout << " the number of nodes here " << tree1->nodeNum() << endl;
        }
      }
      // test more
      for (int i = 0; i < (tree1->nodeNum()); i++) {
        node_tmp = tree1->getNode(i);
        for (int m = 1; m <= node_tmp->getKeynum(); m++) {
          string str_key = node_tmp->getKey(m);
          int offset_leaf = node_tmp->getLeafnum();
          int level_test = node_tmp->getLevel();
          int level_numtest = node_tmp->getLevelnum();
          // cout << " some info " << str_key << " " << offset_leaf << " level "
          //<< level_test << " level number " << level_numtest
          //<< " The offset " << node_tmp->getLeafnum() << endl;
        }
      }
      // cout << "-----------------------------------------------------" <<
      // endl;
      //
      level_num1 = level_num;  // store the number of nodes in this level
      num_nodes = tree1->nodeNum();
      // cout << "Node number in level " << level << " is " << level_num1 <<
      // endl;
      for (int n = num_nodes - level_num1; n < num_nodes; n++) {
        // cout << "n in the for loop is " << n << endl;
        int offset1 = tree1->getNode(n)->getLeafnum();
        // cout << " The number of n is              " << n << endl;
        // cout << "offset1         " << offset1 << " Level is " << level <<
        // endl;
        offset1 += level_num1;
        // cout << "offset2        " << offset1 << " Level is " << level <<
        // endl;
        tree1->getNode(n)->insertLeafnum(offset1);
        // tree1->setNode(n, *node_tmp);
      }
      // more test!!!!
      /***    for (int i = 0; i < (tree1->nodeNum()); i++) {
            node_tmp = tree1->getNode(i);
            for (int m = 1; m <= node_tmp->getKeynum(); m++) {
              string str_key = node_tmp->getKey(m);
              int offset_leaf = node_tmp->getLeafnum();
              int level_test = node_tmp->getLevel();
              int level_numtest = node_tmp->getLevelnum();
              cout << " some info " << str_key << " " << offset_leaf << " level
         "
                   << level_test << " level number " << level_numtest
                   << " The offset " << node_tmp->getLeafnum() << endl;
            }
          }*/
      //
    }
    num_nodes = tree1->nodeNum();
    // cout << "Finish the while loop " << num_nodes << endl;
    this->encodingpointer = new encodingIndex(num_nodes);
    encodingindexNode *indexnode_tmp = new encodingindexNode;
    int levelnum = tree1->getNode(num_nodes - 1)->getLevelnum();
    int nodes_left = num_nodes;
    int nodes_inserted = 0;
    int j = 0;
    // cout << "NODES LEFT" << nodes_left << endl;
    while (nodes_left > 0) {
      levelnum = tree1->getNode(nodes_left - 1)->getLevelnum();
      // cout << "here!!!!!!!" << endl;
      nodes_left -= levelnum;
      for (int i = nodes_left; i < nodes_left + levelnum; i++, j++) {
        node_tmp = tree1->getNode(i);
        indexnode_tmp->insertNode(*node_tmp);
        // then I need to adjust the level_num, so it is the number of nodes in
        // this level
        indexnode_tmp->insertLevelnum(levelnum);
        encodingindexNode indexnode_tmp1 = *indexnode_tmp;
        fullindex.push_back(indexnode_tmp1);
        this->encodingpointer->insertIndexnode(j, *indexnode_tmp);
      }
    }
    for (int t = 0; t < tree1->nodeNum(); t++) {
      node_tmp = tree1->getNode(t);
      for (int m = 1; m <= node_tmp->getKeynum(); m++) {
        string str_key = node_tmp->getKey(m);
        int offset_leaf = node_tmp->getLeafnum();
        int level_test = node_tmp->getLevel();
        int level_numtest = node_tmp->getLevelnum();
        // cout << " some info " << str_key << " " << offset_leaf << " level "
        //<< level_test << " level number " << level_numtest << endl;
      }
    }
    delete node_tmp;
    delete node_tmp1;
    delete tree1;
    return 0;
  }

  return -1;
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
  // cout << "column name: " << colname << endl;
  //}
  //}

  // read the data, line by line
  while (getline(myFile, line)) {
    // Create a string stream of the current line
    // stringstream ss(line);
    result.push_back(line);
    // cout << "line value: " << line << endl;
  }

  myFile.close();
  return result;
}

map<string, int> strs1;
vector<string> strings;
vector<int> codes;
vector<string> strings1;
vector<int> codes1;
void Dictionary(vector<string> a) {
  string tmp = "";
  int size = a.size();
  vector<string> strs_tmp;
  for (int i = 0; i < size; i++) {
    tmp = a[i];
    strs1.insert(pair<string, int>(tmp, i));
  }
  int m = 0;
  for (map<string, int>::iterator it = strs1.begin(); it != strs1.end(); ++it) {
    it->second = m;
    m++;
    tmp = it->first;

    strings.push_back(tmp);
    // cout << " The string to be inserted into the vector " << tmp << endl;
  }
}

void decodingDic(vector<int> a) {
  auto start_time = chrono::steady_clock::now();
  int size = a.size();
  int tmp;
  for (int i = 0; i < size; i++) {
    for (map<string, int>::iterator it = strs1.begin(); it != strs1.end();
         ++it) {
      tmp = it->second;
      if (tmp == a[i]) {
        strings1.push_back(it->first);
        //cout << it->first << endl;
      }
    }
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Naive Dictionary decoding task has finished: " << ms
       << " ms consumed" << endl;
  cout << "size is: " << strings1.size() << endl;
}

void encodingDic(vector<string> a) {
  auto start_time = chrono::steady_clock::now();
  int size = a.size();
  string tmp = "";
  for (int i = 0; i < size; i++) {
    for (map<string, int>::iterator it = strs1.begin(); it != strs1.end();
         ++it) {
      tmp = it->first;
      if (tmp.find(a[i]) == 0) {
        codes.push_back(it->second);
        // cout<<it->second<<"encoding result"<<endl;
      }
    }
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Naive Dictionary Encoding task has finished: " << ms
       << " ms consumed" << endl;
  cout << "size is: " << codes.size() << endl;
}

vector<string> alphabaticallySort(vector<string> a) {
  map<string, int> strs;
  string tmp = "";
  int size = a.size();
  // cout << " The size of the input vector a: " << size << endl;
  vector<string> strs_tmp;
  for (int i = 0; i < size; i++) {
    tmp = a[i];
    // cout << " The string from the file is " << tmp << endl;
    strs.insert(pair<string, int>(tmp, 1));
  }
  // cout << " The size of the map is " << strs.size() << endl;
  for (map<string, int>::iterator it = strs.begin(); it != strs.end(); ++it) {
    tmp = it->first;
    // cout << " The string to be inserted into the vector " << tmp << endl;
    strs_tmp.push_back(tmp);
  }

  // sort(strs_tmp.begin(), strs_tmp.end(), mycomp);
  return strs_tmp;
}

int sizeLength(char *value) {
  int i = 0;
  while (value[i]) {
    i++;
  }
  return i;
}

int prefix_len(char *value, char *value_curr) {
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

string Leaves::lookupCode(int code) {
  string result = "";
  Leaf *leaf_tmp = this->getLeaf(0);
  for (int i = 0; leaf_tmp != NULL; i++) {
    result = leaf_tmp->bulkLookup_code(leaf_tmp->pointerLeaf, code);
    if (result != "") {
      break;
    }
    leaf_tmp = this->getLeaf(i + 1);
  }
  return result;
}

string Leaves::lookupCode_index(int code) {
  string result = "";
  vector<decodingindexNode> test_vec1 = this->Getindex_decode();
  int offset_tmp = 0;
  int offset_tmp1 = offset_tmp;
  int last_key = test_vec1[0].getKeynum();
  int key_tmp = test_vec1[0].getKey(last_key);
  int key_tmp1 = 0;
  int key_num = 0;
  int level_tmp = test_vec1[0].getLevel();
  int break_point = 0;
  int level_start = 0;
  int levelnum_count = 0;
  int levelnum_count1 = 0;
  int leaf_num = 0;

  // cout << "the input code is " << code << endl;
  while (level_tmp >= 0) {
    offset_tmp1 = offset_tmp;
    // cout << "The information here: "
    //<< " level: " << level_tmp << " offset_tmp " << offset_tmp
    //<< " The key here " << test_vec1[offset_tmp].getKey(1) << endl;
    levelnum_count1 = levelnum_count;
    levelnum_count += test_vec1[offset_tmp].getLevelnum();
    // the number of the  nodes until this level
    for (int i = level_start, m = 0; i < test_vec1[offset_tmp].getLevelnum();
         i++, m++) {
      // all the nodes in the same level, in order to find the right position
      offset_tmp1 += m;
      for (int j = 1; j <= test_vec1[offset_tmp1].getKeynum(); j++) {
        key_tmp = test_vec1[offset_tmp1].getKey(j);
        // cout << " the key_tmp here is " << key_tmp << endl;
        if (i == 0 && j == 1 && (code < key_tmp)) {
          offset_tmp = test_vec1[offset_tmp1].getOffset() + levelnum_count1;
          // cout << " The offset stored in this node is "
          //<< test_vec1[offset_tmp1].getOffset();
          // cout << " The level number is " << levelnum_count1 << endl;
          // cout << " the offset here is " << offset_tmp << endl;
          break_point = 1;
          level_start = 0;  // starting at the beginning of the lower level
          if (level_tmp == 0) {
            leaf_num = test_vec1[offset_tmp1].getOffset() + j - 1;
          }
          break;
        } else if (j == test_vec1[offset_tmp1].getKeynum() &&
                   i == test_vec1[offset_tmp].getLevelnum() - 1 &&
                   code >= key_tmp) {
          offset_tmp = test_vec1[offset_tmp1].getOffset() + j + levelnum_count1;
          // cout << " The offset stored in this node is "
          //<< test_vec1[offset_tmp1].getOffset();
          // cout << " The level number is " << levelnum_count1 << endl;
          // cout << " the offset here is " << offset_tmp << endl;
          break_point = 1;
          level_start = test_vec1[offset_tmp].getLevelnum() - 1;
          if (level_tmp == 0) {
            leaf_num = test_vec1[offset_tmp1].getOffset() + j;
          }
          // locate to the last node of the lower level
          break;

        } else {
          if (code < key_tmp) {
            offset_tmp =
                test_vec1[offset_tmp1].getOffset() + j - 1 + levelnum_count1;
            // cout << " The offset stored in this node is "
            //<< test_vec1[offset_tmp1].getOffset();
            // cout << " The level number is " << levelnum_count1 << endl;
            // cout << " the offset here is " << offset_tmp << endl;
            level_start = offset_tmp - levelnum_count;
            break_point = 1;
            if (level_tmp == 0) {
              leaf_num = test_vec1[offset_tmp1].getOffset() + j - 1;
            }
            break;
          }
        }
      }

      if (break_point == 1) {
        break_point = 0;
        break;
      }
    }
    level_tmp--;
  }
  // cout << " The leaf number here is: " << leaf_num << endl;
  result = this->getLeaf(leaf_num)->bulkLookup_code(
      this->getLeaf(leaf_num)->pointerLeaf, code);

  return result;
}

vector<int> Leaves::lookUpIndex(char *value, int prefix_flag) {
  vector<encodingindexNode> test_vec1 = this->Getfullindex();
  for (int i = 0; i < test_vec1.size(); i++) {
    int node_size = test_vec1[i].getKeynum();
    for (int j = 1; j <= node_size; j++) {
      string key_index = test_vec1[i].getKey(j);
      int offset_index = test_vec1[i].getOffset();
      int levelnum = test_vec1[i].getLevelnum();
      int level = test_vec1[i].getLevel();
      // cout << " The offset of the node is: " << offset_index
      //<< " The key of the node: " << key_index << " The level number is "
      //<< levelnum << " The level is " << level << endl;
    }
  }

  vector<int> result;
  int offset_tmp = 0;
  int offset_tmp1 = offset_tmp;
  int lastkey = test_vec1[0].getKeynum();
  string key_tmp = test_vec1[0].getKey(lastkey);
  string key_tmp1 = "";
  string key_target = value;
  int key_num = 0;
  int level_tmp = test_vec1[0].getLevel();
  int break_point = 0;
  int level_start = 0;  // the starting offset of the one level
  int levelnum_count = 0;
  // used to cound the level_num, for the calculation of level start
  int levelnum_count1 = 0;
  // used to store the levels before the start of this level.

  // the break_point is used to break from the nodes loop, meaning that the
  // right node has been found in this level, and I have the offset in order
  // to reach the next level. encodingindexNode indexnode_tmp; indexnode_tmp =
  // test_vec1[offset_tmp1];
  int leaf_num = 0;  // used to store the leaf number
  // cout << "The input value here is " << key_target << endl;

  while (level_tmp >= 0) {
    // start the loop in one level, starting from the level 2
    offset_tmp1 = offset_tmp;
    // cout << "The information here: "
    //<< " level: " << level_tmp << " offset_tmp " << offset_tmp
    //<< " The key here " << test_vec1[offset_tmp].getKey(1) << endl;
    levelnum_count1 = levelnum_count;
    levelnum_count += test_vec1[offset_tmp].getLevelnum();

    // the number of the  nodes until this level
    for (int i = level_start, m = 0; i < test_vec1[offset_tmp].getLevelnum();
         i++, m++) {
      // all the nodes in the same level, in order to find the right position
      offset_tmp1 += m;
      // indexnode_tmp = test_vec1[offset_tmp1];
      // offset_tmp1 used to locate the node in this level
      // offset_tmp is used to locate the first node of this level.
      // so the level_num is extracted from the fullindex[offset_tmp]
      // the sequence of the node is i+1
      for (int j = 1; j <= test_vec1[offset_tmp1].getKeynum(); j++) {
        // loop the key in each node
        // where the comparation happens
        // first store the key in i position
        key_tmp = test_vec1[offset_tmp1].getKey(j);
        // cout << " the key_tmp here is " << key_tmp << endl;
        // if the first value in this level is larger than the target value,
        // then I will reach the next level
        if (i == 0 && j == 1 && (key_target.compare(key_tmp) < 0)) {
          offset_tmp = test_vec1[offset_tmp1].getOffset() + levelnum_count1;
          // cout << " The offset stored in this node is "
          //<< test_vec1[offset_tmp1].getOffset();
          // cout << " The level number is " << levelnum_count1 << endl;
          // cout << " the offset here is " << offset_tmp << endl;
          break_point = 1;
          level_start = 0;  // starting at the beginning of the lower level
          if (level_tmp == 0) {
            leaf_num = test_vec1[offset_tmp1].getOffset() + j - 1;
          }
          break;
        }
        // if the last value of the node in this level is less than the value
        // here, jump to the last node of the next level
        else if (j == test_vec1[offset_tmp1].getKeynum() &&
                 i == test_vec1[offset_tmp].getLevelnum() - 1 &&
                 key_target.compare(key_tmp) >= 0) {
          offset_tmp = test_vec1[offset_tmp1].getOffset() + j + levelnum_count1;
          // cout << " The offset stored in this node is "
          //<< test_vec1[offset_tmp1].getOffset();
          // cout << " The level number is " << levelnum_count1 << endl;
          // cout << " the offset here is " << offset_tmp << endl;
          break_point = 1;
          level_start = test_vec1[offset_tmp].getLevelnum() - 1;
          if (level_tmp == 0) {
            if (key_target.compare(key_tmp) == 0) {
              leaf_num = test_vec1[offset_tmp1].getOffset() + j - 1;
            } else {
              leaf_num = test_vec1[offset_tmp1].getOffset() + j;
            }
          }
          // locate to the last node of the lower level
          break;
        } else {
          // but I find that I just need to find the key that is lager than
          // the target key once I find such a key, I will get the offset and
          // then end the loop in this level and jump to the lower level.
          if (key_target.compare(key_tmp) <= 0) {
            // here we need to think about == situation, once the result is
            // equal, I need to start from the former leaf
            offset_tmp =
                test_vec1[offset_tmp1].getOffset() + j - 1 + levelnum_count1;
            // cout << " The offset stored in this node is "
            //<< test_vec1[offset_tmp1].getOffset();
            // cout << " The level number is " << levelnum_count1 << endl;
            // cout << " the offset here is " << offset_tmp << endl;
            level_start = offset_tmp - levelnum_count;
            break_point = 1;
            if (level_tmp == 0) {
              leaf_num = test_vec1[offset_tmp1].getOffset() + j - 1;
            }
            break;
          }
        }
      }
      // if I get the right node, jump out of the loop here.
      if (break_point == 1) {
        break_point = 0;
        break;
      }
    }

    // then I come to the next level and I would like to decrease the level
    level_tmp--;
    // levelnum_count += fullindex[offset_tmp].getLevelnum();
  }

  if (leaf_num > 0) {
    // cout << "try to change the leaf num here" << endl;
    string smallest = this->getLeaf(leaf_num - 1)->smallestValue();
    string largest = this->getLeaf(leaf_num)->smallestValue();
    // cout << smallest << " " << largest << endl;
    if (smallest.compare(key_target) < 0 && key_target.compare(largest) < 0) {
      leaf_num--;
    }
  }
  // cout << " The leaf number here is: " << leaf_num << endl;

  if (prefix_flag == 0) {
    int result_tmp = this->getLeaf(leaf_num)->bulkLookup(
        this->getLeaf(leaf_num)->pointerLeaf, value);
    result.push_back(result_tmp);
  }

  else {
    // we need to do the prefix match here
    //
    result = this->getLeaf(leaf_num)->bulkLookup_prefix(
        this->getLeaf(leaf_num)->pointerLeaf, value);
    int length = sizeLength(value);
    leaf_num++;
    if (leaf_num < this->getLeavesnum()) {
      string next_leaf = (this->getLeaf(leaf_num))->smallestValue();

      string prefix_tmp = value;
      while (next_leaf.find(prefix_tmp) == 0 &&
             leaf_num < this->getLeavesnum()) {
        // cout << "Here!1111111111111111111111111111111111111111" << endl;
        vector<int> result_tmp = this->getLeaf(leaf_num)->bulkLookup_prefix(
            this->getLeaf(leaf_num)->pointerLeaf, value);
        // leaf_num++;
        // next_leaf = this->getLeaf(leaf_num)->smallestValue();
        for (int i = 0; i < result_tmp.size(); i++) {
          if (result_tmp[i] != -1) {
            result.push_back(result_tmp[i]);
          }
        }
        leaf_num++;
        if (leaf_num < this->getLeavesnum()) {
          next_leaf = (this->getLeaf(leaf_num))->smallestValue();
        } else {
          break;
        }
      }
    }
  }

  return result;
}

int Leaves::lookUp(char *value) {
  Leaf *leaf_tmp = this->getLeaf(0);
  int result = -1;
  for (int i = 0; leaf_tmp != NULL; i++) {
    result = leaf_tmp->bulkLookup(leaf_tmp->pointerLeaf, value);
    if (result != -1) {
      break;
    }
    // cout<<"Here!"<<endl;
    leaf_tmp = this->getLeaf(i + 1);
  }
  return result;
}

int Leaves::bulkLoadSuffix(vector<string> strs) { return 0; }

int Leaves::bulkLoad(vector<string> strs) {
  // build some files to check different parts of the component
  // the order
  // the single leaf

  // change the order
  // have more strings, try to limit the input size.

  // add all the strings into a vector
  // vector<string> strs;
  // for (int j = 0; str[j] != NULL && *str[j] != '\0'; j++) {
  //}

  // for (int j = 0; j < strs.size(); j++) {
  // cout << strs[j] << " the vector string in the load method: " << j <<
  // endl;
  //}
  //
  // the key point of this function is to make sure that the size of the values
  // inserted is less than the leaf size
  strs = alphabaticallySort(strs);
  int size = strs.size();
  // cout << "the number of strings " << size << endl;

  // generate an array of pointers to point to all the strings
  // now I have all the strings prepared
  char *value[size];
  char *value1[size];

  for (int j = 0; j < size; j++) {
    const char *cstr = strs[j].c_str();
    value[j] = (char *)cstr;
    value1[j] = (char *)cstr;
  }
  // store all the uncompressed strings
  // create a tmp_leaf to make sure the data inserted is less than the
  // leafSize
  Leaf leaf_tmp;

  // calculate the number of offset vectors, which is also the number of
  // uncompressed data
  int off_vector = ceil((double)size / (double)leaf_tmp.getDecode_interval());
  // cout << "the number of offset vectors is: " << off_vector << endl;
  int prefix_length[off_vector];

  char *value_uncompressed[off_vector];

  int interval = leaf_tmp.getDecode_interval();
  int codeSize = leaf_tmp.getCode_size();
  int leafSize = leaf_tmp.getLeaf_size();
  // cout<<leafSize<<endl;
  int offsetSize = leaf_tmp.getOffset_size();
  int prefixSize = leaf_tmp.getPrefix_size();
  // move all the uncompressed data in here
  for (int j = 0; j < off_vector; j++) {
    value_uncompressed[j] = value[interval * j];
  }

  // calculate and store the prefix length
  for (int j = 0; j < off_vector; j++) {
    // there need to have compressed value, else I only need to consider
    // compressed data
    if (interval > 1) {
      prefix_length[j] =
          prefix_len(value_uncompressed[j], value[(interval * j + 1)]);
      // the initial number is the first value after the uncompressed value
      for (int t = 2; t < interval && interval * j + t < size; t++) {
        int prefix_length1 =
            prefix_len(value_uncompressed[j], value[interval * j + t]);
        // make sure I choose the minimum value as the prefix
        if (prefix_length1 < prefix_length[j]) {
          prefix_length[j] = prefix_length1;
        }
      }
      // the prefix cannot be too large
      if (prefix_length[j] >= 255) {
        prefix_length[j] = 255;
      }
    } else {
      prefix_length[j] = 0;
    }
    // cout << "prefix_length " << prefix_length[j] << endl;
  }
  // generate the compressed data
  for (int j = 0; j < off_vector; j++) {
    for (int t = 1; t < interval && interval * j + t < size; t++) {
      // all the compressed data has been put in the right place now
      value[interval * j + t] = &value[interval * j + t][prefix_length[j]];
      // cout << "The compressed value is " << value[interval * j + t] << endl;
    }
  }

  int size_interval[off_vector];  // the size of each interval plus the size
                                  // of offset vector
  // cout<<off_vector<<endl;
  // I need to calculate the size of each interval, here I need to think about
  // the uncompressed value plus the compressed value plus the offset vectors
  for (int j = 0; j < off_vector; j++) {
    // the size of uncompressed data
    size_interval[j] = sizeLength(value_uncompressed[j]) + 1;
    // the size of compressed data + codesize + prefixsize
    for (int t = 1; t < interval && (interval * j + t) < size; t++) {
      size_interval[j] +=
          sizeLength(value[interval * j + t]) + 1 + codeSize + prefixSize;
    }
    // each range has one offset vector
    size_interval[j] += offsetSize + codeSize;
    // cout
    //<< "The size of each interval, used to calculate the number of leaves: "
    //<< size_interval[j] << endl;
  }
  unsigned int code_start = 0;
  int leaf_number = 0;
  int leaf_watcher = 0;
  int size1 = size;
  int keeper = 0;  // the number of blocks have been inserted
  // cout<<"Here!"<<endl;

  for (int j = 0; j < off_vector; j++) {
    // leaf_watcher stores the size of current data
    leaf_watcher += size_interval[j];
    // cout << leaf_watcher << " " << j << " " << size_interval[j] << endl;
    // cout << leafSize << endl;
    // cout << " the size of the new added range is " << size_interval[j] <<
    // endl;
    if (leaf_watcher > leafSize || j == (off_vector - 1)) {
      int number_string = 0;
      // cout<<"Here!"<<endl;
      if (j == (off_vector - 1) && !(leaf_watcher > leafSize)) {
        // cout << "here!!!!!!!!!!!" << off_vector << endl;
        number_string = size - keeper * interval;
        // cout << number_string << endl;
      } else if (j == (off_vector - 1) && (leaf_watcher > leafSize)) {
        number_string = interval * (j - keeper);
        j = j - 1;
      } else {
        number_string = interval * (j - keeper);
        j = j - 1;
        /**
          if (keeper == 0) {
          int j1 = j+1;
          number_string = interval * (j1 - keeper);
        } else {
          number_string =
              interval *
              (j - keeper);  // the number of strings ready to be inserted
        }**/
      }
      // cout << "The number string: " << number_string << "Keeper " << keeper
      //<< endl;
      char *string_value[number_string];
      for (int t = keeper * interval; t < number_string + keeper * interval;
           t++) {
        string_value[t - keeper * interval] = value1[t];
        // cout << "The values ready to be inserted! "
        //<< string_value[t - keeper * interval] << endl;
      }
      // insert the data into the leaf_tmp
      leaf_number++;
      // cout << "The number of the leaf now: " << leaf_number << endl;
      int test = leaf_tmp.bulkload_initial(leaf_tmp.pointerLeaf, string_value,
                                           number_string, code_start);
      this->position++;
      code_start = leaf_tmp.node_last;
      // cout << "The number of leaves is: " << this->position << endl;
      this->Insert(leaf_tmp);
      keeper = j + 1;
      leaf_watcher = 0;
    }
  }

  return 1;
}

// the parts need to be filled later
Leaf *Leaves::getLeaf(int position) {
  Leaf *p = head;
  if (p == NULL) {
    // cout << "The is not leaf!" << endl;
  } else {
    int posi = 0;
    while (p != NULL && posi != position) {
      posi++;
      p = p->next;
    }
    if (p == NULL) {
      // cout << "There is no such leaf!" << endl;
      return NULL;
    } else {
      // cout << "The leaf is found!" << endl;
      return p;
    }
  }
  return NULL;
}

void Leaves::Insert(Leaf &leaf) {
  if (head == NULL) {
    head = tail = new Leaf(leaf);
    // head = new Leaf(leaf);
    head->next = NULL;
    tail->next = NULL;
    // cout << "The first leaf inserted!" << endl;
  } else {
    Leaf *p = new Leaf(leaf);
    tail->next = p;
    tail = p;
    // cout << "Insert a new leaf!" << endl;
    tail->next = NULL;
  }
}

Leaves::Leaves() {
  head = tail = NULL;
  position = 0;
  encodingpointer = NULL;
}

Leaves::~Leaves() {
  delete head;
  // delete tail;
}

vector<encodingindexNode> &Leaves::Getfullindex() { return this->fullindex; }

vector<decodingindexNode> &Leaves::Getindex_decode() {
  return this->index_decode;
}

bool Leaf::mycomp(string a, string b) { return a < b; }

vector<string> Leaf::alphabaticallySort(vector<string> a) {
  sort(a.begin(), a.end(), mycomp);
  return a;
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
    // cout << "vector string: " << strs[j] << endl;
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
    // cout << "The sorted value is: " << value[2 * j] << endl;
    // cout << "The generated code is: " << *(unsigned int *)value[2 * j + 1]
    //<< endl;  // test if the code has been pointed by the char * pointer
  }
  this->node_last = code[i - 1];
  // calculate the offset vectors, and set the number of uncompressed data.
  int off_vector = ceil((double)i / (double)decodeInterval);
  string_num = off_vector;
  // cout << " string number is " << string_num << endl;
  // cout << "The number of offset vectors: " << string_num << endl;
  int prefix_length[string_num];
  char *value1[string_num * 2];
  for (int j = 0; j < string_num; j++) {
    value1[2 * j] = value[decodeInterval * j * 2];
    value1[2 * j + 1] = value[decodeInterval * j * 2 + 1];
    // cout << "offset vector: " << value1[2 * j] << " "
    //<< *(unsigned int *)value1[2 * j + 1] << endl;
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
      // cout << "prefix length is: " << prefix_length[j] << endl;
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
      // cout << "The compressed value is: " << value[(decodeInterval * j + t) *
      // 2]
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
        // cout << " t here is " << t << endl;
      }
      offset[j] += offset[j - 1];
      // cout << "offset  uncompressed value is " << j << " is: " << offset[j]
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
    // cout << "The inserted uncompressed value is: " << leafpointer + offset[j]
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
      int prefix_tmp1 = *(int *)prefix_tmp;
      // cout << " the offset here is " << leaf_off - prefixSize << endl;
      // cout << "prefix length of compressed value is " << prefix_tmp1 << endl;
      tmp = value[(decodeInterval * j + t) * 2];
      strcpy(leafpointer + leaf_off, tmp.c_str());
      // cout << " the compressed data is " << leafpointer + leaf_off << endl;
      leaf_off += sizeLength(value[(decodeInterval * j + t) * 2]) + 1;
      char *code_tmp;
      code_tmp = value[(decodeInterval * j + t) * 2 + 1];
      for (int m = 0; m < codeSize; m++) {
        leafpointer[leaf_off] = code_tmp[m];
        leaf_off++;
      }
      // cout << *(unsigned int *)(leafpointer + leaf_off - codeSize) << endl;
    }
    // cout << "offset now is: " << leaf_off << endl;
  }
  int leaf_off1 = leaf_off;
  leaf_data = leaf_off1;
  // insert the offset vectors at the end of the leaf
  leaf_off = leafSize - 1 - string_num * (offsetSize + codeSize);
  for (int j = 0; j < string_num; j++) {
    char *code_tmp;
    code_tmp = value1[2 * (string_num - 1 - j) + 1];
    // cout << "code_tmp " << *(unsigned int *)value1[2 * (string_num - 1 - j) +
    // 1]
    //<< endl;
    for (int m = 0; m < codeSize; m++) {
      leafpointer[leaf_off] = code_tmp[m];
      leaf_off++;
    }

    char *offset_tmp = (char *)&offset[string_num - 1 - j];
    // cout << "offset here " << offset[string_num - 1 - j] << endl;
    for (int m = 0; m < offsetSize; m++) {
      leafpointer[leaf_off] = offset_tmp[m];
      leaf_off++;
    }
    char offset_tmp9[offsetSize];
    for (int j = 0; j < offsetSize; j++) {
      offset_tmp[j] = leafpointer[leaf_off - offsetSize + j];
    }
    int offset_tmp8 = *(int *)offset_tmp9;
    // cout << "offset vectors: "
    //<< *(unsigned int *)(leafpointer + leaf_off - offsetSize - codeSize)
    //<< " " << offset_tmp8 << endl;
  }

  return 0;
}

string Leaf::bulkLookup_code(char *leafpointer, int code) {
  int end_uncompressed = string_num - 1;
  int start_uncompressed = 0;
  int resultBinary = binarySearch_code(this->pointerLeaf, start_uncompressed,
                                       end_uncompressed, code);
  // cout << " the result of binary search is " << resultBinary << endl;
  if (resultBinary == -1) {
    // cout << "Thevalue does not exist!" << endl;
    return "";
  } else {
    int offset_result = leafSize - 1 - (offsetSize + codeSize) * resultBinary;
    // cout << "herer " << endl;
    char offset_tmp[offsetSize];
    for (int m = 0; m < offsetSize; m++) {
      offset_tmp[m] = this->pointerLeaf[offset_result - offsetSize + m];
    }
    unsigned int offset = *(unsigned int *)(offset_tmp);

    // cout << "offset to the target interval is " << offset << endl;
    string resultValue = this->pointerLeaf + offset;
    char code_tmp[codeSize];
    for (int m = 0; m < codeSize; m++) {
      code_tmp[m] =
          this->pointerLeaf[offset_result - offsetSize - codeSize + m];
    }
    int code1 = *(int *)(code_tmp);
    // cout << "the code here is " << code1 << endl;
    if (code1 == code) {
      // cout << "The result is in the uncompressed part: " << resultValue <<
      // endl;
      return resultValue;
    } else {
      // cout << "Search the code in the compressed value part: " << endl;
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
      // cout << "the test of the prefix here is " << test_tmp << endl;

      resultValue = sequentialSearch_code1(test_tmp, offset, offset1, code);
      // cout << "result value is: " << resultValue << endl;
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
  // cout << "start is: " << start_uncompressed << endl;
  // cout << "end is: " << end_uncompressed << endl;
  int resultBinary =
      binarySearch_prefix(leafpointer, start_uncompressed, end_uncompressed,
                          value);  // the reuslt of binary search
  // for the prefix matching, the binary search will still be able to find the
  // start of the range
  // cout << resultBinary << " The result of the binary search is " << endl;

  if (resultBinary == -1) {
    // cout << "the value does not exist, based on binary search." << endl;
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
    // cout << "The result of the binary search is " << resultValue_tmp << endl;

    string value_prefix = value;
    if (resultValue_tmp.find(value_prefix) == 0) {
      // cout << "Find the uncompressed result value!" << endl;
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
    // cout << "the start point and the end point of sequentialSearch " <<
    // offset
    //<< " " << offset1 << endl;
    result = sequentialSearch_prefix(leafpointer, offset, offset1, value);

    string value_next = &leafpointer[offset1];
    // cout << "The next uncompressed value is " << value_next << endl;
    // then we need to start the while loop, to test the rest ranges in this
    // leaf in order to make sure all the data is here.
    while (value_next.find(value_prefix) == 0) {
      // cout << "Find the uncompressed result value!" << endl;
      offset_result = offset_result + offsetSize + codeSize;
      int off_temp = leafSize - 1 - offset_result - offsetSize - codeSize;
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off_temp + m];
      }
      result.push_back(*(int *)(code_tmp));
      // cout << "the uncompressed result here is " << *(int *)(code_tmp) <<
      // endl;
      offset = offset1;
      resultBinary++;
      // cout << resultBinary << " the result binary is "
      //<< "leaf_data " << leaf_data << "the string num is " << string_num
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
        // cout << "Leaf data is  iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii "
        //<< leaf_data << endl;
      }
      string starting = &leafpointer[offset];
      // cout << "The string staring is " << starting << endl;
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
  // cout << "start is: " << start_uncompressed << endl;
  // cout << "end is: " << end_uncompressed << endl;
  int resultBinary =
      binarySearch(leafpointer, start_uncompressed, end_uncompressed,
                   value);  // the reuslt of binary search
  // for the prefix matching, the binary search will still be able to find the
  // start of the range
  if (resultBinary == -1) {
    // cout << "the value does not exist, based on binary search." << endl;
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
    // cout << "result value is: " << resultValue
    //<< endl;  // the testing result works fine
    int result;  // the final code to return
    if (strcmp(value, resultValue) == 0) {
      // cout << "Find the uncompressed result value!" << endl;
      int off_temp = leafSize - 1 - offset_result - offsetSize - codeSize;
      char code_tmp[codeSize];
      for (int m = 0; m < codeSize; m++) {
        code_tmp[m] = leafpointer[off_temp + m];
      }
      result = *(int *)(code_tmp);
      result_prefix.push_back(result);
      // cout << "The code of uncompressed result is: " << result << endl;
      return result;
    } else {
      // cout << "Search in the compressed value part!" << endl;
      unsigned int offset1;
      if (resultBinary + 1 <= string_num) {
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
      // cout << "The start offset of sequentialSearch is: " << offset <<
      // endl; cout << "The end offset of sequentialSearch is: " << offset1 <<
      // endl;
      result = sequentialSearch(leafpointer, offset, offset1, value);
      return result;
    }

    return -1;
  }
}

int Leaf::binarySearch_code(char *leafpointer, int start, int end, int code) {
  if (end >= start) {
    int mid = start + (end - start) / 2;
    // cout << "binary_code start: " << start << endl;
    // cout << "binary_code end: " << end << endl;
    // cout << "binary_code code: " << code << endl;
    // cout << "binary_code mid: " << mid << endl;
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
    // cout << "binary_code code1 is: " << code1 << endl;
    // cout << "bianry_code code2 is: " << code2 << endl;

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
    // cout << "offset1: " << offset1 << " " << offset_1 << endl;
    // cout << "value1: " << value1 << endl;
    // cout << "value: " << value << endl;
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
    // cout << "offset1: " << offset1 << " " << offset_1 << endl;
    // cout << "value1: " << value1 << " " << mid_off << endl;
    // cout << "value: " << value << endl;
    // cout << "here!!!!!!!!!!!!!!"
    //<< " " << mid_off << endl;
    if (strcmp(value1, value) < 0) {
      if (strcmp(value, value2) <
          0)  // make sure value1<=value, and there is no value2 between them
      {
        return mid_off;
      }
      // cout << "here!!!!!!!!!!!!!!"
      //<< " " << mid_off << endl;

      // if this comparation happened between the value and the uncompressed
      // value of the last interval, then I need to return the number of the
      // last interval.
      if (mid_off == this->string_num - 1) {
        // cout << "here is the place!!!" << endl;
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
  // cout << "The prefix length here is " << prefix_len << endl;
  // cout << " the code here is " << code << endl;
  for (int m = 0; m < code; m++) {
    value_curr = this->pointerLeaf + start1 + prefixSize;
    // cout << value_curr << endl;
    start1 += prefixSize + codeSize + value_curr.length() + 1;
  }

  // cout << value_curr << endl;
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
  // cout << " The prefix length here is " << curr_prefix_len << endl;
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
  int prefix_length = prefix_len(value, value_curr);
  string value_un = value_curr;

  // cout << " the value here is " << prefix_value << endl;
  // cout << " The starting value is " << value_curr << endl;

  int prefix_length1 = prefix_length;
  int curr_prefix_len;
  char *value1 = &value[prefix_length];

  // cout << " the value apart from the prefix common part " << value1 << endl;
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
    // cout << " The substring here is " << sub_str << endl;

    // cout << "the curr_prefix_len is " << curr_prefix_len << endl;
    value_curr = &leafpointer[start1];  // point the uncompressed part
    start1 = start1 + sizeLength(value_curr) + 1;
    // the code of compressed
    // value
    string value_com = value_curr;
    // cout << "double check the value compressed here " << value_com << endl;
    sub_str.append(value_com);
    // get the uncompressed string
    // cout << "the sub string used to do the comparation is " << sub_str <<
    // endl;
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
    // cout << "start1 is " << start1 << endl;
    // cout << "end is " << end << endl;
  }

  if (result.size() == 0) {
    // result.push_back(-1);
    // cout << "no result in the place!" << endl;
  }

  return result;
}

int Leaf::sequentialSearch(char *leafpointer, int start, int end, char *value) {
  char *value_curr = &leafpointer[start];  // pointer to the value from the
                                           // start
  int start1 = start + sizeLength(value_curr) +
               1;  // the start of the next compressed string
  int prefix_length = prefix_len(value, value_curr);
  int prefix_length1 = prefix_length;
  int curr_prefix_len;
  char *value1 =
      &value[prefix_length];  // the value apart from the prefix common part
  while (start1 <= end &&
         prefix_length1 <
             sizeLength(value))  // not reach the end and prefix length
  {
    // start1++;
    char prefix_tmp[prefixSize];
    for (int m = 0; m < prefixSize; m++) {
      prefix_tmp[m] = leafpointer[start1 + m];
      start1++;
    }
    curr_prefix_len = *(int *)prefix_tmp;
    value_curr = &leafpointer[start1];  // point the uncompressed part
    start1 = start1 + sizeLength(value_curr) + 1;  // te code of compressed
                                                   // value
    if (curr_prefix_len < prefix_length or curr_prefix_len > prefix_length) {
      continue;
    } else if (compareValue(value_curr, value1) >
               0)  // current value1 comes after search value, and here the
                   // value is also the part without the prefix value.
    {
      // cout << "GOT HERE?" << endl;
      return -1;
    }
    prefix_length1 =
        prefix_length +
        prefix_len(value1,
                   value_curr);  // the value here should be the original value
                                 // minus the first prefix_length charactors.
    start1 = start1 + codeSize;
    // cout << "The common prefix size is: " << prefix_length1 << endl;
    // cout << "The size of the value is: " << sizeLength(value) << endl;
  }
  if (prefix_length1 == sizeLength(value)) {
    // cout << "GOT HERE!" << endl;
    int off = start1;  // the start of the result code
    off = off - codeSize;
    char code_tmp[codeSize];
    for (int m = 0; m < codeSize; m++) {
      code_tmp[m] = leafpointer[off + m];
    }
    int result = *(int *)(code_tmp);
    return result;
  } else {
    return -1;
  }
}

void Leaf::printLeaf(int start, int end) {
  for (int i = start; i <= end; i++) {
    // cout << *(pointerLeaf + i) << endl;
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

static vector<string> decode_strings;

static mutex exclusive;

void Leaves::concurrent_worker_decode(vector<int> codes) {
  vector<string> tmp_decode;
  string tmp_string;
  int size = codes.size();
  // int code;
  for (auto code : codes) {
    tmp_string = this->lookupCode_index(code);
    // this->decode_result[m+start]=tmp_string ;
    //
    tmp_decode.push_back(tmp_string);
  }
  this->exclusive.lock();
  this->decode_result.insert(decode_result.end(), tmp_decode.begin(),
                             tmp_decode.end());
  this->exclusive.unlock();
}

thread Leaves::concurrent_worker_decodeThread(vector<int> codes) {
  return thread(&Leaves::concurrent_worker_decode, this, codes);
}

void Leaves::concurrent_task_decode(vector<int> codes) {
  auto start_time = chrono::steady_clock::now();
  unsigned concurrent_count = thread::hardware_concurrency();
  // cout << "hardware_concurrency: " << concurrent_count << endl;
  vector<thread> threads;
  int size = codes.size();
  // this->decode_result.resize(size);
  int range = (int)ceil((double)size / (double)concurrent_count);

  for (int t = 0; t < concurrent_count - 1; t++) {
    int tmp = range * t;
    vector<int>::const_iterator min = codes.begin() + tmp;
    vector<int>::const_iterator max = codes.begin() + tmp + range;
    vector<int> codes_tmp(min, max);
    threads.push_back(this->concurrent_worker_decodeThread(codes_tmp));
  }

  vector<int>::const_iterator min =
      codes.begin() + (concurrent_count - 1) * range;
  vector<int>::const_iterator max = codes.end();
  vector<int> codes_tmp(min, max);
  threads.push_back(this->concurrent_worker_decodeThread(codes_tmp));

  for (auto &t : threads) {
    t.join();
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  // for (auto decode_re : this->decode_result) {
  // cout << "The result of decoding " << decode_re << endl;
  //}
  cout << "Concurrent has finished ," << ms << " ms consumed" << endl;
  cout << "size is: " << this->decode_result.size() << endl;
}

void Leaves::serial_task_decode(vector<int> codes) {
  auto start_time = chrono::steady_clock::now();
  int size = codes.size();
  string tmp_string;
  // vector<string> tmp_decode;
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      tmp_string = this->lookupCode_index(codes[i]);
      this->decode_result.push_back(tmp_string);
    }
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Serial task has finished: " << ms << " ms consumed" << endl;
  cout << "size is: " << size << endl;
  // for (auto decode_re : this->decode_result) {
  // cout << "The result of decoding is: " << decode_re << endl;
  //}
}

void Leaves::concurrent_worker_encode(vector<string> strings) {
  vector<int> tmp_codes;
  vector<int> tmp_code;
  int size = strings.size();
  for (auto string_tmp : strings) {
    char *tmp = (char *)string_tmp.c_str();
    tmp_code = this->lookUpIndex(tmp, 1);
    tmp_codes.insert(tmp_codes.end(), tmp_code.begin(), tmp_code.end());
  }
  this->exclusive.lock();
  this->encode_result.insert(encode_result.end(), tmp_codes.begin(),
                             tmp_codes.end());
  this->exclusive.unlock();
}

thread Leaves::concurrent_worker_encodeThread(vector<string> strings) {
  return thread(&Leaves::concurrent_worker_encode, this, strings);
}

void Leaves::concurrent_task_encode(vector<string> strings) {
  auto start_time = chrono::steady_clock::now();
  unsigned concurrent_count = thread::hardware_concurrency();
  vector<thread> threads;
  int size = strings.size();
  int range = (int)ceil((double)size / (double)concurrent_count);

  for (int t = 0; t < concurrent_count - 1; t++) {
    int tmp = range * t;
    vector<string>::const_iterator min = strings.begin() + tmp;
    vector<string>::const_iterator max = strings.begin() + tmp + range;
    vector<string> strings_tmp(min, max);
    threads.push_back(this->concurrent_worker_encodeThread(strings_tmp));
  }

  vector<string>::const_iterator min =
      strings.begin() + (concurrent_count - 1) * range;
  vector<string>::const_iterator max = strings.end();
  vector<string> strings_tmp(min, max);
  threads.push_back(this->concurrent_worker_encodeThread(strings_tmp));

  for (auto &t : threads) {
    t.join();
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  // for (auto string1 : encode_result) {
  // cout<<"The result of the encoding is: "<<string1<<endl;
  //}
  cout << "Concurrent has finished ," << ms << " ms consumed" << endl;
  cout << "size is: " << this->encode_result.size() << endl;
}

void Leaves::serial_task_encode(vector<string> strings) {
  auto start_time = chrono::steady_clock::now();
  int size = strings.size();
  vector<int> code_tmp;
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      char *string_tmp = (char *)strings[i].c_str();
      code_tmp = this->lookUpIndex(string_tmp, 1);
      this->encode_result.insert(this->encode_result.end(), code_tmp.begin(),
                                 code_tmp.end());
    }
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  // for (auto code : encode_result) {
  // cout << "The encoding result is: " << code << endl;
  //}
  cout << "Serial task has finished: " << ms << " ms consumed" << endl;
  cout << "Size is: " << size << endl;
}

int main() {
  Leaf leaf2(1024, 3, 4, 1, 2, 0);
  string key = generateKey("aaf", "aaq");
  // cout << "The key generated is: " << key << endl;
  char value[] = {'a', 'g', 'y', 'g', '\0'};
  char value1[] = {'c', '\0'};
  vector<string> strs;
  strs = read_csv("sorted result.csv");

  // char *test[strs.size()];

  // cout<<"Here"<<endl;
  // for (int i = 0; i < strs.size(); i++) {
  // cout<<"Here "<<endl;
  // test[i] = (char *)strs[i].c_str();
  // strcpy(test[i], strs[i].c_str());
  // cout << "the string " << test[i] << " " << i << endl;
  //}
  // int offset1 = 0;
  // int offset2 = 19;
  // int offset3 = 25;
  char *name[6] = {(char *)"Hello", (char *)"Hel",    (char *)"Hela",
                   (char *)"Hell",  (char *)"Hello2", (char *)"Hello0"};
  // int test1 = leaf2.bulkload_initial(leaf2.pointerLeaf, name, 6, 0);
  // string str1 = leaf2.smallestValue();
  // string str2 = leaf2.largestValue();
  // cout << "The smallest string is: " << str1 << endl;
  // cout << " The largest value is: " << str2 << endl;
  // cout << " print the leaf here!!!" << endl;
  // leaf2.printStrings();
  // leaf2.printLeaf(0,1024);
  // cout << " the print is over here!!!" << endl;

  // string str4 = "WA";
  // string str5 = "a";
  // test.insertKeys(str4);
  // test.insertKeys(str3);
  // test.insertKeys(str3);
  // int t1 = test.insertKeys(str3);
  // int key_num = test.getKeynum();
  // int key_pos = test.getVector(3);

  // cout << "Key " << key1 << " key number " << key_num << " key position "
  //<< key_pos << " the return value of insertion method " << t1 << endl;
  // Leaf leaf3(leaf2);
  // int bulk_lookup1 = leaf3.bulkLookup(leaf3.pointerLeaf, value);
  // string code_result1 = leaf3.bulkLookup_code(leaf3.pointerLeaf, 60);
  Leaves leaves1;
  // leaves1.Insert(leaf2);
  // int test2 = leaves1.treeCreation();
  // vector<encodingindexNode> test_vec;
  // vector<encodingindexNode> test_vec1;
  // leaves1.Insert(leaf3);
  // Leaf *leaf4 = leaves1.getLeaf(9);
  int load_result = leaves1.bulkLoad(strs);
  int leaves_num = leaves1.getLeavesnum();
  // cout << "the number of leaves here " << leaves_num << endl;
  // Leaf *leaf4 = leaves1.getLeaf(leaves_num - 1);
  // leaf4->printStrings();
  // leaf4->printLeaf(0,1023);
  /*
    for (int i = 0; i < leaves_num; i++) {
      Leaf *leaf4 = leaves1.getLeaf(i);
      leaf4->printStrings();
    }
  */

  int encoding = leaves1.encodingIndexcreation();
  // test_vec1 = leaves1.Getfullindex();
  leaves1.serial_task_encode(strs);
  leaves1.concurrent_task_encode(strs);
  
  /**
  vector<int> encode_result;
  for (auto value_tmp : strs) {
    char *value = (char *)value_tmp.c_str();
    vector<int> encode_tmp = leaves1.lookUpIndex(value, 1);
    // cout<<"encode_tmp size is: "<<encode_tmp.size()<<endl;
    encode_result.insert(encode_result.end(), encode_tmp.begin(),
                         encode_tmp.end());
  }

  for (auto str_re : encode_result) {
    cout << "The result of the encoding serial task is: " << str_re << endl;
  }

  cout << "The size of the result is: " << encode_result.size() << " "
       << strs.size() << endl;
**/
  /**
       string tmp_2 = "lbbkoxvnfsattgmkynqe";
       char *value_tmp2 = (char*)tmp_2.c_str();
        vector<int> index_test = leaves1.lookUpIndex(value_tmp2, 1);
       for (int i = 0; i < index_test.size(); i++) {
         cout << "the result of index look up is: " << index_test[i]
              << " the i is: " << i << endl;
       }
   **/
  // vector<string> decode_result;
  int decoding = leaves1.decodingIndexcreation();
  // string decode_test = leaves1.lookupCode_index(442);
  // cout << " the decoding result here is " << decode_test << endl;
  /**
       for (int m = 0; m <= 999; m++) {
         string decode_test = leaves1.lookupCode_index(m);
         decode_result.push_back(decode_test);
       }
       for (auto decode_re : decode_result) {
         cout << " The result of decoding " << decode_re << endl;
       }
     **/

  vector<int> codes;
  for (int t = 999; t >= 0; t--) {
    for (int m = 0; m < 100; m++) {
      codes.push_back(t);
    }
  }
  leaves1.serial_task_decode(codes);
  leaves1.concurrent_task_decode(codes);

  Dictionary(strs);
  encodingDic(strs);
  decodingDic(codes);
  // leaves1.concurrent_task(0,999);
  // concurrent_task(0,999,leaves1);
  // get the vector from the custom object, dictionary
  // int index_size = leaves1.encodingpointer->getNodenum();
  // encodingindexNode indexnode_tmp1;
  // encodingindexNode *indexnode_tmp = new encodingindexNode;
  // for (int i = 0; i < index_size; i++) {
  // indexnode_tmp = leaves1.encodingpointer->index + i;
  // indexnode_tmp1 = *indexnode_tmp;
  // int node_size = indexnode_tmp->getKeynum();
  // for (int j = 1; j <= node_size; j++) {
  // string key_index = indexnode_tmp->getKey(j);
  // int offset_index = indexnode_tmp->getOffset();
  // cout << " The offset of the node is: " << offset_index
  //<< " The key of the node: " << key_index << endl;
  //}
  //}

  // cout << "----------------------------------------"
  //<< "The final full index test here!" << endl;
  /*
       for (int i = 0; i < test_vec1.size(); i++) {
      int node_size = test_vec1[i].getKeynum();
      for (int j = 1; j <= node_size; j++) {
        string key_index = test_vec1[i].getKey(j);
        int offset_index = test_vec1[i].getOffset();
        int levelnum = test_vec1[i].getLevelnum();
        int level = test_vec1[i].getLevel();
        cout << " The offset of the node is: " << offset_index
             << " The key of the node: " << key_index << " The level number is "
             << levelnum << " The level is " << level << endl;
      }
    }
    */
  // cout << "the data in the vector: " << test_vec1.size() << endl;
  // cout << "The number of leaves " << leaves_num << endl;
  // Leaf *leaf5 = leaves1.getLeaf(5);
  // leaf5->printLeaf(0, 1000);
  // string code_result1 = leaf5->bulkLookup_code(leaf5->pointerLeaf, 20);
  // int bulk_lookup1 = leaf5->bulkLookup(leaf5->pointerLeaf, value);
  // int leaves_lookup = leaves1.lookUp(value);
  // string code_result2 = leaves1.lookupCode(60);
  // if (!code_result2.empty()) {
  // cout << "the answer of bulkLookup_code is: " << code_result2 << endl;
  //} else {
  // cout << "the answer of bulkLookup_code is: no such code" << endl;
  //}
  // cout << "the answer of bulk lookup is: " << bulk_lookup1 << endl;
  // cout << "the answer of leaves lookup is: " << code_result1 << endl;
  return 0;
}
