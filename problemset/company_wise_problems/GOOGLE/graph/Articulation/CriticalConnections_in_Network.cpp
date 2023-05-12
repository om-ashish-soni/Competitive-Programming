// problem link : https://leetcode.com/problems/critical-connections-in-a-network/
// solution : below code

#define vvi vector<vector<int>> 
#define vb vector<bool>
#define vi vector<int>
#define pb push_back
#define pii pair<int,int>
#define mpiib map<pii,bool>
class Solution {
public:
    vb ap,visited;
    vvi graph;
    vi low,disc;
    mpiib mp;
    mpiib con;
    vvi criticals;
    int time=0;
    void tarjans(int u,int parent){
        visited[u]=true;
        int children=0;
        low[u]=disc[u]=++time;
        for(auto &v:graph[u]){
            if(visited[v]==false){
                children++;
                tarjans(v,u);
                if(low[v]>disc[u]){
                    ap[u]=true;
                    mp[{u,v}]=true;
                    mp[{v,u}]=true;
                }
                low[u]=min(low[u],low[v]);
            }else{
                if(v!=parent){
                    low[u]=min(low[u],disc[v]);
                }
            }
        }
        if(parent==-1 and children>1){
            ap[u]=true;
        }
        if(graph[u].size()==1){
            ap[u]=true;
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        graph.resize(n);
        low.resize(n);
        disc.resize(n);
        ap.assign(n,false);
        visited.assign(n,false);
        for(auto &edge:connections){
            graph[edge[0]].pb(edge[1]);
            graph[edge[1]].pb(edge[0]);
        }
        for(int i=0;i<n;i++) if(visited[i]==false) tarjans(i,-1);
        for(auto &edge:connections){
            if(mp.count({edge[0],edge[1]})>0) criticals.pb(edge);
        }
        return criticals;
    }
};
