// problem link : https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/submissions/
// solution : below code

class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n=nums.size();
        unordered_map<int,int> hash1;
        vector<int> pref(n,0),suff(n,0);
        int mn=n+1;
        pref[0]=nums[0];
        for(int i=1;i<n;i++){
            pref[i]=pref[i-1]+nums[i];
        }
        for(int i=0;i<n;i++){
            if(pref[i]==x) mn=min(mn,i+1);
        }
        suff[n-1]=nums[n-1];
        
        for(int i=n-2;i>=0;i--){
            suff[i]=suff[i+1]+nums[i];
        }
        for(int i=n-1;i>=0;i--){
            if(suff[i]==x) mn=min(mn,n-i);
        }
        reverse(suff.begin(),suff.end());
        for(int i=0;i<n;i++){
            hash1[pref[i]]=i;
        }
        for(int i=0;i<n;i++){
            int rem=x-suff[i];
            if(rem>0 && hash1.count(rem)){
                int first=hash1[rem]+1;
                int second=i+1;
                mn=min(mn,first+second);
            }
        }
        
        if(mn==n+1) return -1;
        return mn;
    }
};
