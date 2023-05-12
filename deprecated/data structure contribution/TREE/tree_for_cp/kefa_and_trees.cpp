// Problem link : https://codeforces.com/problemset/problem/580/C
// Solution : below code
#include<bits/stdc++.h>
#define int long long 
#define endl "\n"
using namespace std;
void print(bool b){
	cout<<((b)?("YES"):("NO"))<<endl;
}
int dfs(vector<vector<int>>& tree,int m,vector<int>& isCat,int start,int par,int obs){
	if(obs>m) return 0;
	int calls=0,ways=0;
	for(auto node:tree[start]){
		if(node != par){
			calls++;
			ways+=dfs(tree,m,isCat,node,start,isCat[node]?obs+1:0);
		}
	}
	if(calls==0) return 1;
	return ways;
}
void solve(){
	int n,m;cin>>n>>m;
	vector<vector<int>> tree(n+1);
	vector<int> isCat(n+1);
	for(int i=1;i<=n;i++) cin>>isCat[i];
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		tree[u].push_back(v);tree[v].push_back(u);
	}
	cout<<dfs(tree,m,isCat,1,-1,isCat[1])<<endl;
}
signed main(){

	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	// cin>>t;
	while(t--){
		solve();
	}
}
