// problem link : https://leetcode.com/problems/maximum-product-after-k-increments/
// solution : below code

class Solution {
public:
    long long modMul(long long a,long long b,long long mod){
        return ((a%mod)*(b%mod))%mod;
    }
    int maximumProduct(vector<int>& nums, int k) {
        double sm=0;
        int n=nums.size();
        priority_queue<pair<int,int>> pq;
        for(int i=0;i<n;i++){
            sm+=nums[i];
            pq.push({-nums[i],i});
        }
        int mean=ceil(sm/n);
        while(pq.size()>0 and k>0){
            pair<long long,long long> top=pq.top();
            pq.pop();
            top.first=abs(top.first);
            nums[top.second]+=1;
            pq.push({-(top.first+1),top.second});
            k--;
        }
        long long mod=1e9 + 7;
        long long ans=1;
        for(auto num:nums){
            ans=modMul(ans,num,mod);
        }
        return ans;
    }
};
