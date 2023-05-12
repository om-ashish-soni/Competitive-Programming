// problem link : https://codeforces.com/problemset/problem/1511/C
//  solution : below code
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
	int n,q;cin>>n>>q;
	vector<int> colors(51,-1);
	vector<int> lst(n+1);
	for(int i=1;i<=n;i++){
		cin>>lst[i];
	}
	for(int i=n;i>=1;i--){
		colors[lst[i]]=i;
	}
	for(int i=0;i<q;i++){
		int color;cin>>color;
		cout<<colors[color]<<" ";
		for(int clr=1;clr<51;clr++){
			if(colors[clr]<colors[color]){
				colors[clr]+=1;
			}
		}
		colors[color]=1;
	}	
	cout<<endl;
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
