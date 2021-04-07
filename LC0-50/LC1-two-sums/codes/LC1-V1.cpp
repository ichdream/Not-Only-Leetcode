class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int nSize = nums.size();
        vector<int> res(2, -1);
        if(nSize <= 1) return vector<int>{};
        unordered_map<int, int> mp;
        for(int i = 0; i < nSize; i++) {
            int tmp = target - nums[i];
            auto it = mp.find(tmp);
            if(it != mp.end()) {
                res[0] = it->second;
                res[1] = i;
                break;
            }
            else mp[nums[i]] = i;
        }
        return res;
    }
};