
#include <bits/stdc++.h>
using namespace std;
// disjointSet
class disjointSet{
    vector<int> ump;
    public:
    vector<int>& getUmp(){
        return ump;
    }
    disjointSet(int n){
        ump.assign(n+1,-1);
    }
    int findSet(int u){
        // cout<<"in findSet "<<u<<endl;
        int r=u;
        while(ump[r]>=0){
            r=ump[r];
        }
        while(u!=r){
            int par=ump[u];
            ump[u]=r;
            u=par;
        }
        return r;
    }
    bool setUnion(int u,int v){
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot=findSet(u);
        int vroot=findSet(v);
        // cout<<"root : "<<uroot<<" "<<vroot<<endl;
        if(uroot == vroot) return false;
        int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        
        if(uchild>vchild){
            ump[uroot]=vroot;
            ump[vroot]=totalChild;
        }else{
            ump[vroot]=uroot;
            ump[uroot]=totalChild;
        }
        return true;
    }
    bool prefered_union(int u,int v){
        int uroot=findSet(u);
        int vroot=findSet(v);
        if(uroot==vroot) return false;
        int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        ump[uroot]=vroot;
        ump[vroot]=totalChild;
        return true;
    }
    bool checkOdd(int l,int r){
        for(int i=l;i<=r;i++){
            // cout<<ump[i]<<" ";
            if(ump[i]<0){
                if(abs(ump[i])%2) return false;
            }
        }
        // cout<<endl;
        return true;
    }
};
class MEX{
public:
    static int find(vector<int> & v){
        int n=v.size()+1;
        disjointSet *ds=new disjointSet(n+1);
        for(auto num:v){
            if(num<=n){
                ds->prefered_union(num,num+1);
            }
        }
        int mexof=ds->findSet(0);
        delete ds;
        return mexof;
    }
};
class GraphColoring{
public:
    static void visit(vector<vector<int>> & graph,vector<int> & color,vector<bool> & visited,int start){
        visited[start]=true;
        vector<int> surrounds={0};
        for(auto node:graph[start]){
            surrounds.push_back(color[node]);
        }
        int mex=MEX::find(surrounds);
        color[start]=mex;
    }
    static int run(vector<vector<int>> & graph){
        int n=graph.size();
        vector<int> color(n,0);
        vector<bool> visited(n,false);
        for(int i=0;i<n;i++){
            if(visited[i]==false) visit(graph,color,visited,i);
        }
        int colorability=0;
        for(int i=0;i<n;i++){
            cout<<"color of "<<i<<" is "<<color[i]<<endl;
            colorability=max(colorability,color[i]);
        }
        return colorability;
    }
};
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>> graph(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int colorability=GraphColoring::run(graph);
    cout<<"colorability : "<<colorability<<endl;
    return 0;
}
