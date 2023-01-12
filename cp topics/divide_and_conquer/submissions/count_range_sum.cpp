// problem link : https://leetcode.com/problems/count-of-range-sum/description/
// solution : below code

#define ll long long
class Solution {
public:
    ll lower=0;
    ll upper=0;
    vector<ll> nums;
    ll ctr=0;
    vector<ll> dnc(ll l,ll r,ll dir=-1){
        if(l>r) return {};
        if(l==r){
            if(lower<=nums[l] && nums[l]<=upper){
                ctr++;
            }   
            return {nums[l]};
        }
        ll n=r-l+1;
        vector<ll> prefsuff(n,0);
        for(ll i=0;i<n;i++){
            prefsuff[i]=nums[i+l];
        }
        ll mid=(l+r)/2;
        vector<ll> left=dnc(l,mid,0);
        vector<ll> right=dnc(mid+1,r,1);
        sort(right.begin(),right.end());
        ll rz=right.size();
        for(ll i=0;i<left.size();i++){
            ll fd=lower-left[i];
            ll sd=upper-left[i];
            ll fi=lower_bound(right.begin(),right.end(),fd)-right.begin();
            ll si=upper_bound(right.begin(),right.end(),sd)-right.begin();
            ll delta=si-fi;
            ctr+=delta;
        }
        if(dir==1){
            for(int i=1;i<n;i++){
                prefsuff[i]+=prefsuff[i-1];
            }
        }else{
            for(int i=n-2;i>=0;i--){
                prefsuff[i]+=prefsuff[i+1];
            }
        }
        return prefsuff;
    }
    ll countRangeSum(vector<int>& nums, ll lower, ll upper) {
        this->lower=lower;
        this->upper=upper;
        for(auto num:nums){
            this->nums.push_back(num);
        }
        this->ctr=0;
        ll n=nums.size();
        ll l=0;
        ll r=n-1;
        dnc(l,r);
        return ctr;
    }
};
