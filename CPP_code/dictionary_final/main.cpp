#include"Leaves.h"
#include "Leaf.h"
int main() {

  vector<string> strs;
     strs = read_csv("sorted result.csv");
     Leaves leaves1;
     leaves1.bulkLoad(strs);
     leaves1.encodingIndexcreation();
     leaves1.bulkLoadSuffix(strs);
     leaves1.encodingIndexcreationSuffix();
     leaves1.decodingIndexcreation();
     leaves1.generateFile("test");
     Leaves leaves2;
     leaves2.readFile("test");
     leaves2.serial_task_encode(strs,0);
     leaves2.concurrent_task_encode(strs,0);

     vector<string> str1;
     string a = "a";
     str1.push_back(a);
     leaves2.serial_task_encode(str1,1);
     leaves2.concurrent_task_encode(str1,1);

     leaves2.serial_task_encode(str1,2);
     leaves2.concurrent_task_encode(str1,2);

     vector<int> codes;
     for(int i=0; i<strs.size(); i++){
       codes.push_back(i);
     }
     leaves2.serial_task_decode(codes);
     leaves2.concurrent_task_decode(codes);


  return 0;
}
