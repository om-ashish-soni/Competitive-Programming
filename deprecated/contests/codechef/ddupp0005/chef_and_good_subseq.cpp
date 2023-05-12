// Problem link : https://www.codechef.com/problems/GDSUB
// Solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
inline int modAdd(int a,int b,int mod){
	return ((a%mod)+(b%mod))%mod;
}
void solve(){
	int mod=1e9+7;
	int n,k;
	int sum=0;
	cin>>n>>k;
	map<int,int> mp;
	for(int i=0;i<n;i++){
		int num;
		cin>>num;
		mp[num]++;
	}
	vector<int> v;
	for(auto &pr:mp) v.push_back(pr.second);
	int m=v.size();
	vector<int> memo(m+1,0);
	memo[0]=1;
	for(int i=0;i<m;i++){
		int backup=memo[0];
		int limit=min(i,k);
		for(int j=0;j<=limit;j++){
			int temp=memo[j+1];;
			memo[j+1]=modAdd(memo[j+1],backup*v[i],mod);
			backup=temp;
		}
	}
	int upto=min(m+1,k+1);
	for(int i=0;i<upto;i++){
		sum=modAdd(sum,memo[i],mod);
	}
	cout<<sum<<endl;
}
signed main(){
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	solve();
	return 0;
}
