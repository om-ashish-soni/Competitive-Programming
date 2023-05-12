//  problem link : https://codeforces.com/problemset/problem/1336/A
// solution : below code
#include<bits/stdc++.h>
#define int long long 
#define endl "\n"
using namespace std;
void print(bool b){
	cout<<((b)?("YES"):("NO"))<<endl;
}
int dfs(vector<vector<int>>& tree,vector<int>& childs,vector<int>& levelOf,int start,int par,int level=0){
	// cout<<"s : "<<start<<" l: "<<level<<endl;
	levelOf[start]=level;
	for(auto node:tree[start]){
		if(node != par){
			childs[start]+=dfs(tree,childs,levelOf,node,start,level+1);
		} 
	}
	return childs[start]+1;
}
void solve(){
	int n,k;cin>>n>>k;
	vector<vector<int>> tree(n+1);
	vector<int> levelOf(n+1,-1),childs(n+1,0);
	for(int i=0;i<n-1;i++){
		int u,v;cin>>u>>v;
		tree[u].push_back(v);tree[v].push_back(u);
	}
	dfs(tree,childs,levelOf,1,-1,0);
	priority_queue<pair<int,int>> pq;
	for(int i=1;i<=n;i++){
		// cout<<i<<" "<<childs[i]<<endl;
		pq.push({levelOf[i]-childs[i],i});
	}
	int sm=0;
	while(k--){
		pair<int,int> top=pq.top();pq.pop();
		sm+=top.first;
		// cout<<top.first<<" "<<top.second<<" "<<endl;
	}
	cout<<sm<<endl;
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
