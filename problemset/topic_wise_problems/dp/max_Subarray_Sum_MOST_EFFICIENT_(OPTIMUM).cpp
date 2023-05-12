class Solution {
public:
    
    int maxSubArray(vector<int>& nums) {
        int mx=0,mn=INT_MIN;
        mn=max(mn,*(nums.end()-1));
        mx=max(mx,*(nums.end()-1));
        for(int i=nums.size()-2;i>=0;i--){
            mn=max(mn,nums[i]);
            nums[i]+=max(0,nums[i+1]);
            mx=max(mx,nums[i]);
        }
        if(mn<1) return mn;
        if(mx==0 && mn<0) mx=mn;
        return mx;
    }
};