class Solution {
public:

    int lengthOfLIS(vector<int>& nums) {
        vector<int> memo;
        for(auto num:nums){
            auto found=lower_bound(memo.begin(),memo.end(),num);
            if(found==memo.end()) memo.push_back(num);
            else *found=num;
        }
        return memo.size();
    }
};