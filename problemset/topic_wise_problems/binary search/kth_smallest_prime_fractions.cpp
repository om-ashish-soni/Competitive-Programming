// problem link : https://leetcode.com/problems/k-th-smallest-prime-fraction/description/
// solution : below code

class Solution {
public:
    #define ll long long
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        k--;
        ll n=arr.size();
        ll l=1;
        ll r=(1e5+10);
        ll pivot=1;
        vector<ll> curr_stop(n,n);
        while(l<=r){
            bool flag=(l==r);
            ll mid=(l+r)/2;
            ll frac=mid;
            ll taken=0;
            vector<ll> curr_start=curr_stop;
            for(int i=0;i<n;i++){
                ll key=arr[i]*frac;
                int start=upper_bound(arr.begin()+i,arr.begin()+curr_stop[i],key)-arr.begin();
                curr_start[i]=start;
                taken+=curr_stop[i]-start;    
            }
            if(k>taken){
                pivot=min(pivot,frac);
                k-=taken;
                curr_stop=curr_start;
                r=mid;
            }else{
                l=mid+1;
            }
            if(flag) break;
        }
        vector<pair<ll,ll>> prs;
        for(int i=0;i<n;i++){
            ll key=arr[i]*pivot;
            int start=upper_bound(arr.begin()+i,arr.begin()+curr_stop[i],key)-arr.begin();
            int stop=curr_stop[i];
            for(int j=start;j<stop;j++){
                prs.push_back({arr[i],arr[j]});
            }
        }
        sort(prs.begin(),prs.end(),[](auto & a,auto & b){
            return a.first*b.second<a.second*b.first;
        });
        return {(int)prs[k].first,(int)prs[k].second};
    }
};