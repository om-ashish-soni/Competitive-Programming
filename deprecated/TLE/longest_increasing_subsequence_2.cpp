// problem link : https://leetcode.com/contest/weekly-contest-310/problems/longest-increasing-subsequence-ii/
// solution : below code

class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        map<int,int> s;
        int n=nums.size();
        vector<int> dp(n,1);
        map<int,int> mp;
        for(int i=n-1;i>=0;i--){
            // cout<<"i : "<<i<<" , num : "<<nums[i]<<endl;
            int num=nums[i];
            int key=num;
            int range=n-1;
            int index=n-1;
            if(mp.count(num)) dp[i]=max(dp[i],mp[num]);
            
            while(key<=num+k){
                
                range=min(range,index);
                auto it=s.lower_bound(key+1);
                if(it==s.end()) break;
                key=it->first;
                index=it->second;
                // cout<<"key"<<" : "<<key<<" , index : "<<index<<endl;
                if(key<=num+k && index<=range){
                    dp[i]=max(dp[i],dp[index]+1);
                }
            }
            mp[num]=dp[i];
            s[num]=i;
            // cout<<"dp["<<i<<"] = "<<dp[i]<<endl;
        }
        int mx=0;
        for(auto num:dp){
            mx=max(mx,num);
        }
        return mx;
    }
};
