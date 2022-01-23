// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution
{
	public:
	//Function to return list containing vertices in Topological order. 
	void doTopoSort(vector<vector<int>>& adj,int V,int i,vector<int>&v,vector<bool>& visited){
	    if(visited[i]) return ;
	    if(i>=V) return;
	    visited[i]=true;
	    for(auto node:adj[i]){
	        doTopoSort(adj,V,node,v,visited);
	    }
	    v.push_back(i);
	    return;
	}
	vector<int> topoSort(int V, vector<int> adj[]) 
	{
	    vector<vector<int>> adj1(V);
	    for(int i=0;i<V;i++){
	        adj1[i]=adj[i];
	    }
	    vector<int> v;
	    vector<bool> visited(V,0);
	    for(int i=0;i<V;i++) doTopoSort(adj1,V,i,v,visited);
	    reverse(v.begin(),v.end());
	    return v;
	    // code here
	}
};

// { Driver Code Starts.

/*  Function to check if elements returned by user
*   contains the elements in topological sorted form
*   V: number of vertices
*   *res: array containing elements in topological sorted form
*   adj[]: graph input
*/
int check(int V, vector <int> &res, vector<int> adj[]) {
    
    if(V!=res.size())
    return 0;
    
    vector<int> map(V, -1);
    for (int i = 0; i < V; i++) {
        map[res[i]] = i;
    }
    for (int i = 0; i < V; i++) {
        for (int v : adj[i]) {
            if (map[i] > map[v]) return 0;
        }
    }
    return 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> E >> N;
        int u, v;

        vector<int> adj[N];

        for (int i = 0; i < E; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
        }
        
        Solution obj;
        vector <int> res = obj.topoSort(N, adj);

        cout << check(N, res, adj) << endl;
    }
    
    return 0;
}  // } Driver Code Ends
