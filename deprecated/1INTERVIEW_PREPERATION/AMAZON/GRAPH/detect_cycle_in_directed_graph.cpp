// problem link : https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1/
// solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
  public:
    // Function to detect cycle in a directed graph.
    vector<bool> recstack,visited;
    bool isCyclic(vector<vector<int>>& adj,int node){
        if(recstack[node]) return true;
        recstack[node]=true;
        visited[node]=true;
        for(auto neb:adj[node]){
            if(visited[neb]){
                if(recstack[neb]==true) return true;
            }else{
                if(isCyclic(adj,neb)) return true;
            }
        }
        recstack[node]=false;
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        vector<vector<int>> graph(V);
        recstack.assign(V,false);
        visited.assign(V,false);
        for(int i=0;i<V;i++){
            for(auto node:adj[i]) graph[i].push_back(node);
        }
        for(int i=0;i<V;i++){
            if(visited[i]==false){
                if(isCyclic(graph,i)) return true;
            } 
        }
        return false;
        // code here
    }
};

// { Driver Code Starts.

int main() {

    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        for (int i = 0; i < E; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        cout << obj.isCyclic(V, adj) << "\n";
    }

    return 0;
}
  // } Driver Code Ends
