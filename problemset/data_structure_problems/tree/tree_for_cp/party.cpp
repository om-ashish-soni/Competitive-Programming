// problem link : https://codeforces.com/problemset/problem/115/A
// solution : below code
#include<bits/stdc++.h>
#define int long long 
#define endl "\n"
using namespace std;
void print(bool b){
	cout<<((b)?("YES"):("NO"))<<endl;
}
int dfs(vector<vector<int>>& tree,int start){
	int dep=0;
	// compute depth

	for(auto node:tree[start]){
		dep=max(dep,dfs(tree,node));
	}
	// return depth
	return 1+dep;
}
void solve(){
	int n;cin>>n;
	vector<vector<int>> tree(n+1);
	for(int i=1;i<=n;i++){
		int sup;cin>>sup;sup=max(sup,0LL);
		tree[sup].push_back(i);
	}
	// for(int i=0;i<=n;i++){
	// 	cout<<i<<" \n\t";
	// 	for(auto node:tree[i]) cout<<node<<" ";cout<<endl;
	// }
	cout<<dfs(tree,0)-1<<endl;
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
