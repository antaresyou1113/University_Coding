class Solution {
 public:
  int maxSubArrayLen(vector<int>& nums, int k) {
    int sum = 0;
    int res = 0;
    unordered_map<int, int> hash;
    // when there is no value, the sum is 0
    hash[0] = 0;
    int size = nums.size();
    for (int i = 0; i < size; i++) {
      sum += nums[i];
      // add the value into the sum variable
      if (sum == k) {
        // the position should add 1
        res = i + 1;
      } else if (hash.count(sum - k)) {
        // if the k equals to the sum from some values other than 0
        res = max(res, i - hash[sum - k] + 1);
      }
      if (!hash.count(sum)) {
        // if the sum does not exist in the hash table, insert it, make sure
        // this is the lowest i
        hash[sum] = i + 1;
      }
    }
    return res;
  }
};
