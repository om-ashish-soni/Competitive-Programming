// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
public:
    bool isChangeOccured(vector<vector<int>>& edges,vector<int>&dist){
        bool isChange=false;
        for(auto &edge:edges){
            int u=edge[0],v=edge[1],w=edge[2];
            if(dist[u]<INT_MAX && dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                isChange=true;
            }
        }
        return isChange;
    }
	int isNegativeWeightCycle(int n, vector<vector<int>>&edges){
	    vector<int> dist(n,INT_MAX);
	    dist[0]=0;
	    for(int i=0;i<n;i++) if(false==isChangeOccured(edges,dist)) return 0;
        return (isChangeOccured(edges,dist))?1:0;
	}
};

// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n, m;
		cin >> n >> m;
		vector<vector<int>>edges;
		for(int i = 0; i < m; i++){
			int x, y, z;
			cin >> x >> y >> z;
			edges.push_back({x,y,z});
		}
		Solution obj;
		int ans = obj.isNegativeWeightCycle(n, edges);
		cout << ans <<"\n";
	}
	return 0;
}  // } Driver Code Ends
