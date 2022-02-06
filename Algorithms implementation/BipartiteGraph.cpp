// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
public:
    bool checkBipartite(vector<int>adj[],int color[],bool visited[],int start){
        vector<int>& childs=adj[start];
        for(auto child:childs){
            if(color[child]==color[start]) {
                // cout<<start<<" "<<child<<" false "<<endl;
                return false;
                
            }
            if(!visited[child]){ 
                visited[child]=true;
                color[child]=(!color[start]);
                if(false == checkBipartite(adj,color,visited,child)){
                    // cout<<start<<" "<<child<<" false "<<endl;
                    return false;
                }
            }
        }
        
        return true;
    }
	bool isBipartite(int V, vector<int>adj[]){
	    // Code here
	    int n=V;
	    int color[n];
	    memset(color,-1,sizeof(color));
	    bool visited[n];
	    memset(visited,0,sizeof(visited));
        	    
        for(int i=0;i<n;i++){
            if(!visited[i]){
                visited[i]=true;
                color[i]=1;
                
                if(false==checkBipartite(adj,color,visited,i)) return false;
            }
        }
        return true;
	}

};

// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int V, E;
		cin >> V >> E;
		vector<int>adj[V];
		for(int i = 0; i < E; i++){
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		Solution obj;
		bool ans = obj.isBipartite(V, adj);    
		if(ans)cout << "1\n";
		else cout << "0\n";  
	}
	return 0;
}  // } Driver Code Ends
