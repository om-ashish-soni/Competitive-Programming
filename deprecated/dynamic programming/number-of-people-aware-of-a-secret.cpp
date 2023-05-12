// problem link : https://leetcode.com/contest/weekly-contest-300/problems/number-of-people-aware-of-a-secret/
// solution : below code

class Solution {
public:
    int mod=1e9 + 7;
    inline int modAdd(int a,int b){
        return ((a%mod+b%mod)%mod+mod)%mod;
    }
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<int> v(n,0);
        v[0]=1;
        vector<int> pref=v;
        for(int i=1;i<n;i++){
            int shared_by=i-delay;
            int forgot_by=i-forget;
            int curr=0;
            if(forgot_by>=0){
                curr=modAdd(curr,-pref[forgot_by]);
            }
            if(shared_by>=0){
                curr=modAdd(curr,pref[shared_by]);
            }
            v[i]=curr;
            pref[i]=modAdd(pref[i-1],v[i]);
        }
        int total=0;
        for(int i=n-forget;i<n;i++){
            total=modAdd(total,v[i]);
        }
        return total;
    }
};
