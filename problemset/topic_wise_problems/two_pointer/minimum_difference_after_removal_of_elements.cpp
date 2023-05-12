// problem link : https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/description/
// solution : below code

class Solution {
public:
    #define ll long long
    long long minimumDifference(vector<int>& nums) {
        priority_queue<ll,vector<ll>,greater<ll>> pq2;
        priority_queue<ll> pq1;
        int n=nums.size();
        vector<ll> pref(n,0),suff(n,0);
        int n3=n/3;
        for(int i=0;i<n3;i++){
            pq1.push(nums[i]);
            pref[n3-1]+=nums[i];
        }
        for(int i=2*n3;i<n;i++){
            pq2.push(nums[i]);
            suff[2*n3]+=nums[i];
        }
        for(int i=n3;i<2*n3;i++){
            pq1.push(nums[i]);
            ll remove=pq1.top();
            pq1.pop();
            // cout<<"pref : ";cout<<i<<" :: pushed "<<nums[i]<<" removed "<<remove<<endl;
            pref[i]=pref[i-1];
            pref[i]+=nums[i]-remove;
        }

        for(int i=2*n3-1;i>=n3;i--){
            pq2.push(nums[i]);
            ll remove=pq2.top();
            pq2.pop();
            // cout<<"suff : ";cout<<i<<" :: pushed "<<nums[i]<<" removed "<<remove<<endl;
            suff[i]=suff[i+1];
            suff[i]+=nums[i]-remove;
        }
        // for(int i=0;i<n;i++) cout<<pref[i]<<" ";cout<<endl;
        // for(int i=0;i<n;i++) cout<<suff[i]<<" ";cout<<endl;
        ll mn=LLONG_MAX;
        for(int i=n3-1;i<2*n3;i++){
            // cout<<pref[i]<<" , "<<suff[i]<<" for I : "<<i<<endl;
            mn=min(mn,pref[i]-suff[i+1]);
        }
        return mn;
    }
};