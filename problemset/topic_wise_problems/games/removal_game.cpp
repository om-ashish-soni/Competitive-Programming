// problem link : https://cses.fi/problemset/task/1097
// solution : below code

void solve(int testcase) {
 
    int n;
    read(n);
    vi v(n);
    readv(v);
    vvi dp(n,vi(n,0));
    F(i,0,n){
        dp[i][i]=v[i];
        if(i+1<n){
            dp[i][i+1]=max(v[i],v[i+1]);
        }
    }
    F(d,2,n){
        F(i,0,n-d){
            int j=i+d;
            int left=0,mid=0,right=0;
            left=v[j]+min(dp[i+1][j-1],dp[i][j-2]);
            right=v[i]+min(dp[i+1][j-1],dp[i+2][j]);
            dp[i][j]=max(left,right);
        }
    }
    println(dp[0][n-1]);
}