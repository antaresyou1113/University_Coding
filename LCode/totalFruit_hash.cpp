class Solution {
public:
    int totalFruit(vector<int>& tree) {
        //hash map version
        int res = 0;
        int n = tree.size();
        int start = 0;
        unordered_map<int, int> m;
        for(int i=0; i<n; i++){
            //insert the value into the map
            m[tree[i]]++;
            while(m.size() > 2){
                if(--m[tree[start]] == 0){
                    //erase the value 
                    m.erase(tree[start]);
                }
                start++;
            }
            res = max(res, i - start + 1);
        }
        return res;
    }
};
