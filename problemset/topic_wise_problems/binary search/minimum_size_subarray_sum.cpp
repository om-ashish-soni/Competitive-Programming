// problem link : https://leetcode.com/problems/minimum-size-subarray-sum/
// solution : below code

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n=nums.size();
        int sm=0;
        int mn=n;
        for(auto num:nums) sm+=num;
        if(sm<target) return 0;
        vector<int> pref(n+1,0);
        for(int i=1;i<=n;i++){
            pref[i]=nums[i-1]+pref[i-1];
        }
        for(int i=1;i<=n;i++){
            if(pref[i]>=target){
                int diff=pref[i]-target;
                int index=lower_bound(pref.begin(),pref.end(),diff)-pref.begin();
                // cout<<"index : "<<index<<" vs i : "<<i<<endl;
                if(pref[i]-pref[index]>=target){
                    mn=min(mn,i-index);
                }else{
                    mn=min(mn,i-index+1);
                }
            }
        }
        return mn;
    }
};
