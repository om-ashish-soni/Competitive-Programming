// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
//User function template for C++

class Solution
{
	public:
    //Function to return a list of lists of integers denoting the members 
    //of strongly connected components in the given graph.
    //Function to find number of strongly connected components in the graph.
	void topoSort(stack<int>& topo,vector<vector<int>>& adj,int V,vector<bool>& visited,int i){
	    if(i>=V) return;
	    visited[i]=true;
	    for(auto neb:adj[i]) if(!visited[neb]) topoSort(topo,adj,V,visited,neb);
	    topo.push(i);
	}
	void revDfs(vector<vector<int>>& transpose,int V,vector<int>& sccComp,vector<bool>& visited,int i){
	    if(i>=V) return;
	    visited[i]=true;
	    for(auto neb:transpose[i]){
	        if(!visited[neb]) revDfs(transpose,V,sccComp,visited,neb);
	    }
	    sccComp.push_back(i);
	    return;
	}
    vector<vector<int>> kosaraju(int V, vector<int> adj[])
    {
        vector<vector<int>> adj1(V);
        vector<vector<int>> transpose(V);
        for(int i=0;i<V;i++){
            for(auto node:adj[i]){
                adj1[i].push_back(node);
                transpose[node].push_back(i);
            }
        }
        stack<int> topo;
        vector<bool> visited(V,false);
        for(int i=0;i<V;i++) if(!visited[i]) topoSort(topo,adj1,V,visited,i);
        for(int i=0;i<V;i++) visited[i]=false;
        vector<vector<int>> scc;
        int comps=-1;
        
        while(!topo.empty()){
            int top=topo.top();
            topo.pop();
            if(!visited[top]){ 
                scc.push_back(*new vector<int>);
                comps++;
                vector<int>& sccComp=scc[comps];
                revDfs(transpose,V,sccComp,visited,top);
            }
        }
        for(auto &component:scc){
            sort(component.begin(),component.end());
        }
        sort(scc.begin(),scc.end());
        return scc;
        //code here
    }
    vector<vector<int>> tarjans(int V, vector<int> adj[])
    {
        return kosaraju(V,adj);   
        //code here
    }
};
// { Driver Code Starts.


int main()
{
    
    int t;
    cin >> t;
    while(t--)
    {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        for(int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        vector<vector<int>> ptr = obj.tarjans(V, adj);

        for(int i=0; i<ptr.size(); i++)
        {
            for(int j=0; j<ptr[i].size(); j++)
            {
                if(j==ptr[i].size()-1)
                    cout<<ptr[i][j];
                else
                    cout<<ptr[i][j]<<" ";
            }
            cout<<',';
        }
        cout<<endl;
    }

    return 0;
}

  // } Driver Code Ends
