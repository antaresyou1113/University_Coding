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

void stringGenerator(char **str, int length);

void bubbleString(char *pA[], int length);

char *createString();

void Show(char **p, int length);

void write_csv(string filename, vector<string> vals);

vector<string> read_csv(string filename);

void sort_string(string *in_array, int n, string *out_array);

void sort_string(string *in_array, int n, string *out_array) {
  vector<string> strArray;
  int i, j = 0;
  for (int i = 0; i < n; i++) {
    strArray.push_back(in_array[i]);
  }
  sort(strArray.begin(), strArray.end());
  vector<string>::iterator st;
  for (st = strArray.begin(); st != strArray.end(); st++) {
    out_array[j++] = *st;
  }
}

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

void write_csv(string filename, vector<string> vals) {
  ofstream myFile(filename);

  // myFile << column ;;
  for (int i = 0; i < vals.size(); ++i) {
    myFile << vals.at(i) << "\n";
  }
  myFile.close();
}

void Show(char **p, int length) {
  for (int i = 0; i < length; i++) {
    cout << p[i] << endl;
  }
}

// create the string and return it.
char *createString() {
  int num = rand() % 10;
  char *pStr = new char[num + 1];
  int i = 0;
  for (i = 0; i < num; i++) {
    pStr[i] = (char)(97 + rand() % 26);  // from asc code to charactor
  }
  pStr[i] = '\0';
  return pStr;
}

void bubbleString(char *pA[], int length) {
  for (int i = 0; i < length - 1; i++) {
    for (int j = i + 1; j < length - 1 - i; j++)
      if (strcmp(pA[j], pA[i]) < 0) {
        pA[i] = pA[j];
      }
    cout << pA[i] << endl;
  }
}

void stringGenerator(char **str, int length) {
  srand(time(0));
  // int n = rand() % 60 + 1;
  int n = length;
  // cout << "number" << n << endl;
  while (n--) {
    // int k = rand() % 15 + 1;
    int k = 20;
    for (int i = 0; i < k; i++) {
      int x, s;
      s = rand() % 2;
      if (s == 1) {
        // x = rand() % ('Z' - 'A' + 1) + 'A';
        x = rand() % ('z' - 'a' + 1) + 'a';
      } else {
        x = rand() % ('z' - 'a' + 1) + 'a';
      }
      str[n][i] = x;
    }
    str[n][k] = '\0';
    // cout << "The string here is: " << str[n] << endl;
  }
}

int main() {
  int length = 500;
  char **pA = new char *[length];
  for (int i = 0; i < length; i++) {
    // pA[i] = createString();
    // cout<<pA[i]<<endl;
    pA[i] = new char[50];
  }

  stringGenerator(pA, length);

  for (int i = 0; i < length; i++) {
    cout << pA[i] << endl;
  }

  vector<string> strs;
  vector<string> strs1;
  for (int i = 0; pA[i] && *pA[i] != '\0'; i++) {
    strs.push_back(&(*pA[i]));
  }

  // write_csv("testfile.csv", "values", strs);

  // strs = read_csv("testfile.csv");

  string test_in[length];
  string test_out[length];
  for (int i = 0; i < strs.size(); i++) {
    // cout << strs[i] << " The value from the readin file!" << endl;
    test_in[i] = strs[i];
  }

  sort_string(test_in, length, test_out);

  for (int t = 0; t < length; t++) {
    cout << test_out[t] << " The sorted result " << endl;
    strs1.push_back(test_out[t]);
  }
  write_csv("sorted result.csv", strs1);

  vector<string> strs2;
  strs2 = read_csv("sorted result.csv");
  for (int i = 0; i < strs2.size(); i++) {
    cout << strs2[i] << " The result from the read_in method: " << endl;
	cout<<i<<endl;
  }

  for (int i = 0; i < length; i++) {
    delete[] pA[i];
  }
  delete[] pA;
  // bubbleString(pA, length);
  // Show(pA, length);
  return 0;
}
