#include <bits/stdc++.h>
#define int long long
using namespace std;
class MaxFlowDFS{
  int N;
  int source;
  int sink;
  int iterations=0;
  int flow=0;
  int residue=0;
  vector<map<int,int>> graph;
  vector<int> ResidueVector;
  vector<bool> isDone;
  public:
  MaxFlowDFS(int N,int source,int sink){
      this->N=N;
      this->source=source;
      this->sink=sink;
      graph.resize(N+1);
      isDone.assign(N,false);
      ResidueVector.assign(N,0);
  }
  void addEdge(int u,int v,int w){
      graph[u][v]=w;
      ResidueVector[u]+=w;
  }
  int max_flow(int start,int incoming){
        iterations++;
        if(start == sink ) return incoming;
        isDone[start]=true;
        int totalCut=0;
        int residual=incoming;
        int u=start;
        for(auto &edge : graph[start]){
            int v=edge.first;
            int w=edge.second;
            w=min(w,residual);
            // cout<<u<<" -> "<<v<<" : residue : "<<w<<endl;
            if(w>0 && isDone[v]==false){
                
                int currCut=max_flow(v,w);
                // cout<<u<<" -> "<<v<<" : "<<currCut<<endl;
                residual-=currCut;
                graph[u][v]-=currCut;
                graph[v][u]+=currCut;
                totalCut+=currCut;
            }
        }
        isDone[start]=false;
        return totalCut;
    }
    pair<int,int> max_flow_fast(int start,int incoming){
        iterations++;
        if(start == sink ) return {incoming,0};
        isDone[start]=true;
        int totalCut=0;
        int residual=incoming;
        int u=start;
        for(auto &edge : graph[start]){
            int v=edge.first;
            int w=edge.second;
            w=min(w,residual);
            cout<<u<<" -> "<<v<<" : residue : "<<w<<" vs "<<ResidueVector[v]<<endl;
            
            if(w>0 && (v==sink || ResidueVector[v]>0) && isDone[v]==false){
                pair<int,int> pr=max_flow_fast(v,w);
                int currCut=pr.first;
                
                cout<<u<<" -> "<<v<<" : "<<currCut<<endl;
                residual-=currCut;
                graph[u][v]-=currCut;
                ResidueVector[u]-=currCut;
                graph[v][u]+=currCut;
                ResidueVector[v]+=currCut;
                totalCut+=currCut;
            }
        }
        
        isDone[start]=false;
        return {totalCut,ResidueVector[start]};
    }
    int get_max_flow(){
        
        pair<int,int> pr=max_flow_fast(source,LLONG_MAX);
        this->flow=pr.first;
        this->residue=pr.second;
        return this->flow;
    }
};

    
signed main() {
    cout<<"ford Fulkerson : "<<endl;
    int n;
    cin>>n;
    int source;
    cin>>source;
    int sink;
    cin>>sink;
    int edges;
    cin>>edges;
    MaxFlowDFS *mxd=new MaxFlowDFS(n,source,sink);
    for(int i=0;i<edges;i++){
        int u,v,w;
        cin>>u>>v>>w;
        mxd->addEdge(u,v,w);
    }
    
    
    int flow=mxd->get_max_flow();
    cout<<"flow : "<<flow<<endl;
    return 0;
}
