// problem link : https://leetcode.com/problems/append-k-integers-with-minimal-sum/
// solution : below code

#define ll long long
class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        map<ll,bool> mp;
        for(auto num:nums) mp[num]=true;
        int sz=mp.size();
        vector<ll> v(sz);
        int index=1;
        v.push_back(0LL);
        for(auto &pr:mp){
            
            if(v.back() != pr.first){
                v[index]=pr.first;
                index++;   
            }
        }
        ll MAX=1e9;
        if(v.back()!=MAX) v.push_back(MAX);
        sz=v.size();
        ll ctr=0;
        ll sm=0;
        for(int i=0;i<sz-1;i++){
            ll start=v[i];
            ll end=v[i+1]-1;
            if(ctr>=k) break;
            int rem=k-ctr;
            end=min(start+rem,end);
            if(start<end){
                ctr+=end-start;
                sm+=(end*(end+1)/2)-(start*(start+1)/2);   
            }
            
        }
        return sm;
    }
};
