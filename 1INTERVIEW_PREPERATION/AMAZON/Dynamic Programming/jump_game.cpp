// problem link : https://leetcode.com/problems/jump-game/
// solution : below code

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n=nums.size();
        vector<int> v(n,false);
        v[n-1]=true;
        int next=n-1;
        for(int i=n-2;i>=0;i--){
            int limit=min(n-1,i+nums[i]);
            if(limit>=next){
                next=i;
                v[i]=true;
            }
        }
        return v[0];
    }
};
