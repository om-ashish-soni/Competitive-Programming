// problem link : https://leetcode.com/problems/contains-duplicate-iii/description/
// solution : below code

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        set<pair<int,int>> window;
        for(int i=0;i<nums.size();i++){
            int so_far=i-indexDiff;
            int l=nums[i]-valueDiff;
            int r=nums[i]+valueDiff;
            while(window.size()>0){
                auto left_it=window.lower_bound({l,0});
                if(left_it == window.end()){
                    break;
                }
                int val=left_it->first;
                int index=left_it->second;
                if(val>r) break;
                if(index >= so_far){
                    return true;
                }else{
                    window.erase(left_it);
                }
            }
            window.insert({nums[i],i});
        }
        return false;
    }
};