// problem link : https://leetcode.com/problems/contains-duplicate-iii/
// solution : below code

#define ll long long
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n=nums.size();
        vector<pair<ll,ll>> v(n);
        for(int i=0;i<n;i++) v[i]={nums[i],i};
        sort(begin(v),end(v));
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                ll val_diff=abs(v[i].first-v[j].first);
                if(val_diff>t) break;
                if(abs(v[i].second-v[j].second)<=k) return true;
            }
        }
        return false;
    }
};
