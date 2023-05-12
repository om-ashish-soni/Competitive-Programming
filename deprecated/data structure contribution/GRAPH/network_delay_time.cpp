// problem link : https://leetcode.com/problems/network-delay-time/
// solution : below code

#define pii pair<int,int> 
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pii>> graph(n+1);
        vector<int> dist(n+1,1e9 + 7);
        for(auto &way:times){
            graph[way[0]].push_back({way[1],way[2]});
        }
        //begin dijkstra
        
        priority_queue<pii> pq;
        dist[k]=0;
        pq.push({k,0});
        while(pq.size()>0){
            pii top=pq.top();pq.pop();
            int v=top.first;
            int d_v=top.second;
            if(dist[v] != d_v) continue;
            for(auto &way:graph[v]){
                int node=way.first;
                int weight=way.second;
                if(weight+dist[v] < dist[node]){
                    dist[node]=weight+dist[v];
                    pq.push({node,dist[node]});
                }
            }
        }
        
        //end dijkstra
        int mn=1e9 + 7;
        int mx=-1;
        for(int i=1;i<=n;i++){
            mn=min(mn,dist[i]);
            mx=max(mx,dist[i]);
        }
        if(mx==1e9+7) return -1;
        return mx;
    }
};
