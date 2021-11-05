class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,bool> ump;
        for(auto &num:nums){
            if(ump[num]) return true;
            ump[num]=true;
        }
        return false;
    }
};