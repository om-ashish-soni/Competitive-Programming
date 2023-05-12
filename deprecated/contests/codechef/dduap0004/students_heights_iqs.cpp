// Problem link : https://www.codechef.com/problems/CCBTS04
// Solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

unordered_map<int,int> memo;
int mod=1e9+7;
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}
int hdq(int a[],int b[],int n,int index){
	if(memo.count(index)) return memo[index];
	int ctr=1;
	for(int i=index+1;i<n;i++){
		if(a[i]>a[index] && b[i]<b[index]){
			ctr=max(ctr,1+hdq(a,b,n,i));
		}
	}
	memo[index]=ctr;
	return ctr;
}
void solve(){
	int n;
	cin>>n;
	int a[n],b[n];
	scan(a,n);
	scan(b,n);
	memo.clear();
	int ans=hdq(a,b,n,0);
	for(int i=1;i<n;i++){
		ans=max(ans,hdq(a,b,n,i));
	}
	cout<<ans<<endl;
}
signed main(){
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	// seive();
	// seiveWithHPLP();
	// seiveWithAllFactors();
	// seiveWithAllPrimes();
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
