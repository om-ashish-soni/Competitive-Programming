// problem link : https://www.codechef.com/problems/KFIB
// Solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

const int M=2e5+10;
int memo[M]={0,0,0};
int mod=1e9+7;
int kfib(int n,int k){
	if(n<=k) return 1;
	if(memo[n] != 0) return memo[n];
	int ans=0;
	for(int i=1;i<=k;i++){
		ans=ans+kfib(n-i,k);
	}
	ans=ans%mod;
	memo[n]=ans;
	return ans;
}
signed main(){
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n,k;
	cin>>n>>k;
	if(k==1){
		cout<<1<<endl;
		return 0;
	}
	int ans=kfib(n,k);
	cout<<ans<<endl;
	return 0;
}
