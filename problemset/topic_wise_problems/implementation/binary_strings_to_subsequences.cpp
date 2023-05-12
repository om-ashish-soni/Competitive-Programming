// problem link : https://codeforces.com/problemset/problem/1399/D
// solution : below code

void solve(int t){
    int n;
    read(n);
    string s;
    read(s);
    vi dp(n,0);
    set<int> ones,zeros;
    int ctr=0;
    F(i,0,n){
        if(s[i]=='0'){
            if(ones.size()==0){
                ctr++;
                ones.insert(ctr);
            }
            dp[i]=*ones.begin();
            ones.erase(dp[i]);
            zeros.insert(dp[i]);
        }else{
            if(zeros.size()==0){
                ctr++;
                zeros.insert(ctr);
            }
            dp[i]=*zeros.begin();
            zeros.erase(dp[i]);
            ones.insert(dp[i]);
        }
    }
    int mx=*max_element(ALL(dp));
    println(mx);
    printv(dp);
}
