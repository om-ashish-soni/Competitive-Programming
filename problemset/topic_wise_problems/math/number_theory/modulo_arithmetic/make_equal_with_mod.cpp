// problem link : https://codeforces.com/problemset/problem/1656/C
// solution : below code

#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
void print(bool b){
    if(b) cout<<"YES";
    else cout<<"NO";
    cout<<endl;
}
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
    sort(arr,arr+n);
    
    bool isOne=false,isTwo=false;
    bool isZero=(arr[0]==0);
    for(int i=0;i<n;i++){
        if(arr[i]==1){
            isOne=true;
        }else if(arr[i]==2){
            isTwo=true;
        }
    }
    if(isOne){
        // if(isZero || isTwo){
        //     return print(false);
        // }
        // return print(true);
        for(int i=1;i<n;i++){
            if(arr[i]-arr[i-1]==1) return print(false);
        }
        return print(true);
    }
    return print(true);
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
