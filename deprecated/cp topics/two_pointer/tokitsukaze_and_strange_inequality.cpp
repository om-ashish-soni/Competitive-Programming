// problem link : https://codeforces.com/problemset/problem/1677/A
// solution : below code
void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    int a[n];
    read(a,n);
    int total=0;
    vvi dp(n,vi(n,0));
    F(i,0,n){
    	int last=0;
    	FND(j,n-1,i+1){
    		if(a[i]>a[j]) last++;
    		dp[i][j]=last;
    	}
    	int first=0;
    	F(j,0,i){
    		if(a[i]>a[j]) first++;
    		dp[i][j]=first;
    	}
    }
    F(i,1,n-1){
    	F(j,i+1,n-1){
    		int prf=dp[j][i-1];
    		int suf=dp[i][j+1];
    		// cout<<i<<" "<<" : "<<prf<<" * "<<suf<<endl;
    		total+=prf*suf;
    	}
    }
    println(total);
}   
