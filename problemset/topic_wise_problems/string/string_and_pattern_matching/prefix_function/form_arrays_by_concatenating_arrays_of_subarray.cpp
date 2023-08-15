// problem link : https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/description/
// solution : below code


class Solution {
public:
    void prefix_function(vector<int> & s,vector<int>& pf){
        int n=s.size();
        pf.resize(n);
        pf[0]=0;
        for(int i=1;i<n;i++){
            int j=pf[i-1];
            while(j>0 && s[i]!=s[j]){
                j=pf[j-1];
            }
            if(s[i]==s[j]){
                j++;
            }
            pf[i]=j;
        }
        // Time complexity : O(n)
    }
    void kmp(vector<int> &  s,vector<int> & pattern,vector<int>&match){
        int pz=pattern.size();
        int pos(-1),i(0),j(0);
        vector<int> pf;
        prefix_function(pattern,pf);
        // for(auto num:pf) cout<<num<<" ";cout<<endl;
        while(i<s.size()){
            // cout<<i<<" vs "<<s.size()<<" , "<<j<<" vs "<<pf.size()<<endl;
            if(s[i]==pattern[j]){
                j++;
                i++;
            }else{
                if(j!=0){
                    j=pf[j-1];
                }else i++;
            }
            // cout<<j<<" vs "<<pattern.size()<<endl;
            if(j==pattern.size()){
                match.push_back(i-pz);
                j=pf[j-1];
            }
        }
    }
    bool canChoose(vector<vector<int>>& groups, vector<int>& nums) {
        int n=groups.size();
        int m=nums.size();
        vector<int> dp(m,0);
        for(int i=0;i<n;i++){
            vector<int> match;
            kmp(nums,groups[i],match);
            for(int ind:match){
                int index=ind+groups[i].size()-1;
                int left=0;
                if(ind-1>=0) left=dp[ind-1];
                if(left>=i){
                    dp[index]=max(dp[index],i+1);
                }
            }
            for(int j=1;j<m;j++){
                
                dp[j]=max(dp[j],dp[j-1]);
            }
            // for(auto num:dp) cout<<num<<" ";cout<<endl;
        }
        return dp.back() >= n;
    }
};