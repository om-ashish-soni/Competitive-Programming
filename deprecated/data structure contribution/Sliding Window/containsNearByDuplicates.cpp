class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,vector<int>> ump;
        int index=0;
        for(auto &num:nums) ump[num].push_back(index++);
        for(auto &num:nums){
            vector<int> &v=ump[num];
            for(int j=1;j<v.size();j++){
                if(v[j]-v[j-1] <= k) return true;
            }
        }
        return false;
    }
};