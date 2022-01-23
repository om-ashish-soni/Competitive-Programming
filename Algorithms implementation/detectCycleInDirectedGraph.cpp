// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic1(vector<vector<int>> &adj,int V,int i,vector<bool>&recStack,vector<bool>&visited){
        if(i>=V) return false;
        recStack[i]=true;
        visited[i]=true;
        vector<int>& friends=adj[i];
        for(auto node:friends){
            if(!visited[node]){
                if(isCyclic1(adj,V,node,recStack,visited)) return true;
            }else if(recStack[node]){
                return true;
            }
        }
        recStack[i]=false;
        return false;
    }
    bool isCyclic(int V, vector<int> adj[]) {
        // code here
        vector<bool> recStack(V,0);
        vector<bool> visited(V,0);
        vector<vector<int>> adj1(V);
        for(int i=0;i<V;i++){
            adj1[i]=adj[i];
        }
        for(int i=0;i<V;i++) 
            if(!visited[i] && isCyclic1(adj1,V,i,recStack,visited)) 
                return true;
        return false;
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
