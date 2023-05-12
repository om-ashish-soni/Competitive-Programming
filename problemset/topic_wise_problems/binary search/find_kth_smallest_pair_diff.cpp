// problem link : https://leetcode.com/problems/find-k-th-smallest-pair-distance/description/
// solution : below code

class Solution {
public:
    unordered_map<int,int> mp;
    pair<long long,long long> calcdiff(vector<int> & v,int diff){
        int n=v.size();
        long long less=0;
        long long self=0;
        for(int i=0;i<n;i++){
            int key=v[i]+diff;
            int first=lower_bound(v.begin(),v.end(),key)-(v.begin());
            less+=first-i-1;
            self+=mp[key];
        }
        return {less,self};
    }
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        for(auto num:nums) mp[num]++;
        int n=nums.size();
        int l=0;
        int r=(1e6)+10;
        int ans=-1;
        int total=n*(n-1)/2;
        while(l<=r){
            bool flag=(l==r);
            int mid=(l+r)/2;
            int diff=mid;
            pair<long long,long long> pr=calcdiff(nums,diff);
            int left=pr.first;
            int self=pr.second;
            if(left>k-1){
                r=mid;
            }else{
                if(left+self>=k){
                    ans=diff;
                }
                l=mid+1;
            }
            if(flag) break;
        }
        return ans;
    }
};