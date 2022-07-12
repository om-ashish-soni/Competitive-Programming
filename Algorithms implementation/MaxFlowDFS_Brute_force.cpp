#include <bits/stdc++.h>
#define int long long
using namespace std;
class MaxFlowDFS{
  int N;
  int source;
  int sink;
  int iterations=0;
  int flow=0;
  vector<map<int,int>> graph;
  vector<bool> isDone;
  public:
  MaxFlowDFS(int N,int source,int sink){
      this->N=N;
      this->source=source;
      this->sink=sink;
      graph.resize(N+1);
      isDone.assign(N,false);
      
  }
  void addEdge(int u,int v,int w){
      graph[u][v]=w;
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
    int get_max_flow(){
        this->flow=max_flow(source,LLONG_MAX);
        return this->flow;
    }
};

    
signed main() {
    cout<<"ford Fulkerson : "<<endl;
    vector<map<int,int>> graph(N);
    vector<bool> isDone(N,false);
    MaxFlowDFS *mxd=new MaxFlowDFS(4,0,3);
    mxd->addEdge(0,1,1e5);
    mxd->addEdge(0,2,1e5);
    mxd->addEdge(1,3,1e5);
    mxd->addEdge(2,3,1e5);
    mxd->addEdge(1,2,1);
    
    int flow=mxd->get_max_flow();
    cout<<"flow : "<<flow<<endl;
    return 0;
}
