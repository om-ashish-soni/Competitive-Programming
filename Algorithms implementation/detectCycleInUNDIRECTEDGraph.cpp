// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
  public:
    // Function to detect cycle in an undirected graph.
    bool isCycle1(vector<vector<int>>& adj,int V,int i,vector<bool>&visited,int par=-1){
        if(i>=V) return false;
        visited[i]=true;
        for(auto node:adj[i]){
            if(node == par) continue;
            if(visited[node]) return true;
            if(isCycle1(adj,V,node,visited,i)) return true;
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<vector<int>> adj1(V);
        for(int i=0;i<V;i++) adj1[i]=adj[i];
        vector<bool> visited(V,0);
        for(int i=0;i<V;i++){
            if(!visited[i] && isCycle1(adj1,V,i,visited)) return true;
        }return false;
    }
};

// { Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int V, E;
        cin >> V >> E;
        vector<int> adj[V];
        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        Solution obj;
        bool ans = obj.isCycle(V, adj);
        if (ans)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}  // } Driver Code Ends
