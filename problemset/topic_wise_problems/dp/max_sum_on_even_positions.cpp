// problem link : https://codeforces.com/problemset/problem/1373/D
// solution : below code

#define map unordered_map
void solve(int t){
    
    int n;
    read(n);
    vi v(n);
    readv(v);
    doit(v);
    int sm=0;
    vi v2;
    F(i,0,n){
        if(i&1) v2.pb(v[i]-v[i-1]);
        else sm+=v[i];
    }
    int sz=v2.size();
    int first=sm+kadene(v2);
    
    vi v3;
    F(i,2,n){
        if((i&1) == 0){
            v3.pb(v[i-1]-v[i]);
        }
    }
    int second=sm+kadene(v3);
    // println(first,second);
    int mx=max(first,second);
    println(mx);
}
