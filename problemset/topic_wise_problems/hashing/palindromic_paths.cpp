// problem link : https://codeforces.com/problemset/problem/1366/C
// solution : below code

void solve(int t){
    int n,m;
    read(n,m);
    vvi v(n,vi(m));
    readm(v);
    int sz=n-1+m-1+1;
    vector<vector<int>> mp(sz,vector<int>(2,0));
    F(i,0,n){
        F(j,0,m){
            mp[i+j][v[i][j]]++;
        }
    }
    int ctr=0;
    for(int i=0;i<sz/2;i++){
        int zeros=mp[i][0]+mp[sz-i-1][0];
        int ones=mp[i][1]+mp[sz-i-1][1];
        ctr+=min(zeros,ones);
    }
    println(ctr);
}