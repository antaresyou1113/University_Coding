#include "Leaves.h"

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

vector<string> alphabaticallySort(vector<string> a) {
  map<string, int> strs;
  string tmp = "";
  int size = a.size();
  //cout << " The size of the input vector a: " << size << endl;
  vector<string> strs_tmp;
  for (int i = 0; i < size; i++) {
    tmp = a[i];
    //cout << " The string from the file is " << tmp << endl;
    strs.insert(pair<string, int>(tmp, 1));
  }
  //cout << " The size of the map is " << strs.size() << endl;
  for (map<string, int>::iterator it = strs.begin(); it != strs.end(); ++it) {
    tmp = it->first;
    //cout << " The string to be inserted into the vector " << tmp << endl;
    strs_tmp.push_back(tmp);
  }

  // sort(strs_tmp.begin(), strs_tmp.end(), mycomp);
  return strs_tmp;
}

int Leaves::getsuffixLeavesnum() { return this->position1; }

int Leaves::getLeavesnum() { return this->position; }

int Leaves::getAllleaves() { return this->position1; }
int Leaves::decodingIndexcreation() {
  if (this->head != NULL && this->position > 0) {
    vector<int> level_tmp;
    vector<decodingindexNode> index_tmp;
    int leaf_num = this->position;
    //cout << "leaf number is " << leaf_num << endl;
    decodingindexNode decode_node;
    int key_num = (decode_node.nodeSize() - 2 * 4) / 4;
    // int key_num = 2;
    // leaf_num--;
    int decode_num = 0;  // the number of nodes used for decoding index building
    for (int i = 0; leaf_num > 1; i++) {
      leaf_num = (int)ceil((double)(leaf_num - 1) / (double)(key_num));
      level_tmp.push_back(leaf_num);
      //cout << "leaf number is " << leaf_num << endl;
      decode_num += leaf_num;
    }
    //cout << "the size of the level " << level_tmp.size()
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
        //cout << "the code inserted " << code_tmp << endl;
        leaf_num++;
        if (leaf_num == this->position) {
          break;
        }
      }
      // if (leaf_num == this->position) {
      // break;
      //}
      index_tmp.push_back(decode_node);
      //cout << "the code here is " << decode_node.smallestKey() << endl;
      //cout << "the level is " << decode_node.getLevel() << endl;
      //cout << " the offset here is " << decode_node.getOffset() << endl;
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
          //cout << "HERE " << code_tmp << endl;
          decode_node.insertKey(code_tmp);
          leaf_num++;
          leaf_num1++;
          //cout << "Leaf number " << leaf_num << endl;
          if (leaf_num == level_tmp[i - 1]) {
            break;
          }
        }

        index_tmp.push_back(decode_node);
        //cout << "the code here is " << decode_node.smallestKey() << endl;
        //cout << "the level is " << decode_node.getLevel() << endl;
        //cout << " the offset here is " << decode_node.getOffset() << endl;
      }
      leaf_num++;
      //cout << "Herere" << endl;
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

    //for (int i = 0; i < this->index_decode.size(); i++) {
      //for (int j = 0; j < this->index_decode[i].getKeynum(); j++) {
        //int code_tmp = this->index_decode[i].getKey(j + 1);
        //int offset = this->index_decode[i].getOffset();
        //cout << "The code here is " << code_tmp << " The offset here is "
            // << offset << endl;
      //}
  //  }
    // the index has been built successfully

    return 0;
  }
  return -1;
}

int Leaves::encodingIndexcreationSuffix() {
  if (this->head != NULL && this->position1 > this->position &&
      this->position > 0) {
    Tree *tree1 = new Tree;
    int offset = position;
    //int keys_num = 0;
    int test = 0;       // used to see whether the node is full
    int level_num = 0;  // the number of nodes in one level
    int level = 0;      // the level of the nodes, starting from 0.
    Node *node_tmp = new Node;
    for (int i = position, j = position + 1; j < position1; i++, j++) {
      Leaf *leaf1 = new Leaf;
      Leaf *leaf2 = new Leaf;
      leaf1 = this->getLeaf(i);
      leaf2 = this->getLeaf(j);
      // get the largest value in the lower leaf and the smallest in the larger
      // leaf
      string smaller = leaf1->largestValue();
      string larger = leaf2->smallestValue();
      string key = generateKey(smaller, larger);
      //cout << "ssssssssssssssssssssssssssssssssss key " << key << endl;
      //cout << "smaller " << smaller << " larger " << larger << endl;
      // now the key has been generated, create a node in order to store the key
      // value
      node_tmp->insertLeafnum(offset);
      test = node_tmp->insertKeys(key);
      node_tmp->setLevel(level);
      if (test == -1) {
        level_num++;
        node_tmp->setLevelnum(level_num);
        tree1->Insert(*node_tmp);
        //cout << "        ddddddddddd         nodes number" << tree1->nodeNum()
            // << endl;
        offset += node_tmp->getKeynum();
        node_tmp->emptyNode();
        node_tmp->insertLeafnum(offset);
        test = node_tmp->insertKeys(key);
        if (test == -1) {
          //cout << "The node is too small for the key! " << endl;
          return -1;
        }
        if (j == position1 - 1) {
          level_num++;
          node_tmp->setLevelnum(level_num);
          tree1->Insert(*node_tmp);
        }
      } else if (j == position1 - 1) {
        level_num++;
        node_tmp->setLevelnum(level_num);
        tree1->Insert(*node_tmp);
        //cout << "                 nodes number" << tree1->nodeNum() << endl;
      }
    }
    Node *node_tmp1 = new Node;
    int offset1 = 0;
    int level_num1 =
        level_num;  // used to remember the number of nodes in one deeper level
    //cout << " The number of nodes in the former level  " << level_num1 << endl;
    int num_nodes = tree1->nodeNum();
    //int num_nodes1 = num_nodes;
    //cout << " current last level number is in level_num1 " << level_num1
        // << " current node number " << num_nodes << endl;
    for (int i = num_nodes - level_num1 + 1; i < num_nodes; i++) {
      //cout << "                The i here is " << i << " " << num_nodes << " "
           //<< level_num1 << endl;
      node_tmp1 = tree1->getNode(i);
      string key = node_tmp1->smallestKey();
      //cout << " The key here is " << key
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
        //cout << "                The i here is " << i << " " << num_nodes << " "
             //<< level_num1 << endl;
        node_tmp1 = tree1->getNode(i);
        string key = node_tmp1->smallestKey();
        //cout << " The key here is kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << key << " "
             //<< tree1->getNode(num_nodes - 1)->smallestKey() << endl;
        node_tmp2.insertLeafnum(offset);
        node_tmp2.setLevel(level);
        test = node_tmp2.insertKeys(tree1->getNode(i)->smallestKey());
        if (test == -1) {
          // if the node is full, insert the current node and insert the key in
          // a new nodei

          level_num++;  // this node has been inserted, so there is one more
                        // node in this level
          //cout << "level number here is " << level_num << endl;
          node_tmp2.setLevelnum(level_num);
          tree1->Insert(node_tmp2);
          // //cout<<" the number of nodes here "<<tree1->nodeNum()<<endl;
          offset += node_tmp2.getKeynum();  // offset calculation for the next
                                            // node in the same level
          node_tmp2.insertKeynum(0);
          node_tmp2.emptyNode();
          node_tmp2.insertLeafnum(offset);
          test =
              node_tmp2.insertKeys(key);  // insert the key into this new node
          if (test == -1) {
            //cout << " The key is too small! " << key << endl;
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
          // //cout << "             The position of node here is " << level_num +
          // i
          //<< endl;
          if (level_num == 1) {
            offset = 0;
            node_tmp2.insertLeafnum(offset);
          }
          node_tmp2.setLevelnum(level_num);
          tree1->Insert(node_tmp2);
          //cout << " the number of nodes here " << tree1->nodeNum() << endl;
        }
      }

      // test more
      /**
      for (int i = 0; i < (tree1->nodeNum()); i++) {
        node_tmp = tree1->getNode(i);
        for (int m = 1; m <= node_tmp->getKeynum(); m++) {
          string str_key = node_tmp->getKey(m);
          //int offset_leaf = node_tmp->getLeafnum();
          //int level_test = node_tmp->getLevel();
          //int level_numtest = node_tmp->getLevelnum();
          //cout << " some info " << str_key << " " << offset_leaf << " level "
              //<< level_test << " level number " << level_numtest
              // << " The offset " << node_tmp->getLeafnum() << endl;
        }
      }
      **/
      //cout << "-----------------------------------------------------" << endl;
      level_num1 = level_num;  // store the number of nodes in this level
      num_nodes = tree1->nodeNum();
      //cout << "Node number in level " << level << " is " << level_num1 << endl;
      for (int n = num_nodes - level_num1; n < num_nodes; n++) {
        // //cout << "n in the for loop is " << n << endl;
        int offset1 = tree1->getNode(n)->getLeafnum();
        //cout << " The number of n is              " << n << endl;
        //cout << "offset1         " << offset1 << " Level is " << level << endl;
        offset1 += level_num1;
        //cout << "offset2        " << offset1 << " Level is " << level << endl;
        tree1->getNode(n)->insertLeafnum(offset1);
        // tree1->setNode(n, *node_tmp);
      }
    }
    num_nodes = tree1->nodeNum();
    //cout << "Finish the while loop " << num_nodes << endl;
    this->encodingpointer = new encodingIndex(num_nodes);
    encodingindexNode *indexnode_tmp = new encodingindexNode;
    int levelnum = tree1->getNode(num_nodes - 1)->getLevelnum();
    int nodes_left = num_nodes;
    //int nodes_inserted = 0;
    int j = 0;
    //cout << "NODES LEFT" << nodes_left << endl;
    while (nodes_left > 0) {
      levelnum = tree1->getNode(nodes_left - 1)->getLevelnum();
      //cout << "here!!!!!!!" << endl;
      nodes_left -= levelnum;
      for (int i = nodes_left; i < nodes_left + levelnum; i++, j++) {
        node_tmp = tree1->getNode(i);
        indexnode_tmp->insertNode(*node_tmp);
        indexnode_tmp->insertLevelnum(levelnum);
        encodingindexNode indexnode_tmp1 = *indexnode_tmp;
        this->index_encode_suffix.push_back(indexnode_tmp1);
        this->encodingpointer->insertIndexnode(j, *indexnode_tmp);
      }
    }
    /**
    for (int t = 0; t < tree1->nodeNum(); t++) {
      node_tmp = tree1->getNode(t);
      for (int m = 1; m <= node_tmp->getKeynum(); m++) {
        string str_key = node_tmp->getKey(m);
        int offset_leaf = node_tmp->getLeafnum();
        int level_test = node_tmp->getLevel();
        int level_numtest = node_tmp->getLevelnum();
        //cout << " some info " << str_key << " " << offset_leaf << " level "
             //<< level_test << " level number " << level_numtest << endl;
      }
    }
    **/
    delete node_tmp;
    delete node_tmp1;
    delete tree1;
    return 0;
  }

  return -1;
}

int Leaves::encodingIndexcreation() {
  if (this->head != NULL && this->position > 0) {
    Tree *tree1 = new Tree;
    int offset = 0;
    //int keys_num = 0;
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
      //cout << "ssssssssssssssssssssssssssssssssss key " << key << endl;
      //cout << "smaller " << smaller << " larger " << larger << endl;
      // now the key has been generated, create a node in order to store the key
      // value
      node_tmp->insertLeafnum(offset);
      test = node_tmp->insertKeys(key);
      node_tmp->setLevel(level);
      if (test == -1) {
        level_num++;
        node_tmp->setLevelnum(level_num);
        tree1->Insert(*node_tmp);
        //cout << "        ddddddddddd         nodes number" << tree1->nodeNum()
            // << endl;
        offset += node_tmp->getKeynum();
        node_tmp->emptyNode();
        node_tmp->insertLeafnum(offset);
        test = node_tmp->insertKeys(key);
        if (test == -1) {
          //cout << "The node is too small for the key! " << endl;
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
        //cout << "                 nodes number" << tree1->nodeNum() << endl;
      }
    }
    // node_tmp = tree1->getNode(i);
    // The part above is finished and it good. now I need to think abot how to
    // implement the levels on top of it.
    Node *node_tmp1 = new Node;
    // Node node_tmp2;
    // node_tmp->emptyNode();
    int offset1 = 0;
    // //cout << level_num << " The level number " << endl;
    int level_num1 =
        level_num;  // used to remember the number of nodes in one deeper level
    //cout << " The number of nodes in the former level  " << level_num1 << endl;
    int num_nodes = tree1->nodeNum();
    //int num_nodes1 = num_nodes;
    //cout << " current last level number is in level_num1 " << level_num1
         //<< " current node number " << num_nodes << endl;
    // test
    //
    for (int i = num_nodes - level_num1 + 1; i < num_nodes; i++) {
      //cout << "                The i here is " << i << " " << num_nodes << " "
           //<< level_num1 << endl;
      node_tmp1 = tree1->getNode(i);
      string key = node_tmp1->smallestKey();
      //cout << " The key here is " << key
          // << tree1->getNode(num_nodes - 1)->smallestKey() << endl;
    }

    while (level_num > 1) {
      // I need to create the levels above
      Node node_tmp2;
      level++;
      level_num = 0;  // the number of nodes in this level
      offset1 = 0;    // used to recalculate the offset for nodes in this level
      offset = 0;  // used to calculate the offset for the nodes in this level
      for (int i = num_nodes - level_num1 + 1; i < num_nodes; i++) {
        //cout << "                The i here is " << i << " " << num_nodes << " "
            // << level_num1 << endl;
        node_tmp1 = tree1->getNode(i);
        string key = node_tmp1->smallestKey();
        //cout << " The key here is kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << key << " "
            // << tree1->getNode(num_nodes - 1)->smallestKey() << endl;
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
          //cout << "level number here is " << level_num << endl;
          node_tmp2.setLevelnum(level_num);
          tree1->Insert(node_tmp2);
          // //cout<<" the number of nodes here "<<tree1->nodeNum()<<endl;
          offset += node_tmp2.getKeynum();  // offset calculation for the next
                                            // node in the same level
          node_tmp2.insertKeynum(0);
          node_tmp2.emptyNode();
          node_tmp2.insertLeafnum(offset);
          test =
              node_tmp2.insertKeys(key);  // insert the key into this new node
          if (test == -1) {
            //cout << " The key is too small! " << key << endl;
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
          // //cout << "             The position of node here is " << level_num +
          // i
          //<< endl;
          if (level_num == 1) {
            offset = 0;
            node_tmp2.insertLeafnum(offset);
          }
          node_tmp2.setLevelnum(level_num);
          tree1->Insert(node_tmp2);
          //cout << " the number of nodes here " << tree1->nodeNum() << endl;
        }
      }
      // test more
      /**
      for (int i = 0; i < (tree1->nodeNum()); i++) {
        node_tmp = tree1->getNode(i);
        for (int m = 1; m <= node_tmp->getKeynum(); m++) {
          string str_key = node_tmp->getKey(m);
          //int offset_leaf = node_tmp->getLeafnum();
          int level_test = node_tmp->getLevel();
          int level_numtest = node_tmp->getLevelnum();
          //cout << " some info " << str_key << " " << offset_leaf << " level "
              // << level_test << " level number " << level_numtest
              // << " The offset " << node_tmp->getLeafnum() << endl;
        }
      }
      **/
      //cout << "-----------------------------------------------------" << endl;
      //
      level_num1 = level_num;  // store the number of nodes in this level
      num_nodes = tree1->nodeNum();
      //cout << "Node number in level " << level << " is " << level_num1 << endl;
      for (int n = num_nodes - level_num1; n < num_nodes; n++) {
        // //cout << "n in the for loop is " << n << endl;
        int offset1 = tree1->getNode(n)->getLeafnum();
        //cout << " The number of n is              " << n << endl;
        //cout << "offset1         " << offset1 << " Level is " << level << endl;
        offset1 += level_num1;
        //cout << "offset2        " << offset1 << " Level is " << level << endl;
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
              //cout << " some info " << str_key << " " << offset_leaf << " level
         "
                   << level_test << " level number " << level_numtest
                   << " The offset " << node_tmp->getLeafnum() << endl;
            }
          }*/
      //
    }
    num_nodes = tree1->nodeNum();
    //cout << "Finish the while loop " << num_nodes << endl;
    this->encodingpointer = new encodingIndex(num_nodes);
    encodingindexNode *indexnode_tmp = new encodingindexNode;
    int levelnum = tree1->getNode(num_nodes - 1)->getLevelnum();
    int nodes_left = num_nodes;
    //int nodes_inserted = 0;
    int j = 0;
    //cout << "NODES LEFT" << nodes_left << endl;
    while (nodes_left > 0) {
      levelnum = tree1->getNode(nodes_left - 1)->getLevelnum();
      //cout << "here!!!!!!!" << endl;
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
    /**
    for (int t = 0; t < tree1->nodeNum(); t++) {
      node_tmp = tree1->getNode(t);
      for (int m = 1; m <= node_tmp->getKeynum(); m++) {
        string str_key = node_tmp->getKey(m);
        int offset_leaf = node_tmp->getLeafnum();
        int level_test = node_tmp->getLevel();
        int level_numtest = node_tmp->getLevelnum();
        //cout << " some info " << str_key << " " << offset_leaf << " level "
            // << level_test << " level number " << level_numtest << endl;
      }
    }
    **/
    delete node_tmp;
    delete node_tmp1;
    delete tree1;
    return 0;
  }

  return -1;
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
  //int key_tmp1 = 0;
  //int key_num = 0;
  int level_tmp = test_vec1[0].getLevel();
  int break_point = 0;
  int level_start = 0;
  int levelnum_count = 0;
  int levelnum_count1 = 0;
  int leaf_num = 0;

  //cout << "the input code is " << code << endl;
  while (level_tmp >= 0) {
    offset_tmp1 = offset_tmp;
    //cout << "The information here: "
        // << " level: " << level_tmp << " offset_tmp " << offset_tmp
        // << " The key here " << test_vec1[offset_tmp].getKey(1) << endl;
    levelnum_count1 = levelnum_count;
    levelnum_count += test_vec1[offset_tmp].getLevelnum();
    // the number of the  nodes until this level
    for (int i = level_start, m = 0; i < test_vec1[offset_tmp].getLevelnum();
         i++, m++) {
      // all the nodes in the same level, in order to find the right position
      offset_tmp1 += m;
      for (int j = 1; j <= test_vec1[offset_tmp1].getKeynum(); j++) {
        key_tmp = test_vec1[offset_tmp1].getKey(j);
        //cout << " the key_tmp here is " << key_tmp << endl;
        if (i == 0 && j == 1 && (code < key_tmp)) {
          offset_tmp = test_vec1[offset_tmp1].getOffset() + levelnum_count1;
          //cout << " The offset stored in this node is "
              // << test_vec1[offset_tmp1].getOffset();
          //cout << " The level number is " << levelnum_count1 << endl;
          //cout << " the offset here is " << offset_tmp << endl;
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
          //cout << " The offset stored in this node is "
              // << test_vec1[offset_tmp1].getOffset();
          //cout << " The level number is " << levelnum_count1 << endl;
          //cout << " the offset here is " << offset_tmp << endl;
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
            //cout << " The offset stored in this node is "
                // << test_vec1[offset_tmp1].getOffset();
            //cout << " The level number is " << levelnum_count1 << endl;
            //cout << " the offset here is " << offset_tmp << endl;
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
  //cout << " The leaf number here is: " << leaf_num << endl;
  result = this->getLeaf(leaf_num)->bulkLookup_code(
      this->getLeaf(leaf_num)->pointerLeaf, code);

  return result;
}
/**
vector<int> Leaves::lookUpIndexSuffix(char *value){
    vector<encodingindexNode> test_vec1 = this->Getindex_suffix();


}
**/
vector<int> Leaves::lookUpIndex(char *value, int prefix_flag) {
  vector<encodingindexNode> test_vec1;
  if (prefix_flag == 2) {
    test_vec1 = this->Getindex_suffix();
    string t1 = value;
    //cout << t1 << endl;
    reverse(t1.begin(), t1.end());
    //cout << t1 << endl;
    value = (char *)t1.c_str();
  } else {
    test_vec1 = this->Getfullindex();
  }
  //cout << "value" << value << endl;
  /**
  for (int i = 0; i < test_vec1.size(); i++) {
    int node_size = test_vec1[i].getKeynum();
    for (int j = 1; j <= node_size; j++) {
      string key_index = test_vec1[i].getKey(j);
      int offset_index = test_vec1[i].getOffset();
      int levelnum = test_vec1[i].getLevelnum();
      int level = test_vec1[i].getLevel();
      //cout << " The offset of the node is: " << offset_index
        //   << " The key of the node: " << key_index << " The level number is "
          // << levelnum << " The level is " << level << endl;
    }
  }
  **/

  vector<int> result;
  int offset_tmp = 0;
  int offset_tmp1 = offset_tmp;
  int lastkey = test_vec1[0].getKeynum();
  string key_tmp = test_vec1[0].getKey(lastkey);
  string key_tmp1 = "";
  string key_target = value;
  //int key_num = 0;
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
  //cout << "The input value here is " << key_target << endl;

  while (level_tmp >= 0) {
    // start the loop in one level, starting from the level 2
    offset_tmp1 = offset_tmp;
    //cout << "The information here: "
        // << " level: " << level_tmp << " offset_tmp " << offset_tmp
        // << " The key here " << test_vec1[offset_tmp].getKey(1) << endl;
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
        //cout << " the key_tmp here is " << key_tmp << endl;
        // if the first value in this level is larger than the target value,
        // then I will reach the next level
        if (i == 0 && j == 1 && (key_target.compare(key_tmp) < 0)) {
          offset_tmp = test_vec1[offset_tmp1].getOffset() + levelnum_count1;
          //cout << " The offset stored in this node is "
            //   << test_vec1[offset_tmp1].getOffset();
          //cout << " The level number is " << levelnum_count1 << endl;
          //cout << " the offset here is " << offset_tmp << endl;
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
          //cout << " The offset stored in this node is "
            //   << test_vec1[offset_tmp1].getOffset();
          //cout << " The level number is " << levelnum_count1 << endl;
          //cout << " the offset here is " << offset_tmp << endl;
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
            //cout << " The offset stored in this node is "
              //   << test_vec1[offset_tmp1].getOffset();
            //cout << " The level number is " << levelnum_count1 << endl;
            //cout << " the offset here is " << offset_tmp << endl;
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
    //cout << "try to change the leaf num here" << endl;
    string smallest = this->getLeaf(leaf_num - 1)->smallestValue();
    string largest = this->getLeaf(leaf_num)->smallestValue();
    //cout << smallest << " " << largest << endl;
    if (smallest.compare(key_target) < 0 && key_target.compare(largest) < 0) {
      leaf_num--;
    }
  }
  //cout << " The leaf number here is: " << leaf_num << endl;

  if (prefix_flag == 0) {
    int result_tmp = this->getLeaf(leaf_num)->bulkLookup(
        this->getLeaf(leaf_num)->pointerLeaf, value);
    leaf_num++;
    /**
     if(result_tmp==-1 && leaf_num<this->getLeavesnum()){
         string next_leaf = (this->getLeaf(leaf_num)->smallestValue());
         string value_tmp = value;
         if(value_tmp.compare(next_leaf)>=0){
             result_tmp =
     this->getLeaf(leaf_num)->bulkLookup(this->getLeaf(leaf_num)->pointerLeaf,value);
         }

     }
     **/
    result.push_back(result_tmp);
  }

  else {
    // we need to do the prefix match here
    //
    result = this->getLeaf(leaf_num)->bulkLookup_prefix(
        this->getLeaf(leaf_num)->pointerLeaf, value);
    //int length = sizeLength(value);
    leaf_num++;
    if (leaf_num < this->getLeavesnum()) {
      string next_leaf = (this->getLeaf(leaf_num))->smallestValue();

      string prefix_tmp = value;
      while (next_leaf.find(prefix_tmp) == 0 &&
             leaf_num < this->getLeavesnum()) {
        // //cout << "Here!1111111111111111111111111111111111111111" << endl;
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
    // //cout<<"Here!"<<endl;
    leaf_tmp = this->getLeaf(i + 1);
  }
  return result;
}

int Leaves::bulkLoadSuffix(vector<string> strs) {
  // reverse all the input strings and sort them alphbatially
  // use them as the input of the new dictionary
  for (int t = 0; t < strs.size(); t++) {
    reverse(strs[t].begin(), strs[t].end());
  }

  strs = alphabaticallySort(strs);
  for (auto str_t : strs) {
    //cout << "the reversed data is: " << str_t << endl;
  }

  this->position1 =
      this->position;  // the starting point of the suffix dictionary
  int size = strs.size();
  //cout << "the number of strings " << size << endl;

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
  //cout << "the number of offset vectors is: " << off_vector << endl;
  int prefix_length[off_vector];

  char *value_uncompressed[off_vector];

  int interval = leaf_tmp.getDecode_interval();
  int codeSize = leaf_tmp.getCode_size();
  int leafSize = leaf_tmp.getLeaf_size();
  // //cout<<leafSize<<endl;
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
    // //cout << "prefix_length " << prefix_length[j] << endl;
  }

  // generate the compressed data
  for (int j = 0; j < off_vector; j++) {
    for (int t = 1; t < interval && interval * j + t < size; t++) {
      // all the compressed data has been put in the right place now
      value[interval * j + t] = &value[interval * j + t][prefix_length[j]];
      //cout << "The compressed value is " << value[interval * j + t] << endl;
    }
  }
  int size_interval[off_vector];  // the size of each interval plus the size
                                  // of offset vector
  // //cout<<off_vector<<endl;
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
    //cout
      //  << "The size of each interval, used to calculate the number of leaves: "
    //    << size_interval[j] << endl;
  }

  unsigned int code_start = 0;
  int leaf_number = 0;
  int leaf_watcher = 0;
  //int size1 = size;
  int keeper = 0;  // the number of blocks have been inserted
                   // //cout<<"Here!"<<endl;

  for (int j = 0; j < off_vector; j++) {
    // leaf_watcher stores the size of current data
    leaf_watcher += size_interval[j];
    //cout << leaf_watcher << " " << j << " " << size_interval[j] << endl;
    //cout << leafSize << endl;
    //cout << " the size of the new added range is " << size_interval[j] << endl;
    if (leaf_watcher >= leafSize || j == (off_vector - 1)) {
      int number_string = 0;
      // //cout<<"Here!"<<endl;
      if (j == (off_vector - 1) && leaf_watcher < leafSize) {
        //cout << "here!!!!!!!!!!!" << off_vector << endl;
        number_string = size - keeper * interval;
        //cout << number_string << endl;
      } else if (j == (off_vector - 1) && (leaf_watcher >= leafSize)) {
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
      //cout << "The number string: " << number_string << "Keeper " << keeper
      //     << endl;
      char *string_value[number_string];
      vector<int> codes_suffix;
      vector<string> strs_suffix;
      int code_tmp;
      char *value_re;
      string str_re;
      //cout << "test here is !!!!!!" << endl;
      for (int t = keeper * interval; t < number_string + keeper * interval;
           t++) {
        string_value[t - keeper * interval] = value1[t];
        str_re = value1[t];
        reverse(str_re.begin(), str_re.end());
        value_re = (char *)str_re.c_str();
        code_tmp = this->lookUpIndex(value_re, 1)[0];
        //cout << code_tmp << "the code here is !" << endl;
        codes_suffix.push_back(code_tmp);
        //cout << "The values ready to be inserted! "
        //     << string_value[t - keeper * interval] << endl;
      }
      // insert the data into the leaf_tmp
      leaf_number++;

      // //cout << "The number of the leaf now: " << leaf_number << endl;
      /**
      for (auto code : codes_suffix) {
        //cout << "The code in this range is: " << code << endl;
      }
**/
      int test = leaf_tmp.bulkLoad_initialSuffix(
          leaf_tmp.pointerLeaf, string_value, number_string, codes_suffix);
      if(test==0){
      this->position1++;
      code_start = leaf_tmp.node_last;
      // //cout << "The number of leaves is: " << this->position << endl;
      this->Insert(leaf_tmp);
}
      keeper = j + 1;
      leaf_watcher = 0;
    }
  }
  return 0;
}

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
  // //cout << strs[j] << " the vector string in the load method: " << j <<
  // endl;
  //}
  //
  // the key point of this function is to make sure that the size of the values
  // inserted is less than the leaf size
  strs = alphabaticallySort(strs);
  int size = strs.size();
  //cout << "the number of strings " << size << endl;

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
  //cout << "the number of offset vectors is: " << off_vector << endl;
  int prefix_length[off_vector];

  char *value_uncompressed[off_vector];

  int interval = leaf_tmp.getDecode_interval();
  int codeSize = leaf_tmp.getCode_size();
  int leafSize = leaf_tmp.getLeaf_size();
  // //cout<<leafSize<<endl;
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
    // //cout << "prefix_length " << prefix_length[j] << endl;
  }
  // generate the compressed data
  for (int j = 0; j < off_vector; j++) {
    for (int t = 1; t < interval && interval * j + t < size; t++) {
      // all the compressed data has been put in the right place now
      value[interval * j + t] = &value[interval * j + t][prefix_length[j]];
      //cout << "The compressed value is " << value[interval * j + t] << endl;
    }
  }

  int size_interval[off_vector];  // the size of each interval plus the size
                                  // of offset vector
  // //cout<<off_vector<<endl;
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
    //cout
    //    << "The size of each interval, used to calculate the number of leaves: "
      //  << size_interval[j] << endl;
  }
  unsigned int code_start = 0;
  int leaf_number = 0;
  int leaf_watcher = 0;
  //int size1 = size;
  int keeper = 0;  // the number of blocks have been inserted
  // //cout<<"Here!"<<endl;

  for (int j = 0; j < off_vector; j++) {
    // leaf_watcher stores the size of current data
    leaf_watcher += size_interval[j];
    //cout << leaf_watcher << " " << j << " " << size_interval[j] << endl;
    //cout << leafSize << endl;
    //cout << " the size of the new added range is " << size_interval[j] << endl;
    if (leaf_watcher >= leafSize || j == (off_vector - 1)) {
      int number_string = 0;
      // //cout<<"Here!"<<endl;
      if (j == (off_vector - 1) && leaf_watcher < leafSize) {
        //cout << "here!!!!!!!!!!!" << off_vector << endl;
        number_string = size - keeper * interval;
        //cout << number_string << endl;
      } else if (j == (off_vector - 1) && (leaf_watcher >= leafSize)) {
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
      //cout << "The number string: " << number_string << "Keeper " << keeper
      //     << endl;
      char *string_value[number_string];
      // vector<int> codes_suffix;
      // vector<string> strs_suffix;
      //int code_tmp;
      for (int t = keeper * interval; t < number_string + keeper * interval;
           t++) {
        string_value[t - keeper * interval] = value1[t];
        // code_tmp = this->lookUpIndex(value1[t],1)[0];
        // codes_suffix.push_back(code_tmp);
        //cout << "The values ready to be inserted! "
      //       << string_value[t - keeper * interval] << endl;
      }
      // insert the data into the leaf_tmp
      leaf_number++;
      // //cout << "The number of the leaf now: " << leaf_number << endl;
      int test = leaf_tmp.bulkload_initial(leaf_tmp.pointerLeaf, string_value,
                                           number_string, code_start);
if(test==0){
      this->position++;
      code_start = leaf_tmp.node_last;
      // //cout << "The number of leaves is: " << this->position << endl;
      this->Insert(leaf_tmp);
      keeper = j + 1;
      leaf_watcher = 0;}
    }
  }

  return 1;
}

// the parts need to be filled later
Leaf *Leaves::getLeaf(int position) {
  Leaf *p = head;
  if (p == NULL) {
    //cout << "The is not leaf!" << endl;
  } else {
    int posi = 0;
    while (p != NULL && posi != position) {
      posi++;
      p = p->next;
    }
    if (p == NULL) {
      //cout << "There is no such leaf!" << endl;
      return NULL;
    } else {
      //cout << "The leaf is found!" << endl;
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
    //cout << "The first leaf inserted!" << endl;
  } else {
    Leaf *p = new Leaf(leaf);
    tail->next = p;
    tail = p;
    //cout << "Insert a new leaf!" << endl;
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

vector<encodingindexNode> &Leaves::Getindex_suffix() {
  return this->index_encode_suffix;
}

void Leaves::concurrent_worker_decode(vector<int> codes) {
  vector<string> tmp_decode;
  string tmp_string;
  //int size = codes.size();
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
  this->decode_result.clear();
  auto start_time = chrono::steady_clock::now();
  unsigned concurrent_count = thread::hardware_concurrency();
  //cout << "hardware_concurrency: " << concurrent_count << endl;
  vector<thread> threads;
  int size = codes.size();
  // this->decode_result.resize(size);
  int range = (int)ceil((double)size / (double)concurrent_count);
  if (size >= concurrent_count) {
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
  } else {
    for (int t = 0; t < size; t++) {
      int tmp = range * t;
      vector<int>::const_iterator min = codes.begin() + tmp;
      vector<int>::const_iterator max = codes.begin() + tmp + range;
      vector<int> codes_tmp(min, max);
      threads.push_back(this->concurrent_worker_decodeThread(codes_tmp));
    }
  }
  for (auto &t : threads) {
    t.join();
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Concurrent has finished ," << ms << " ms consumed" << endl;
  cout << "size is: " << this->decode_result.size() << endl;
   for (auto decode_re : this->decode_result) {
   cout << "The result of decoding " << decode_re << endl;
  }
}

void Leaves::serial_task_decode(vector<int> codes) {
  this->decode_result.clear();
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
  for (auto decode_re : this->decode_result) {
    cout << "The result of decoding is: " << decode_re << endl;
  }
}

void Leaves::concurrent_worker_encode(vector<string> strings, int mode) {
  vector<int> tmp_codes;
  vector<int> tmp_code;
  //int size = strings.size();
  for (auto string_tmp : strings) {
    char *tmp = (char *)string_tmp.c_str();
    tmp_code = this->lookUpIndex(tmp, mode);
    tmp_codes.insert(tmp_codes.end(), tmp_code.begin(), tmp_code.end());
  }
  this->exclusive.lock();
  this->encode_result.insert(encode_result.end(), tmp_codes.begin(),
                             tmp_codes.end());
  this->exclusive.unlock();
}

thread Leaves::concurrent_worker_encodeThread(vector<string> strings,
                                              int mode) {
  return thread(&Leaves::concurrent_worker_encode, this, strings, mode);
}

void Leaves::concurrent_task_encode(vector<string> strings, int mode) {
  this->encode_result.clear();
  auto start_time = chrono::steady_clock::now();
  unsigned concurrent_count = thread::hardware_concurrency();
  vector<thread> threads;
  int size = strings.size();
  int range = (int)ceil((double)size / (double)concurrent_count);
  if (size >= concurrent_count) {
    for (int t = 0; t < concurrent_count - 1; t++) {
      int tmp = range * t;
      vector<string>::const_iterator min = strings.begin() + tmp;
      vector<string>::const_iterator max = strings.begin() + tmp + range;
      vector<string> strings_tmp(min, max);
      threads.push_back(
          this->concurrent_worker_encodeThread(strings_tmp, mode));
    }

    vector<string>::const_iterator min =
        strings.begin() + (concurrent_count - 1) * range;
    vector<string>::const_iterator max = strings.end();
    vector<string> strings_tmp(min, max);
    threads.push_back(this->concurrent_worker_encodeThread(strings_tmp, mode));
  }

  else {
    for (int t = 0; t < size; t++) {
      int tmp = range * t;
      vector<string>::const_iterator min = strings.begin() + tmp;
      vector<string>::const_iterator max = strings.begin() + tmp + range;
      vector<string> strings_tmp(min, max);
      threads.push_back(
          this->concurrent_worker_encodeThread(strings_tmp, mode));
    }
  }
  for (auto &t : threads) {
    t.join();
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  for (auto string1 : encode_result) {
    cout << "The result of the encoding is: " << string1 << endl;
  }
  cout << "Concurrent has finished ," << ms << " ms consumed" << endl;
  cout << "size is: " << this->encode_result.size() << endl;
}

void Leaves::serial_task_encode(vector<string> strings, int mode) {
  this->encode_result.clear();
  auto start_time = chrono::steady_clock::now();
  int size = strings.size();
  vector<int> code_tmp;
  if (size > 0) {
    for (int i = 0; i < size; i++) {
      char *string_tmp = (char *)strings[i].c_str();
      code_tmp = this->lookUpIndex(string_tmp, mode);
      this->encode_result.insert(this->encode_result.end(), code_tmp.begin(),
                                 code_tmp.end());
    }
  }
  auto end_time = chrono::steady_clock::now();
  auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time)
                .count();
  cout << "Serial task has finished: " << ms << " ms consumed" << endl;

  for (auto code : encode_result) {
    cout << "The encoding result is: " << code << endl;
  }
  cout << "size of result is: " << encode_result.size() << endl;
  cout << "Size is: " << size << endl;
}

void Leaves::generateFile(string filename) {
  ofstream outfile(filename, ios::binary);
  if (!outfile) {
    cerr << "Failed to open the file!";
  }
  // I need to insert the data of parameters in the leaves class
  // then I start to insert each single leaf one by one

  int data[8];
  unsigned int data1[2];
  int p[3];
  p[0] = this->position;
  p[1] = this->position1;
  p[2] = this->suffix_start;
  outfile.write((char *)p, sizeof(int) * 3);
  for (int t = 0; t < p[1]; t++) {
    Leaf *leaf_tmp = this->getLeaf(t);
    int leafsize = leaf_tmp->getLeaf_size();
    data[0] = leaf_tmp->getLeaf_size();
    data[1] = leaf_tmp->getOffset_size();
    data[2] = leaf_tmp->getCode_size();
    data[3] = leaf_tmp->getPrefix_size();
    data[4] = leaf_tmp->getDecode_interval();
    data[5] = leaf_tmp->getValuenum();
    data[6] = leaf_tmp->getStringnum();
    data[7] = leaf_tmp->leaf_data;
    data1[0] = leaf_tmp->node_first;
    data1[1] = leaf_tmp->node_last;

    outfile.write((char *)data, sizeof(int) * 8);
    outfile.write((char *)data1, sizeof(unsigned int) * 2);
    outfile.write(leaf_tmp->pointerLeaf, leafsize);
  }

  int prefix_index = this->fullindex.size();
  int suffix_index = this->index_encode_suffix.size();
  int decode_index = this->index_decode.size();
  int size[3];
  size[0] = prefix_index;
  size[1] = suffix_index;
  size[2] = decode_index;
  outfile.write((char *)size, sizeof(int) * 3);
  int encode_p[3];
  int decode_p[3];
  for (int t = 0; t < prefix_index; t++) {
    encode_p[0] = fullindex[t].getLevel();
    encode_p[1] = fullindex[t].getLevelnum();
    encode_p[2] = fullindex[t].getIndexnodesize();

    outfile.write((char *)encode_p, sizeof(int) * 3);
    outfile.write(fullindex[t].indexpointer, encode_p[2]);
  }
  for (int m = 0; m < suffix_index; m++) {
    encode_p[0] = index_encode_suffix[m].getLevel();
    encode_p[1] = index_encode_suffix[m].getLevelnum();
    encode_p[2] = index_encode_suffix[m].getIndexnodesize();

    outfile.write((char *)encode_p, sizeof(int) * 3);
    outfile.write(index_encode_suffix[m].indexpointer, encode_p[2]);
  }
  for (int n = 0; n < decode_index; n++) {
    decode_p[0] = index_decode[n].getLevel();
    decode_p[1] = index_decode[n].getLevelnum();
    decode_p[2] = index_decode[n].getIndexnodesize();

    outfile.write((char *)decode_p, sizeof(int) * 3);
    outfile.write(index_decode[n].indexpointer, decode_p[2]);
  }

  cout << "Write the file successfully" << endl;
  outfile.close();
}

void Leaves::readFile(string filename) {
  ifstream infile(filename, ios::binary);
  if (!infile) {
    cerr << "Failed to open the file!";
  }
  // First, it will read the dictionary from the file
  // and it will build the dictionary leaf by leaf

  if (infile.fail()) {
    cout << "the reading procces failed!" << endl;
  }
  int data[8];
  unsigned int data1[2];
  int p[3];
  infile.read((char *)p, sizeof(int) * 3);
  this->position = p[0];
  this->position1 = p[1];
  this->suffix_start = p[2];
  for (int i = 0; i < p[1]; i++) {
    Leaf leaf_tmp;

    infile.read((char *)data, sizeof(int) * 8);
    infile.read((char *)data1, sizeof(int) * 2);
    leaf_tmp.setLeaf_size(data[0]);
    leaf_tmp.setOffset_size(data[1]);
    leaf_tmp.setCode_size(data[2]);
    leaf_tmp.setPrefix_size(data[3]);
    leaf_tmp.setDecode_interval(data[4]);
    leaf_tmp.setValuenum(data[5]);
    leaf_tmp.setStringnum(data[6]);
    leaf_tmp.leaf_data = data[7];
    leaf_tmp.node_first = data1[0];
    leaf_tmp.node_last = data1[1];
    infile.read(leaf_tmp.pointerLeaf, leaf_tmp.getLeaf_size());
    this->Insert(leaf_tmp);
  }
  int encode_p[3];
  int decode_p[3];
  int size[3];
  infile.read((char *)size, sizeof(int) * 3);
  int prefix_index = size[0];
  int suffix_index = size[1];
  int decode_index = size[2];
  for (int i = 0; i < prefix_index; i++) {
    encodingindexNode en_tmp;
    infile.read((char *)encode_p, sizeof(int) * 3);
    en_tmp.setLevel(encode_p[0]);
    en_tmp.setLevelnum(encode_p[1]);
    en_tmp.setIndexnodesize(encode_p[2]);
    infile.read(en_tmp.indexpointer, en_tmp.getIndexnodesize());
    this->fullindex.push_back(en_tmp);
  }

  for (int n = 0; n < suffix_index; n++) {
    encodingindexNode en_tmp;
    infile.read((char *)encode_p, sizeof(int) * 3);
    en_tmp.setLevel(encode_p[0]);
    en_tmp.setLevelnum(encode_p[1]);
    en_tmp.setIndexnodesize(encode_p[2]);
    infile.read(en_tmp.indexpointer, en_tmp.getIndexnodesize());
    this->index_encode_suffix.push_back(en_tmp);
  }

  for (int m = 0; m < decode_index; m++) {
    decodingindexNode de_tmp;
    infile.read((char *)decode_p, sizeof(int) * 3);
    de_tmp.setLevel(decode_p[0]);
    de_tmp.setLevelnum(decode_p[1]);
    de_tmp.setIndexnodesize(decode_p[2]);
    infile.read(de_tmp.indexpointer, de_tmp.getIndexnodesize());
    this->index_decode.push_back(de_tmp);
  }

  infile.close();
}
