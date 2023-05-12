// problem link : https://codeforces.com/problemset/problem/1675/D
// solution : below code

#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}
void dfs(vector<vector<int>>& graph,int root,vector<int>& recStack,vector<vector<int>>& soln){
    recStack.push_back(root);
    if(graph[root].size()==0){
        soln.push_back(recStack);
        recStack.clear();
        return;
    }
    for(auto node:graph[root]){
        dfs(graph,node,recStack,soln);
    }
    return;
}
void solve(){
    int n;cin>>n;int arr[n];scan(arr,n);
    vector<vector<int>> graph(n+1);
    int root=-1;
    for(int i=0;i<n;i++){
        if(arr[i]==i+1){
            root=i+1;
        }else{
            graph[arr[i]].push_back(i+1);
        }
    }
    vector<vector<int>> soln;
    vector<int> recStack;
    dfs(graph,root,recStack,soln);

    cout<<soln.size()<<endl;
    for(auto& row:soln){
        cout<<row.size()<<endl;
        for(auto node:row) cout<<node<<" ";cout<<endl;
    }
    cout<<endl;
}   

signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    int t=1;
    cin>>t;
    while(t--){
        solve();    
    }
    return 0;
}
