// problem link : https://cses.fi/problemset/task/1744
// solution : below code

void solve(int testcase) {
 
    int n, m;
    read(n, m);
    if(n>m) swap(n,m);
    vvi dp(n + 1, vi(m + 1, INT_MAX));
    F(i,0,n+1){
        dp[i][0]=0;
    }
    F(j,0,m+1){
        dp[0][j]=0;
    }
    F(i, 1, min(n,m) + 1) {
        dp[i][i] = 0;
    }
 
    F(i, 1, n+1) {
        F(j,i+1,m+1) {
            int d=j-i;
            F(k,1,j){
                int l1=min(i,k);
                int r1=max(i,k);
                int l2=min(i,j-k);
                int r2=max(i,j-k);
                dp[i][j]  = min(dp[i][j],1 + (dp[l1][r1] + dp[l2][r2]));  
            }
            F(k,1,i){
                int l1=min(k,j);
                int r1=max(k,j);
                int l2=min(i-k,j);
                int r2=max(i-k,j);
                dp[i][j]  = min(dp[i][j],1 + (dp[l1][r1] + dp[l2][r2]));  
            }
        }
    }
    println(dp[n][m]);
 
}