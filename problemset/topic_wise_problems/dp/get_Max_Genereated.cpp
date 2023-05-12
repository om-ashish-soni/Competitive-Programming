class Solution {
public:
    int getMax(int n,vector<int> &memo,int &mx){
        if(n==0 || n==1) return n;
        if(memo[n] != -1) return memo[n];
        if(n&1) memo[n]=getMax(n/2,memo,mx)+getMax(1+n/2,memo,mx);
        else memo[n]=getMax(n/2,memo,mx);
        mx=max(mx,memo[n]);
        return memo[n];
    }
    int getMaximumGenerated(int n) {
        if(n==0 || n==1) return n;
        vector<int> v(n+1,-1);
        v[0]=0;
        v[1]=1;
        int mx=0;
        getMax(n,v,mx);
        for(int i=0;i<v.size();i++){
            if(v[i] == -1) v[i]=getMax(i,v,mx);
        }
        return mx;
    }
};