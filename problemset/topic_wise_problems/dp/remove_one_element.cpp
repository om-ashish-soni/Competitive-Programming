// problem link : https://codeforces.com/problemset/problem/1272/D
// solution : below code

void solve(int t){
    int n;
    read(n);
    vi v(n);
    readv(v);
    vi pref(n,1),suff(n,1);
    F(i,1,n){
        if(v[i]>v[i-1]){
            pref[i]=1+pref[i-1];
        }
    }
    FND(i,n-2,0){
        if(v[i]<v[i+1]){
            suff[i]=1+suff[i+1];
        }
    }
    // printv(pref);
    // printv(suff);
    int mx=0;
    F(i,0,n){
        mx=max(mx,pref[i]);
        mx=max(mx,suff[i]);
        if(i+2<n){
            if(v[i]<v[i+2]) mx=max(mx,pref[i]+suff[i+2]);
        }
    }
    println(mx);
}